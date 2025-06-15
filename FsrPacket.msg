//
// FsrPacket.msg
//
import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.networklayer.contract.ipv4.Ipv4Address;

namespace inet;
struct LinkEntry {
    uint8 neighborCount;
    uint8 neighborIndexStart;
    uint32 versionNumber;
    Ipv4Address targetNode;
}
class FsrPacket extends FieldsChunk
{
    Ipv4Address neighborNodes[];
    LinkEntry topologyLinks[];
}
