// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: redeem.proto

#ifndef PROTOBUF_INCLUDED_redeem_2eproto
#define PROTOBUF_INCLUDED_redeem_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_redeem_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_redeem_2eproto {
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
namespace otc {
class Redeem;
class RedeemDefaultTypeInternal;
extern RedeemDefaultTypeInternal _Redeem_default_instance_;
}  // namespace otc
namespace google {
namespace protobuf {
template<> ::otc::Redeem* Arena::CreateMaybeMessage<::otc::Redeem>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace otc {

// ===================================================================

class Redeem :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:otc.Redeem) */ {
 public:
  Redeem();
  virtual ~Redeem();

  Redeem(const Redeem& from);

  inline Redeem& operator=(const Redeem& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Redeem(Redeem&& from) noexcept
    : Redeem() {
    *this = ::std::move(from);
  }

  inline Redeem& operator=(Redeem&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const Redeem& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Redeem* internal_default_instance() {
    return reinterpret_cast<const Redeem*>(
               &_Redeem_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Redeem* other);
  friend void swap(Redeem& a, Redeem& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Redeem* New() const final {
    return CreateMaybeMessage<Redeem>(nullptr);
  }

  Redeem* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Redeem>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const Redeem& from);
  void MergeFrom(const Redeem& from);
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
  void InternalSwap(Redeem* other);
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

  // string guaranty_id = 2;
  void clear_guaranty_id();
  static const int kGuarantyIdFieldNumber = 2;
  const ::std::string& guaranty_id() const;
  void set_guaranty_id(const ::std::string& value);
  #if LANG_CXX11
  void set_guaranty_id(::std::string&& value);
  #endif
  void set_guaranty_id(const char* value);
  void set_guaranty_id(const char* value, size_t size);
  ::std::string* mutable_guaranty_id();
  ::std::string* release_guaranty_id();
  void set_allocated_guaranty_id(::std::string* guaranty_id);

  // string timestamp = 4;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 4;
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

  // int64 amount = 3;
  void clear_amount();
  static const int kAmountFieldNumber = 3;
  ::google::protobuf::int64 amount() const;
  void set_amount(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:otc.Redeem)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr guaranty_id_;
  ::google::protobuf::internal::ArenaStringPtr timestamp_;
  ::google::protobuf::int64 amount_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_redeem_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Redeem

// string id = 1;
inline void Redeem::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Redeem::id() const {
  // @@protoc_insertion_point(field_get:otc.Redeem.id)
  return id_.GetNoArena();
}
inline void Redeem::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:otc.Redeem.id)
}
#if LANG_CXX11
inline void Redeem::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:otc.Redeem.id)
}
#endif
inline void Redeem::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:otc.Redeem.id)
}
inline void Redeem::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:otc.Redeem.id)
}
inline ::std::string* Redeem::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:otc.Redeem.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Redeem::release_id() {
  // @@protoc_insertion_point(field_release:otc.Redeem.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Redeem::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:otc.Redeem.id)
}

// string guaranty_id = 2;
inline void Redeem::clear_guaranty_id() {
  guaranty_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Redeem::guaranty_id() const {
  // @@protoc_insertion_point(field_get:otc.Redeem.guaranty_id)
  return guaranty_id_.GetNoArena();
}
inline void Redeem::set_guaranty_id(const ::std::string& value) {
  
  guaranty_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:otc.Redeem.guaranty_id)
}
#if LANG_CXX11
inline void Redeem::set_guaranty_id(::std::string&& value) {
  
  guaranty_id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:otc.Redeem.guaranty_id)
}
#endif
inline void Redeem::set_guaranty_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  guaranty_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:otc.Redeem.guaranty_id)
}
inline void Redeem::set_guaranty_id(const char* value, size_t size) {
  
  guaranty_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:otc.Redeem.guaranty_id)
}
inline ::std::string* Redeem::mutable_guaranty_id() {
  
  // @@protoc_insertion_point(field_mutable:otc.Redeem.guaranty_id)
  return guaranty_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Redeem::release_guaranty_id() {
  // @@protoc_insertion_point(field_release:otc.Redeem.guaranty_id)
  
  return guaranty_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Redeem::set_allocated_guaranty_id(::std::string* guaranty_id) {
  if (guaranty_id != nullptr) {
    
  } else {
    
  }
  guaranty_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), guaranty_id);
  // @@protoc_insertion_point(field_set_allocated:otc.Redeem.guaranty_id)
}

// int64 amount = 3;
inline void Redeem::clear_amount() {
  amount_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Redeem::amount() const {
  // @@protoc_insertion_point(field_get:otc.Redeem.amount)
  return amount_;
}
inline void Redeem::set_amount(::google::protobuf::int64 value) {
  
  amount_ = value;
  // @@protoc_insertion_point(field_set:otc.Redeem.amount)
}

// string timestamp = 4;
inline void Redeem::clear_timestamp() {
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Redeem::timestamp() const {
  // @@protoc_insertion_point(field_get:otc.Redeem.timestamp)
  return timestamp_.GetNoArena();
}
inline void Redeem::set_timestamp(const ::std::string& value) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:otc.Redeem.timestamp)
}
#if LANG_CXX11
inline void Redeem::set_timestamp(::std::string&& value) {
  
  timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:otc.Redeem.timestamp)
}
#endif
inline void Redeem::set_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:otc.Redeem.timestamp)
}
inline void Redeem::set_timestamp(const char* value, size_t size) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:otc.Redeem.timestamp)
}
inline ::std::string* Redeem::mutable_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:otc.Redeem.timestamp)
  return timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Redeem::release_timestamp() {
  // @@protoc_insertion_point(field_release:otc.Redeem.timestamp)
  
  return timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Redeem::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp != nullptr) {
    
  } else {
    
  }
  timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), timestamp);
  // @@protoc_insertion_point(field_set_allocated:otc.Redeem.timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace otc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_redeem_2eproto