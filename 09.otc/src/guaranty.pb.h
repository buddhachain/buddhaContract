// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: guaranty.proto

#ifndef PROTOBUF_INCLUDED_guaranty_2eproto
#define PROTOBUF_INCLUDED_guaranty_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_guaranty_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_guaranty_2eproto {
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
class Guaranty;
class GuarantyDefaultTypeInternal;
extern GuarantyDefaultTypeInternal _Guaranty_default_instance_;
}  // namespace otc
namespace google {
namespace protobuf {
template<> ::otc::Guaranty* Arena::CreateMaybeMessage<::otc::Guaranty>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace otc {

// ===================================================================

class Guaranty :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:otc.Guaranty) */ {
 public:
  Guaranty();
  virtual ~Guaranty();

  Guaranty(const Guaranty& from);

  inline Guaranty& operator=(const Guaranty& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Guaranty(Guaranty&& from) noexcept
    : Guaranty() {
    *this = ::std::move(from);
  }

  inline Guaranty& operator=(Guaranty&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const Guaranty& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Guaranty* internal_default_instance() {
    return reinterpret_cast<const Guaranty*>(
               &_Guaranty_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Guaranty* other);
  friend void swap(Guaranty& a, Guaranty& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Guaranty* New() const final {
    return CreateMaybeMessage<Guaranty>(nullptr);
  }

  Guaranty* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Guaranty>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const Guaranty& from);
  void MergeFrom(const Guaranty& from);
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
  void InternalSwap(Guaranty* other);
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

  // string seller = 2;
  void clear_seller();
  static const int kSellerFieldNumber = 2;
  const ::std::string& seller() const;
  void set_seller(const ::std::string& value);
  #if LANG_CXX11
  void set_seller(::std::string&& value);
  #endif
  void set_seller(const char* value);
  void set_seller(const char* value, size_t size);
  ::std::string* mutable_seller();
  ::std::string* release_seller();
  void set_allocated_seller(::std::string* seller);

  // string timestamp = 6;
  void clear_timestamp();
  static const int kTimestampFieldNumber = 6;
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

  // int64 left = 4;
  void clear_left();
  static const int kLeftFieldNumber = 4;
  ::google::protobuf::int64 left() const;
  void set_left(::google::protobuf::int64 value);

  // int64 price = 5;
  void clear_price();
  static const int kPriceFieldNumber = 5;
  ::google::protobuf::int64 price() const;
  void set_price(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:otc.Guaranty)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr seller_;
  ::google::protobuf::internal::ArenaStringPtr timestamp_;
  ::google::protobuf::int64 amount_;
  ::google::protobuf::int64 left_;
  ::google::protobuf::int64 price_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_guaranty_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Guaranty

// string id = 1;
inline void Guaranty::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Guaranty::id() const {
  // @@protoc_insertion_point(field_get:otc.Guaranty.id)
  return id_.GetNoArena();
}
inline void Guaranty::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:otc.Guaranty.id)
}
#if LANG_CXX11
inline void Guaranty::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:otc.Guaranty.id)
}
#endif
inline void Guaranty::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:otc.Guaranty.id)
}
inline void Guaranty::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:otc.Guaranty.id)
}
inline ::std::string* Guaranty::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:otc.Guaranty.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Guaranty::release_id() {
  // @@protoc_insertion_point(field_release:otc.Guaranty.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Guaranty::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:otc.Guaranty.id)
}

// string seller = 2;
inline void Guaranty::clear_seller() {
  seller_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Guaranty::seller() const {
  // @@protoc_insertion_point(field_get:otc.Guaranty.seller)
  return seller_.GetNoArena();
}
inline void Guaranty::set_seller(const ::std::string& value) {
  
  seller_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:otc.Guaranty.seller)
}
#if LANG_CXX11
inline void Guaranty::set_seller(::std::string&& value) {
  
  seller_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:otc.Guaranty.seller)
}
#endif
inline void Guaranty::set_seller(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  seller_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:otc.Guaranty.seller)
}
inline void Guaranty::set_seller(const char* value, size_t size) {
  
  seller_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:otc.Guaranty.seller)
}
inline ::std::string* Guaranty::mutable_seller() {
  
  // @@protoc_insertion_point(field_mutable:otc.Guaranty.seller)
  return seller_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Guaranty::release_seller() {
  // @@protoc_insertion_point(field_release:otc.Guaranty.seller)
  
  return seller_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Guaranty::set_allocated_seller(::std::string* seller) {
  if (seller != nullptr) {
    
  } else {
    
  }
  seller_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), seller);
  // @@protoc_insertion_point(field_set_allocated:otc.Guaranty.seller)
}

// int64 amount = 3;
inline void Guaranty::clear_amount() {
  amount_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Guaranty::amount() const {
  // @@protoc_insertion_point(field_get:otc.Guaranty.amount)
  return amount_;
}
inline void Guaranty::set_amount(::google::protobuf::int64 value) {
  
  amount_ = value;
  // @@protoc_insertion_point(field_set:otc.Guaranty.amount)
}

// int64 left = 4;
inline void Guaranty::clear_left() {
  left_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Guaranty::left() const {
  // @@protoc_insertion_point(field_get:otc.Guaranty.left)
  return left_;
}
inline void Guaranty::set_left(::google::protobuf::int64 value) {
  
  left_ = value;
  // @@protoc_insertion_point(field_set:otc.Guaranty.left)
}

// int64 price = 5;
inline void Guaranty::clear_price() {
  price_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Guaranty::price() const {
  // @@protoc_insertion_point(field_get:otc.Guaranty.price)
  return price_;
}
inline void Guaranty::set_price(::google::protobuf::int64 value) {
  
  price_ = value;
  // @@protoc_insertion_point(field_set:otc.Guaranty.price)
}

// string timestamp = 6;
inline void Guaranty::clear_timestamp() {
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Guaranty::timestamp() const {
  // @@protoc_insertion_point(field_get:otc.Guaranty.timestamp)
  return timestamp_.GetNoArena();
}
inline void Guaranty::set_timestamp(const ::std::string& value) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:otc.Guaranty.timestamp)
}
#if LANG_CXX11
inline void Guaranty::set_timestamp(::std::string&& value) {
  
  timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:otc.Guaranty.timestamp)
}
#endif
inline void Guaranty::set_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:otc.Guaranty.timestamp)
}
inline void Guaranty::set_timestamp(const char* value, size_t size) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:otc.Guaranty.timestamp)
}
inline ::std::string* Guaranty::mutable_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:otc.Guaranty.timestamp)
  return timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Guaranty::release_timestamp() {
  // @@protoc_insertion_point(field_release:otc.Guaranty.timestamp)
  
  return timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Guaranty::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp != nullptr) {
    
  } else {
    
  }
  timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), timestamp);
  // @@protoc_insertion_point(field_set_allocated:otc.Guaranty.timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace otc

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_guaranty_2eproto