// inet/src/inet/routing/fsr/Fsr.cc

#include <queue>
#include <cstdint>

#include "inet/common/Ptr.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/routing/fsr/Fsr.h"
#include "inet/routing/fsr/FsrPacket_m.h"
#include "inet/networklayer/contract/IRoute.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "omnetpp/clog.h"

namespace inet {
namespace fsr {

Define_Module(Fsr);

void Fsr::clearRouting() {
    for (int i = rt_table->getNumRoutes() - 1; i >= 0; i--) {
        IRoute *route = rt_table->getRoute(i);
        if (route->getSource() == this) {
            rt_table->deleteRoute(route);
        }
    }
}

void Fsr::addRoute(const Ipv4Address &dst, const Ipv4Address &nexthop, uint32_t hopCount) {
    IRoute *route = rt_table->createRoute();
    route->setSource(this);
    route->setMetric(hopCount);
    route->setInterface(if_table->findInterfaceByName(par("ifName")));
    route->setPrefixLength(32);
    route->setNextHop(nexthop);
    route->setSourceType(IRoute::MANUAL);
    route->setDestination(dst);
    rt_table->addRoute(route);
}

Ptr<FsrPacket> Fsr::createPacket(std::vector<LinkEntry> &links, std::vector<Ipv4Address> &neighbors) {
    auto fsrPacket = makeShared<FsrPacket>();
    fsrPacket->setTopologyLinksArraySize(links.size());
    for (size_t i = 0; i < links.size(); i++) {
        fsrPacket->setTopologyLinks(i, links[i]);
    }
    fsrPacket->setNeighborNodesArraySize(neighbors.size());
    for (size_t i = 0; i < neighbors.size(); i++) {
        fsrPacket->setNeighborNodes(i, neighbors[i]);
    }
    fsrPacket->setChunkLength(B(BASE_PACKET_SIZE) + B(links.size() * sizeof(LinkEntry) + neighbors.size() * sizeof(Ipv4Address)));
    return fsrPacket;
}

void Fsr::sendToNeighbors(const Ptr<const FsrPacket> &payload) {
    auto &neighbors = topo_table[node_addr].neighbors;
    for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
        Ipv4Address addr = *it;
        if (addr == node_addr)
            continue;

        Packet *packet = new Packet("FsrPacket:TopologyUpdate", payload);
        int interfaceId = CHK(if_table->findInterfaceByName(par("ifName")))->getInterfaceId();
        packet->addTag<InterfaceReq>()->setInterfaceId(interfaceId);
        packet->addTag<L3AddressReq>()->setDestAddress(addr);
        packet->addTag<L4PortReq>()->setDestPort(ROUTING_PORT);
        sock.send(packet);
        bytes_sent += packet->getByteLength();
    }
}

void Fsr::sendHello() {
    auto helloPkt = makeShared<FsrPacket>();
    helloPkt->setChunkLength(B(BASE_PACKET_SIZE));
    helloPkt->setNeighborNodesArraySize(0);
    helloPkt->setTopologyLinksArraySize(0);
    
    Packet *pk = new Packet("FsrPacket:Hello", helloPkt);
    pk->addTag<L4PortReq>()->setDestPort(ROUTING_PORT);
    pk->addTag<L3AddressReq>()->setDestAddress(Ipv4Address::ALLONES_ADDRESS);
    int ifId = if_table->findInterfaceByName(par("ifName"))->getInterfaceId();
    pk->addTag<InterfaceReq>()->setInterfaceId(ifId);
    
    bytes_sent += pk->getByteLength();
    sock.send(pk);
}

void Fsr::sendUpdate() {
    std::vector<LinkEntry> links;
    std::vector<Ipv4Address> neighbors;
    size_t k = 0;
    
    topo_table[node_addr].seq_num = (topo_table[node_addr].seq_num + 1) % MAX_SEQUENCE_NUMBER;
    
    for (auto it = topo_table.begin(); it != topo_table.end(); it++) {
        if ((it->second.age_val >= dist_table[it->first] || it->second.age_val >= (int)(max_wait_time / update_interval))) {
            LinkEntry link;
            link.versionNumber = it->second.seq_num;
            link.targetNode = it->first;
            link.neighborCount = it->second.neighbors.size();
            link.neighborIndexStart = k;
            
            it->second.age_val = 0;
            links.push_back(link);
            
            for (auto addr : it->second.neighbors) {
                neighbors.push_back(addr);
                k++;
            }
        }
    }
    
    auto fsrPacket = createPacket(links, neighbors);
    sendToNeighbors(fsrPacket);
}

void Fsr::updateRouting(std::map<Ipv4Address, Ipv4Address> &prev) {
    clearRouting();

    for (auto p : prev) {
        Ipv4Address dest = p.first;
        if (dest == node_addr || dist_table[dest] == UINT32_MAX)
            continue;
        Ipv4Address nexthop = dest;
        while (prev[nexthop] != node_addr && prev[nexthop] != Ipv4Address::UNSPECIFIED_ADDRESS) {
            nexthop = prev[nexthop];
        }
        addRoute(dest, nexthop, dist_table[dest]);
    }
}

void Fsr::computePaths() {
    std::queue<Ipv4Address> q;
    std::map<Ipv4Address, bool> visited;
    std::map<Ipv4Address, Ipv4Address> prev;
    for (auto it = topo_table.begin(); it != topo_table.end(); it++) {
        Ipv4Address addr = it->first;
        visited[addr] = false;
        dist_table[addr] = 0;
    }
    dist_table[node_addr] = 0;
    visited[node_addr] = true;
    q.push(node_addr);
    while (!q.empty()) {
        Ipv4Address u = q.front();
        q.pop();
        if (topo_table.find(u) == topo_table.end())
            continue;
        for (auto it = topo_table[u].neighbors.begin(); it != topo_table[u].neighbors.end(); it++) {
            Ipv4Address neighbor = *it;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist_table[neighbor] = dist_table[u] + 1;
                prev[neighbor] = u;
                q.push(neighbor);
            }
        }
    }
    updateRouting(prev);
}

void Fsr::processPacket(const Ptr<const FsrPacket> &packet, const L3Address &srcAddrs) {
    Ipv4Address src = srcAddrs.toIpv4();
    topo_table[node_addr].neighbors.insert(src);
    
    for (size_t i = 0; i < packet->getTopologyLinksArraySize(); i++) {
        uint32_t new_seq = packet->getTopologyLinks(i).versionNumber;
        Ipv4Address addr = packet->getTopologyLinks(i).targetNode;
        
        if (addr != node_addr) {
            if (topo_table.find(addr) == topo_table.end() || topo_table[addr].seq_num < new_seq) {
                std::set<Ipv4Address> neighbors;
                uint32_t startIndex = packet->getTopologyLinks(i).neighborIndexStart;
                uint32_t size = packet->getTopologyLinks(i).neighborCount;
                for (size_t j = startIndex; j < startIndex + size; j++) {
                    neighbors.insert(packet->getNeighborNodes(j));
                }
                topo_table[addr].neighbors = neighbors;
                topo_table[addr].seq_num = new_seq;
                life_table[addr] = life_time;
                topo_table[addr].age_val = 0;
            }
        }
    }
    
    computePaths();
}

void Fsr::socketDataArrived(UdpSocket *socket, Packet *packet) {
    const auto fsrPacket = packet->popAtFront<FsrPacket>();
    const char *packet_type = packet->getName();
    L3Address sourceAddr = packet->getTag<L3AddressInd>()->getSrcAddress();
    
    if (strcmp(packet_type, "FsrPacket:Hello") == 0) {
        auto src = sourceAddr.toIpv4();
        size_t old_size = topo_table[node_addr].neighbors.size();
        
        auto oldTimer = timeout_map.find(src);
        if (oldTimer != timeout_map.end()) {
            cancelAndDelete(oldTimer->second);
            timeout_map.erase(oldTimer);
        }
        
        topo_table[node_addr].neighbors.insert(src);
        if (old_size != topo_table[node_addr].neighbors.size()) {
            computePaths();
        }
        
        auto newTimeout = new cMessage("NeighborTimeout");
        timeout_map[src] = newTimeout;
        scheduleAfter(HELLO_TIMEOUT_MULTIPLIER * hello_interval, newTimeout);
    } 
    else if (strcmp(packet_type, "FsrPacket:TopologyUpdate") == 0) {
        processPacket(fsrPacket, sourceAddr);
    }
    delete packet;
}

void Fsr::initNode() {
    topo_table[node_addr].seq_num = 0;
    topo_table[node_addr].age_val = 0;
    topo_table[node_addr].neighbors.insert(node_addr);
    dist_table[node_addr] = 0;
}

void Fsr::handleStartOperation(LifecycleOperation *operation) {
    node_addr = rt_table->getRouterIdAsGeneric().toIpv4();
    sock.setCallback(this);
    sock.setOutputGate(gate("socketOut"));
    sock.setBroadcast(true);
    sock.bind(Ipv4Address(), ROUTING_PORT);

    initNode();

    double offset = uniform(0.0, jitter_max);
    scheduleAfter(2 * offset, update_timer);
    scheduleAfter(offset, hello_timer);
}

void Fsr::handleMessageWhenUp(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (msg == hello_timer) {
            sendHello();
            scheduleAfter(hello_interval + uniform(0.0, jitter_max), hello_timer);
        } else if (msg == update_timer) {
            for (auto it = topo_table.begin(); it != topo_table.end(); ++it)
                topo_table[it->first].age_val++;

            sendUpdate();
            scheduleAfter(update_interval + uniform(0.0, jitter_max), update_timer);
        } else if (msg == life_timer) {
            auto temp = std::set<Ipv4Address>();
            for (auto it = topo_table.begin(); it != topo_table.end(); ++it) {
                topo_table[it->first].age_val++;
                if (it->first == node_addr)
                    continue;

                life_table[it->first] = life_table[it->first] - 1;
                if (life_table[it->first] <= 0) {
                    temp.insert(it->first);
                }
            }
            for (const auto deadLinks : temp) {
                topo_table.erase(deadLinks);
                dist_table.erase(deadLinks);
                life_table.erase(deadLinks);
            }
            if (temp.size() > 0) {
                computePaths();
            }
            scheduleAfter(life_interval + uniform(0.0, jitter_max), life_timer);
        } else {
            for (auto it = timeout_map.begin(); it != timeout_map.end(); ++it) {
                if (msg == it->second) {
                    Ipv4Address deadNbr = it->first;
                    topo_table[node_addr].neighbors.erase(deadNbr);
                    topo_table.erase(deadNbr);
                    cancelAndDelete(it->second);
                    timeout_map.erase(it);
                    dist_table.erase(deadNbr);
                    computePaths();
                    return;
                }
            }
            throw cRuntimeError("Unknown self message %s", msg->getName());
        }
    } else {
        sock.processMessage(msg);
    }
}

void Fsr::initialize(int stage) {
    RoutingProtocolBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        node = getContainingNode(this);
        rt_table.reference(this, "rtModule", true);
        if_table.reference(this, "ifModule", true);
        
        hello_timer = new cMessage("helloTimer");
        update_timer = new cMessage("lspTimer");
        life_timer = new cMessage("lspLifeTimeTimer");
        
        update_interval = par("updateInt").doubleValue();
        max_wait_time = par("waitTime").doubleValue();
        hello_interval = par("helloInt").doubleValue();
        jitter_max = par("jitter").doubleValue();
        life_interval = par("lifeInt").doubleValue();
        
        life_time = DEFAULT_LIFE_TIME;
        bytes_sent = 0;
    }
}

void Fsr::finish() {
    recordScalar("bytes_sent", bytes_sent);
}

Fsr::Fsr() {
}

Fsr::~Fsr() {
    cancelAndDelete(hello_timer);
    cancelAndDelete(update_timer);
    cancelAndDelete(life_timer);
}

}
}
