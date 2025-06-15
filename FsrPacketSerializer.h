// FsrPacketSerializer.h
#ifndef INET_ROUTING_FSR_FSRPACKETSERIALIZER_H
#define INET_ROUTING_FSR_FSRPACKETSERIALIZER_H

#include "inet/common/packet/serializer/FieldsChunkSerializer.h"

namespace inet {
namespace fsr {

class INET_API FsrPacketSerializer: public FieldsChunkSerializer {
protected:
    virtual const Ptr<Chunk> deserialize(MemoryInputStream &stream) const override;
    virtual void serialize(MemoryOutputStream &stream, const Ptr<const Chunk> &chunk) const override;

public:
    FsrPacketSerializer() : FieldsChunkSerializer() {}
};

} // namespace fsr
} // namespace inet

#endif // INET_ROUTING_FSR_FSRPACKETSERIALIZER_H
