// FsrPacketSerializer.cc
#include "FsrPacketSerializer.h"
#include "inet/common/packet/serializer/ChunkSerializerRegistry.h"
#include "inet/routing/fsr/FsrPacket_m.h"

namespace inet {
namespace fsr {
Register_Serializer(FsrPacket, FsrPacketSerializer);

const Ptr<Chunk> FsrPacketSerializer::deserialize(MemoryInputStream &stream) const {
    auto packet = makeShared<FsrPacket>();
    
    // Deserialize neighbor nodes first
    packet->setNeighborNodesArraySize(stream.readUint32Be());
    for (size_t i = 0; i < packet->getNeighborNodesArraySize(); i++) {
        packet->setNeighborNodes(i, stream.readIpv4Address());
    }

    // Then deserialize topology links
    packet->setTopologyLinksArraySize(stream.readUint32Be());
    for (size_t i = 0; i < packet->getTopologyLinksArraySize(); i++) {
        auto *link = new LinkEntry();
        link->neighborCount = stream.readUint8();
        link->neighborIndexStart = stream.readUint8();
        link->versionNumber = stream.readUint32Be();
        link->targetNode = stream.readIpv4Address();
        packet->setTopologyLinks(i, *link);
    }

    // Calculate packet size
    packet->setChunkLength(B(8) + B(packet->getTopologyLinksArraySize() * sizeof(LinkEntry) + 
                                  packet->getNeighborNodesArraySize() * sizeof(Ipv4Address)));
    return packet;
}

void FsrPacketSerializer::serialize(MemoryOutputStream &stream, const Ptr<const Chunk> &chunk) const {
    const auto &packet = staticPtrCast<const FsrPacket>(chunk);
    
    // Serialize neighbor nodes first
    stream.writeUint32Be(packet->getNeighborNodesArraySize());
    for (size_t i = 0; i < packet->getNeighborNodesArraySize(); i++) {
        stream.writeIpv4Address(packet->getNeighborNodes(i));
    }

    // Then serialize topology links
    stream.writeUint32Be(packet->getTopologyLinksArraySize());
    for (size_t i = 0; i < packet->getTopologyLinksArraySize(); i++) {
        const auto &link = packet->getTopologyLinks(i);
        stream.writeUint8(link.neighborCount);
        stream.writeUint8(link.neighborIndexStart);
        stream.writeUint32Be(link.versionNumber);
        stream.writeIpv4Address(link.targetNode);
    }
}

} // namespace fsr
} // namespace inet
