// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: founder.proto

#ifndef PROTOBUF_INCLUDED_founder_2eproto
#define PROTOBUF_INCLUDED_founder_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_founder_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_founder_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
class Founder;
class FounderDefaultTypeInternal;
extern FounderDefaultTypeInternal _Founder_default_instance_;
namespace google {
namespace protobuf {
template<> ::Founder* Arena::CreateMaybeMessage<::Founder>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class Founder :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Founder) */ {
 public:
  Founder();
  virtual ~Founder();

  Founder(const Founder& from);

  inline Founder& operator=(const Founder& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Founder(Founder&& from) noexcept
    : Founder() {
    *this = ::std::move(from);
  }

  inline Founder& operator=(Founder&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const Founder& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Founder* internal_default_instance() {
    return reinterpret_cast<const Founder*>(
               &_Founder_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Founder* other);
  friend void swap(Founder& a, Founder& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Founder* New() const final {
    return CreateMaybeMessage<Founder>(nullptr);
  }

  Founder* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Founder>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const Founder& from);
  void MergeFrom(const Founder& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  void DiscardUnknownFields();
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Founder* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::std::string GetTypeName() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string id = 1;
  void clear_id();
  static const int kIdFieldNumber = 1;
  const ::std::string& id() const;
  void set_id(const ::std::string& value);
  #if LANG_CXX11
  void set_id(::std::string&& value);
  #endif
  void set_id(const char* value);
  void set_id(const char* value, size_t size);
  ::std::string* mutable_id();
  ::std::string* release_id();
  void set_allocated_id(::std::string* id);

  // string desc = 3;
  void clear_desc();
  static const int kDescFieldNumber = 3;
  const ::std::string& desc() const;
  void set_desc(const ::std::string& value);
  #if LANG_CXX11
  void set_desc(::std::string&& value);
  #endif
  void set_desc(const char* value);
  void set_desc(const char* value, size_t size);
  ::std::string* mutable_desc();
  ::std::string* release_desc();
  void set_allocated_desc(::std::string* desc);

  // string address = 4;
  void clear_address();
  static const int kAddressFieldNumber = 4;
  const ::std::string& address() const;
  void set_address(const ::std::string& value);
  #if LANG_CXX11
  void set_address(::std::string&& value);
  #endif
  void set_address(const char* value);
  void set_address(const char* value, size_t size);
  ::std::string* mutable_address();
  ::std::string* release_address();
  void set_allocated_address(::std::string* address);

  // string timestamp = 5;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 5;
  const ::std::string& timestamp() const;
  void set_timestamp(const ::std::string& value);
  #if LANG_CXX11
  void set_timestamp(::std::string&& value);
  #endif
  void set_timestamp(const char* value);
  void set_timestamp(const char* value, size_t size);
  ::std::string* mutable_timestamp();
  ::std::string* release_timestamp();
  void set_allocated_timestamp(::std::string* timestamp);

  // int64 type = 2;
  void clear_type();
  static const int kTypeFieldNumber = 2;
  ::google::protobuf::int64 type() const;
  void set_type(::google::protobuf::int64 value);

  // int64 guaranty = 6;
  void clear_guaranty();
  static const int kGuarantyFieldNumber = 6;
  ::google::protobuf::int64 guaranty() const;
  void set_guaranty(::google::protobuf::int64 value);

  // bool approved = 7;
  void clear_approved();
  static const int kApprovedFieldNumber = 7;
  bool approved() const;
  void set_approved(bool value);

  // @@protoc_insertion_point(class_scope:Founder)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr desc_;
  ::google::protobuf::internal::ArenaStringPtr address_;
  ::google::protobuf::internal::ArenaStringPtr timestamp_;
  ::google::protobuf::int64 type_;
  ::google::protobuf::int64 guaranty_;
  bool approved_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_founder_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Founder

// string id = 1;
inline void Founder::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Founder::id() const {
  // @@protoc_insertion_point(field_get:Founder.id)
  return id_.GetNoArena();
}
inline void Founder::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Founder.id)
}
#if LANG_CXX11
inline void Founder::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Founder.id)
}
#endif
inline void Founder::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Founder.id)
}
inline void Founder::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Founder.id)
}
inline ::std::string* Founder::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:Founder.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Founder::release_id() {
  // @@protoc_insertion_point(field_release:Founder.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Founder::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:Founder.id)
}

// int64 type = 2;
inline void Founder::clear_type() {
  type_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Founder::type() const {
  // @@protoc_insertion_point(field_get:Founder.type)
  return type_;
}
inline void Founder::set_type(::google::protobuf::int64 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:Founder.type)
}

// string desc = 3;
inline void Founder::clear_desc() {
  desc_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Founder::desc() const {
  // @@protoc_insertion_point(field_get:Founder.desc)
  return desc_.GetNoArena();
}
inline void Founder::set_desc(const ::std::string& value) {
  
  desc_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Founder.desc)
}
#if LANG_CXX11
inline void Founder::set_desc(::std::string&& value) {
  
  desc_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Founder.desc)
}
#endif
inline void Founder::set_desc(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  desc_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Founder.desc)
}
inline void Founder::set_desc(const char* value, size_t size) {
  
  desc_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Founder.desc)
}
inline ::std::string* Founder::mutable_desc() {
  
  // @@protoc_insertion_point(field_mutable:Founder.desc)
  return desc_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Founder::release_desc() {
  // @@protoc_insertion_point(field_release:Founder.desc)
  
  return desc_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Founder::set_allocated_desc(::std::string* desc) {
  if (desc != nullptr) {
    
  } else {
    
  }
  desc_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), desc);
  // @@protoc_insertion_point(field_set_allocated:Founder.desc)
}

// string address = 4;
inline void Founder::clear_address() {
  address_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Founder::address() const {
  // @@protoc_insertion_point(field_get:Founder.address)
  return address_.GetNoArena();
}
inline void Founder::set_address(const ::std::string& value) {
  
  address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Founder.address)
}
#if LANG_CXX11
inline void Founder::set_address(::std::string&& value) {
  
  address_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Founder.address)
}
#endif
inline void Founder::set_address(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Founder.address)
}
inline void Founder::set_address(const char* value, size_t size) {
  
  address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Founder.address)
}
inline ::std::string* Founder::mutable_address() {
  
  // @@protoc_insertion_point(field_mutable:Founder.address)
  return address_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Founder::release_address() {
  // @@protoc_insertion_point(field_release:Founder.address)
  
  return address_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Founder::set_allocated_address(::std::string* address) {
  if (address != nullptr) {
    
  } else {
    
  }
  address_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), address);
  // @@protoc_insertion_point(field_set_allocated:Founder.address)
}

// string timestamp = 5;
inline void Founder::clear_timestamp() {
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Founder::timestamp() const {
  // @@protoc_insertion_point(field_get:Founder.timestamp)
  return timestamp_.GetNoArena();
}
inline void Founder::set_timestamp(const ::std::string& value) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Founder.timestamp)
}
#if LANG_CXX11
inline void Founder::set_timestamp(::std::string&& value) {
  
  timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Founder.timestamp)
}
#endif
inline void Founder::set_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Founder.timestamp)
}
inline void Founder::set_timestamp(const char* value, size_t size) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Founder.timestamp)
}
inline ::std::string* Founder::mutable_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:Founder.timestamp)
  return timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Founder::release_timestamp() {
  // @@protoc_insertion_point(field_release:Founder.timestamp)
  
  return timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Founder::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp != nullptr) {
    
  } else {
    
  }
  timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), timestamp);
  // @@protoc_insertion_point(field_set_allocated:Founder.timestamp)
}

// int64 guaranty = 6;
inline void Founder::clear_guaranty() {
  guaranty_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Founder::guaranty() const {
  // @@protoc_insertion_point(field_get:Founder.guaranty)
  return guaranty_;
}
inline void Founder::set_guaranty(::google::protobuf::int64 value) {
  
  guaranty_ = value;
  // @@protoc_insertion_point(field_set:Founder.guaranty)
}

// bool approved = 7;
inline void Founder::clear_approved() {
  approved_ = false;
}
inline bool Founder::approved() const {
  // @@protoc_insertion_point(field_get:Founder.approved)
  return approved_;
}
inline void Founder::set_approved(bool value) {
  
  approved_ = value;
  // @@protoc_insertion_point(field_set:Founder.approved)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_founder_2eproto