// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: buy.proto

#ifndef PROTOBUF_INCLUDED_buy_2eproto
#define PROTOBUF_INCLUDED_buy_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_buy_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_buy_2eproto {
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
class Buy;
class BuyDefaultTypeInternal;
extern BuyDefaultTypeInternal _Buy_default_instance_;
namespace google {
namespace protobuf {
template<> ::Buy* Arena::CreateMaybeMessage<::Buy>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class Buy :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Buy) */ {
 public:
  Buy();
  virtual ~Buy();

  Buy(const Buy& from);

  inline Buy& operator=(const Buy& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Buy(Buy&& from) noexcept
    : Buy() {
    *this = ::std::move(from);
  }

  inline Buy& operator=(Buy&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const Buy& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Buy* internal_default_instance() {
    return reinterpret_cast<const Buy*>(
               &_Buy_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Buy* other);
  friend void swap(Buy& a, Buy& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Buy* New() const final {
    return CreateMaybeMessage<Buy>(nullptr);
  }

  Buy* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Buy>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const Buy& from);
  void MergeFrom(const Buy& from);
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
  void InternalSwap(Buy* other);
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

  // string account = 2;
  void clear_account();
  static const int kAccountFieldNumber = 2;
  const ::std::string& account() const;
  void set_account(const ::std::string& value);
  #if LANG_CXX11
  void set_account(::std::string&& value);
  #endif
  void set_account(const char* value);
  void set_account(const char* value, size_t size);
  ::std::string* mutable_account();
  ::std::string* release_account();
  void set_allocated_account(::std::string* account);

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

  // @@protoc_insertion_point(class_scope:Buy)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr account_;
  ::google::protobuf::internal::ArenaStringPtr timestamp_;
  ::google::protobuf::int64 amount_;
  ::google::protobuf::int64 left_;
  ::google::protobuf::int64 price_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_buy_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Buy

// string id = 1;
inline void Buy::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Buy::id() const {
  // @@protoc_insertion_point(field_get:Buy.id)
  return id_.GetNoArena();
}
inline void Buy::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Buy.id)
}
#if LANG_CXX11
inline void Buy::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Buy.id)
}
#endif
inline void Buy::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Buy.id)
}
inline void Buy::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Buy.id)
}
inline ::std::string* Buy::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:Buy.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Buy::release_id() {
  // @@protoc_insertion_point(field_release:Buy.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Buy::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:Buy.id)
}

// string account = 2;
inline void Buy::clear_account() {
  account_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Buy::account() const {
  // @@protoc_insertion_point(field_get:Buy.account)
  return account_.GetNoArena();
}
inline void Buy::set_account(const ::std::string& value) {
  
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Buy.account)
}
#if LANG_CXX11
inline void Buy::set_account(::std::string&& value) {
  
  account_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Buy.account)
}
#endif
inline void Buy::set_account(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Buy.account)
}
inline void Buy::set_account(const char* value, size_t size) {
  
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Buy.account)
}
inline ::std::string* Buy::mutable_account() {
  
  // @@protoc_insertion_point(field_mutable:Buy.account)
  return account_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Buy::release_account() {
  // @@protoc_insertion_point(field_release:Buy.account)
  
  return account_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Buy::set_allocated_account(::std::string* account) {
  if (account != nullptr) {
    
  } else {
    
  }
  account_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), account);
  // @@protoc_insertion_point(field_set_allocated:Buy.account)
}

// int64 amount = 3;
inline void Buy::clear_amount() {
  amount_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Buy::amount() const {
  // @@protoc_insertion_point(field_get:Buy.amount)
  return amount_;
}
inline void Buy::set_amount(::google::protobuf::int64 value) {
  
  amount_ = value;
  // @@protoc_insertion_point(field_set:Buy.amount)
}

// int64 left = 4;
inline void Buy::clear_left() {
  left_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Buy::left() const {
  // @@protoc_insertion_point(field_get:Buy.left)
  return left_;
}
inline void Buy::set_left(::google::protobuf::int64 value) {
  
  left_ = value;
  // @@protoc_insertion_point(field_set:Buy.left)
}

// int64 price = 5;
inline void Buy::clear_price() {
  price_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Buy::price() const {
  // @@protoc_insertion_point(field_get:Buy.price)
  return price_;
}
inline void Buy::set_price(::google::protobuf::int64 value) {
  
  price_ = value;
  // @@protoc_insertion_point(field_set:Buy.price)
}

// string timestamp = 6;
inline void Buy::clear_timestamp() {
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Buy::timestamp() const {
  // @@protoc_insertion_point(field_get:Buy.timestamp)
  return timestamp_.GetNoArena();
}
inline void Buy::set_timestamp(const ::std::string& value) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Buy.timestamp)
}
#if LANG_CXX11
inline void Buy::set_timestamp(::std::string&& value) {
  
  timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Buy.timestamp)
}
#endif
inline void Buy::set_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Buy.timestamp)
}
inline void Buy::set_timestamp(const char* value, size_t size) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Buy.timestamp)
}
inline ::std::string* Buy::mutable_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:Buy.timestamp)
  return timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Buy::release_timestamp() {
  // @@protoc_insertion_point(field_release:Buy.timestamp)
  
  return timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Buy::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp != nullptr) {
    
  } else {
    
  }
  timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), timestamp);
  // @@protoc_insertion_point(field_set_allocated:Buy.timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_buy_2eproto
