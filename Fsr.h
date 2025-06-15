#ifndef INET_ROUTING_FSR_FSRROUTING_H_
#define INET_ROUTING_FSR_FSRROUTING_H_

#include <set>
#include <cstdint>

#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/networklayer/contract/IRoutingTable.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/routing/fsr/FsrPacket_m.h"
#include "inet/routing/base/RoutingProtocolBase.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "inet/common/packet/Packet.h"

namespace inet {
namespace fsr {

/**
 *  Fisheye State Routing (FSR) implementation for INET 4.5
 */
class INET_API Fsr: public RoutingProtocolBase, public UdpSocket::ICallback {
protected:
    static constexpr int ROUTING_PORT = 4242;
    static constexpr int DEFAULT_LIFE_TIME = 5;
    static constexpr int HELLO_TIMEOUT_MULTIPLIER = 4;
    static constexpr int BASE_PACKET_SIZE = 12;
    static constexpr int MAX_SEQUENCE_NUMBER = 0xFFFFFFFF;

    struct table_entry {
        std::set<Ipv4Address> neighbors;
        uint32_t seq_num;
        uint32_t age_val;
    };

    UdpSocket sock;
    cModule *node = nullptr;
    ModuleRefByPar<IRoutingTable> rt_table;
    ModuleRefByPar<IInterfaceTable> if_table;
    Ipv4Address node_addr;

    std::map<Ipv4Address, cMessage*> timeout_map;
    std::map<Ipv4Address, table_entry> topo_table;
    std::map<Ipv4Address, uint32_t> dist_table;
    std::map<Ipv4Address, int> life_table;

    uint32_t bytes_sent;
    int life_time;

    cMessage *hello_timer = nullptr;
    cMessage *update_timer = nullptr;
    cMessage *life_timer = nullptr;
    double update_interval;
    double hello_interval;
    double max_wait_time;
    double jitter_max;
    double life_interval;

protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override {}
    virtual void handleCrashOperation(LifecycleOperation *operation) override {}

    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void socketErrorArrived(UdpSocket *socket, Indication *indication) override {}
    virtual void socketClosed(UdpSocket *socket) override {}

    void processPacket(const Ptr<const FsrPacket> &packet, const L3Address &sourceAddr);
    void computePaths();
    void updateRouting(std::map<Ipv4Address, Ipv4Address> &prev);
    void initNode();
    void sendUpdate();
    void sendHello();
    void addRoute(const Ipv4Address &dst, const Ipv4Address &nexthop, uint32_t hopCount);
    void clearRouting();
    void sendToNeighbors(const Ptr<const FsrPacket> &payload);
    Ptr<FsrPacket> createPacket(std::vector<LinkEntry> &links, std::vector<Ipv4Address> &neighbors);

public:
    Fsr();
    virtual ~Fsr() override;
};

} // namespace fsr
} // namespace inet

#endif /* INET_ROUTING_FSR_FSRROUTING_H_ */
