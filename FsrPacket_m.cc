//
// Generated file, do not edit! Created by opp_msgtool 6.1 from inet/routing/fsr/FsrPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "FsrPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

LinkEntry::LinkEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const LinkEntry& a)
{
    doParsimPacking(b,a.neighborCount);
    doParsimPacking(b,a.neighborIndexStart);
    doParsimPacking(b,a.versionNumber);
    doParsimPacking(b,a.targetNode);
}

void __doUnpacking(omnetpp::cCommBuffer *b, LinkEntry& a)
{
    doParsimUnpacking(b,a.neighborCount);
    doParsimUnpacking(b,a.neighborIndexStart);
    doParsimUnpacking(b,a.versionNumber);
    doParsimUnpacking(b,a.targetNode);
}

class LinkEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_neighborCount,
        FIELD_neighborIndexStart,
        FIELD_versionNumber,
        FIELD_targetNode,
    };
  public:
    LinkEntryDescriptor();
    virtual ~LinkEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LinkEntryDescriptor)

LinkEntryDescriptor::LinkEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LinkEntry)), "")
{
    propertyNames = nullptr;
}

LinkEntryDescriptor::~LinkEntryDescriptor()
{
    delete[] propertyNames;
}

bool LinkEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinkEntry *>(obj)!=nullptr;
}

const char **LinkEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinkEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinkEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int LinkEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_neighborCount
        FD_ISEDITABLE,    // FIELD_neighborIndexStart
        FD_ISEDITABLE,    // FIELD_versionNumber
        0,    // FIELD_targetNode
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *LinkEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "neighborCount",
        "neighborIndexStart",
        "versionNumber",
        "targetNode",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int LinkEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "neighborCount") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "neighborIndexStart") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "versionNumber") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "targetNode") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *LinkEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "uint8",    // FIELD_neighborCount
        "uint8",    // FIELD_neighborIndexStart
        "uint32",    // FIELD_versionNumber
        "inet::Ipv4Address",    // FIELD_targetNode
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **LinkEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LinkEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LinkEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LinkEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinkEntry'", field);
    }
}

const char *LinkEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinkEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        case FIELD_neighborCount: return ulong2string(pp->neighborCount);
        case FIELD_neighborIndexStart: return ulong2string(pp->neighborIndexStart);
        case FIELD_versionNumber: return ulong2string(pp->versionNumber);
        case FIELD_targetNode: return pp->targetNode.str();
        default: return "";
    }
}

void LinkEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        case FIELD_neighborCount: pp->neighborCount = string2ulong(value); break;
        case FIELD_neighborIndexStart: pp->neighborIndexStart = string2ulong(value); break;
        case FIELD_versionNumber: pp->versionNumber = string2ulong(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkEntry'", field);
    }
}

omnetpp::cValue LinkEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        case FIELD_neighborCount: return (omnetpp::intval_t)(pp->neighborCount);
        case FIELD_neighborIndexStart: return (omnetpp::intval_t)(pp->neighborIndexStart);
        case FIELD_versionNumber: return (omnetpp::intval_t)(pp->versionNumber);
        case FIELD_targetNode: return omnetpp::toAnyPtr(&pp->targetNode); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinkEntry' as cValue -- field index out of range?", field);
    }
}

void LinkEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        case FIELD_neighborCount: pp->neighborCount = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        case FIELD_neighborIndexStart: pp->neighborIndexStart = omnetpp::checked_int_cast<uint8_t>(value.intValue()); break;
        case FIELD_versionNumber: pp->versionNumber = omnetpp::checked_int_cast<uint32_t>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkEntry'", field);
    }
}

const char *LinkEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LinkEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        case FIELD_targetNode: return omnetpp::toAnyPtr(&pp->targetNode); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinkEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkEntry *pp = omnetpp::fromAnyPtr<LinkEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkEntry'", field);
    }
}

Register_Class(FsrPacket)

FsrPacket::FsrPacket() : ::inet::FieldsChunk()
{
}

FsrPacket::FsrPacket(const FsrPacket& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

FsrPacket::~FsrPacket()
{
    delete [] this->neighborNodes;
    delete [] this->topologyLinks;
}

FsrPacket& FsrPacket::operator=(const FsrPacket& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void FsrPacket::copy(const FsrPacket& other)
{
    delete [] this->neighborNodes;
    this->neighborNodes = (other.neighborNodes_arraysize==0) ? nullptr : new Ipv4Address[other.neighborNodes_arraysize];
    neighborNodes_arraysize = other.neighborNodes_arraysize;
    for (size_t i = 0; i < neighborNodes_arraysize; i++) {
        this->neighborNodes[i] = other.neighborNodes[i];
    }
    delete [] this->topologyLinks;
    this->topologyLinks = (other.topologyLinks_arraysize==0) ? nullptr : new LinkEntry[other.topologyLinks_arraysize];
    topologyLinks_arraysize = other.topologyLinks_arraysize;
    for (size_t i = 0; i < topologyLinks_arraysize; i++) {
        this->topologyLinks[i] = other.topologyLinks[i];
    }
}

void FsrPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    b->pack(neighborNodes_arraysize);
    doParsimArrayPacking(b,this->neighborNodes,neighborNodes_arraysize);
    b->pack(topologyLinks_arraysize);
    doParsimArrayPacking(b,this->topologyLinks,topologyLinks_arraysize);
}

void FsrPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    delete [] this->neighborNodes;
    b->unpack(neighborNodes_arraysize);
    if (neighborNodes_arraysize == 0) {
        this->neighborNodes = nullptr;
    } else {
        this->neighborNodes = new Ipv4Address[neighborNodes_arraysize];
        doParsimArrayUnpacking(b,this->neighborNodes,neighborNodes_arraysize);
    }
    delete [] this->topologyLinks;
    b->unpack(topologyLinks_arraysize);
    if (topologyLinks_arraysize == 0) {
        this->topologyLinks = nullptr;
    } else {
        this->topologyLinks = new LinkEntry[topologyLinks_arraysize];
        doParsimArrayUnpacking(b,this->topologyLinks,topologyLinks_arraysize);
    }
}

size_t FsrPacket::getNeighborNodesArraySize() const
{
    return neighborNodes_arraysize;
}

const Ipv4Address& FsrPacket::getNeighborNodes(size_t k) const
{
    if (k >= neighborNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborNodes_arraysize, (unsigned long)k);
    return this->neighborNodes[k];
}

void FsrPacket::setNeighborNodesArraySize(size_t newSize)
{
    handleChange();
    Ipv4Address *neighborNodes2 = (newSize==0) ? nullptr : new Ipv4Address[newSize];
    size_t minSize = neighborNodes_arraysize < newSize ? neighborNodes_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        neighborNodes2[i] = this->neighborNodes[i];
    delete [] this->neighborNodes;
    this->neighborNodes = neighborNodes2;
    neighborNodes_arraysize = newSize;
}

void FsrPacket::setNeighborNodes(size_t k, const Ipv4Address& neighborNodes)
{
    if (k >= neighborNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborNodes_arraysize, (unsigned long)k);
    handleChange();
    this->neighborNodes[k] = neighborNodes;
}

void FsrPacket::insertNeighborNodes(size_t k, const Ipv4Address& neighborNodes)
{
    if (k > neighborNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborNodes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighborNodes_arraysize + 1;
    Ipv4Address *neighborNodes2 = new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborNodes2[i] = this->neighborNodes[i];
    neighborNodes2[k] = neighborNodes;
    for (i = k + 1; i < newSize; i++)
        neighborNodes2[i] = this->neighborNodes[i-1];
    delete [] this->neighborNodes;
    this->neighborNodes = neighborNodes2;
    neighborNodes_arraysize = newSize;
}

void FsrPacket::appendNeighborNodes(const Ipv4Address& neighborNodes)
{
    insertNeighborNodes(neighborNodes_arraysize, neighborNodes);
}

void FsrPacket::eraseNeighborNodes(size_t k)
{
    if (k >= neighborNodes_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighborNodes_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = neighborNodes_arraysize - 1;
    Ipv4Address *neighborNodes2 = (newSize == 0) ? nullptr : new Ipv4Address[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighborNodes2[i] = this->neighborNodes[i];
    for (i = k; i < newSize; i++)
        neighborNodes2[i] = this->neighborNodes[i+1];
    delete [] this->neighborNodes;
    this->neighborNodes = neighborNodes2;
    neighborNodes_arraysize = newSize;
}

size_t FsrPacket::getTopologyLinksArraySize() const
{
    return topologyLinks_arraysize;
}

const LinkEntry& FsrPacket::getTopologyLinks(size_t k) const
{
    if (k >= topologyLinks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)topologyLinks_arraysize, (unsigned long)k);
    return this->topologyLinks[k];
}

void FsrPacket::setTopologyLinksArraySize(size_t newSize)
{
    handleChange();
    LinkEntry *topologyLinks2 = (newSize==0) ? nullptr : new LinkEntry[newSize];
    size_t minSize = topologyLinks_arraysize < newSize ? topologyLinks_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        topologyLinks2[i] = this->topologyLinks[i];
    delete [] this->topologyLinks;
    this->topologyLinks = topologyLinks2;
    topologyLinks_arraysize = newSize;
}

void FsrPacket::setTopologyLinks(size_t k, const LinkEntry& topologyLinks)
{
    if (k >= topologyLinks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)topologyLinks_arraysize, (unsigned long)k);
    handleChange();
    this->topologyLinks[k] = topologyLinks;
}

void FsrPacket::insertTopologyLinks(size_t k, const LinkEntry& topologyLinks)
{
    if (k > topologyLinks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)topologyLinks_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = topologyLinks_arraysize + 1;
    LinkEntry *topologyLinks2 = new LinkEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        topologyLinks2[i] = this->topologyLinks[i];
    topologyLinks2[k] = topologyLinks;
    for (i = k + 1; i < newSize; i++)
        topologyLinks2[i] = this->topologyLinks[i-1];
    delete [] this->topologyLinks;
    this->topologyLinks = topologyLinks2;
    topologyLinks_arraysize = newSize;
}

void FsrPacket::appendTopologyLinks(const LinkEntry& topologyLinks)
{
    insertTopologyLinks(topologyLinks_arraysize, topologyLinks);
}

void FsrPacket::eraseTopologyLinks(size_t k)
{
    if (k >= topologyLinks_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)topologyLinks_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = topologyLinks_arraysize - 1;
    LinkEntry *topologyLinks2 = (newSize == 0) ? nullptr : new LinkEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        topologyLinks2[i] = this->topologyLinks[i];
    for (i = k; i < newSize; i++)
        topologyLinks2[i] = this->topologyLinks[i+1];
    delete [] this->topologyLinks;
    this->topologyLinks = topologyLinks2;
    topologyLinks_arraysize = newSize;
}

class FsrPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_neighborNodes,
        FIELD_topologyLinks,
    };
  public:
    FsrPacketDescriptor();
    virtual ~FsrPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(FsrPacketDescriptor)

FsrPacketDescriptor::FsrPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FsrPacket)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

FsrPacketDescriptor::~FsrPacketDescriptor()
{
    delete[] propertyNames;
}

bool FsrPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FsrPacket *>(obj)!=nullptr;
}

const char **FsrPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FsrPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FsrPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int FsrPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISRESIZABLE,    // FIELD_neighborNodes
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_topologyLinks
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *FsrPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "neighborNodes",
        "topologyLinks",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int FsrPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "neighborNodes") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "topologyLinks") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *FsrPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Ipv4Address",    // FIELD_neighborNodes
        "inet::LinkEntry",    // FIELD_topologyLinks
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **FsrPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *FsrPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int FsrPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborNodes: return pp->getNeighborNodesArraySize();
        case FIELD_topologyLinks: return pp->getTopologyLinksArraySize();
        default: return 0;
    }
}

void FsrPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborNodes: pp->setNeighborNodesArraySize(size); break;
        case FIELD_topologyLinks: pp->setTopologyLinksArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FsrPacket'", field);
    }
}

const char *FsrPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FsrPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborNodes: return pp->getNeighborNodes(i).str();
        case FIELD_topologyLinks: return "";
        default: return "";
    }
}

void FsrPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FsrPacket'", field);
    }
}

omnetpp::cValue FsrPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborNodes: return omnetpp::toAnyPtr(&pp->getNeighborNodes(i)); break;
        case FIELD_topologyLinks: return omnetpp::toAnyPtr(&pp->getTopologyLinks(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FsrPacket' as cValue -- field index out of range?", field);
    }
}

void FsrPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FsrPacket'", field);
    }
}

const char *FsrPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_topologyLinks: return omnetpp::opp_typename(typeid(LinkEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr FsrPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        case FIELD_neighborNodes: return omnetpp::toAnyPtr(&pp->getNeighborNodes(i)); break;
        case FIELD_topologyLinks: return omnetpp::toAnyPtr(&pp->getTopologyLinks(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FsrPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FsrPacket *pp = omnetpp::fromAnyPtr<FsrPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FsrPacket'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp

