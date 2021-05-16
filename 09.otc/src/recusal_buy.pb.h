// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: recusal_buy.proto

#ifndef PROTOBUF_INCLUDED_recusal_5fbuy_2eproto
#define PROTOBUF_INCLUDED_recusal_5fbuy_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_recusal_5fbuy_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_recusal_5fbuy_2eproto {
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
class RecusalBuy;
class RecusalBuyDefaultTypeInternal;
extern RecusalBuyDefaultTypeInternal _RecusalBuy_default_instance_;
namespace google {
namespace protobuf {
template<> ::RecusalBuy* Arena::CreateMaybeMessage<::RecusalBuy>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class RecusalBuy :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:RecusalBuy) */ {
 public:
  RecusalBuy();
  virtual ~RecusalBuy();

  RecusalBuy(const RecusalBuy& from);

  inline RecusalBuy& operator=(const RecusalBuy& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RecusalBuy(RecusalBuy&& from) noexcept
    : RecusalBuy() {
    *this = ::std::move(from);
  }

  inline RecusalBuy& operator=(RecusalBuy&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const RecusalBuy& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RecusalBuy* internal_default_instance() {
    return reinterpret_cast<const RecusalBuy*>(
               &_RecusalBuy_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RecusalBuy* other);
  friend void swap(RecusalBuy& a, RecusalBuy& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RecusalBuy* New() const final {
    return CreateMaybeMessage<RecusalBuy>(nullptr);
  }

  RecusalBuy* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RecusalBuy>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const RecusalBuy& from);
  void MergeFrom(const RecusalBuy& from);
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
  void InternalSwap(RecusalBuy* other);
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

  // string buy_id = 2;
  void clear_buy_id();
  static const int kBuyIdFieldNumber = 2;
  const ::std::string& buy_id() const;
  void set_buy_id(const ::std::string& value);
  #if LANG_CXX11
  void set_buy_id(::std::string&& value);
  #endif
  void set_buy_id(const char* value);
  void set_buy_id(const char* value, size_t size);
  ::std::string* mutable_buy_id();
  ::std::string* release_buy_id();
  void set_allocated_buy_id(::std::string* buy_id);

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

  // @@protoc_insertion_point(class_scope:RecusalBuy)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr buy_id_;
  ::google::protobuf::internal::ArenaStringPtr timestamp_;
  ::google::protobuf::int64 amount_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_recusal_5fbuy_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RecusalBuy

// string id = 1;
inline void RecusalBuy::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuy::id() const {
  // @@protoc_insertion_point(field_get:RecusalBuy.id)
  return id_.GetNoArena();
}
inline void RecusalBuy::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuy.id)
}
#if LANG_CXX11
inline void RecusalBuy::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuy.id)
}
#endif
inline void RecusalBuy::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuy.id)
}
inline void RecusalBuy::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuy.id)
}
inline ::std::string* RecusalBuy::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuy.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuy::release_id() {
  // @@protoc_insertion_point(field_release:RecusalBuy.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuy::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuy.id)
}

// string buy_id = 2;
inline void RecusalBuy::clear_buy_id() {
  buy_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuy::buy_id() const {
  // @@protoc_insertion_point(field_get:RecusalBuy.buy_id)
  return buy_id_.GetNoArena();
}
inline void RecusalBuy::set_buy_id(const ::std::string& value) {
  
  buy_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuy.buy_id)
}
#if LANG_CXX11
inline void RecusalBuy::set_buy_id(::std::string&& value) {
  
  buy_id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuy.buy_id)
}
#endif
inline void RecusalBuy::set_buy_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  buy_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuy.buy_id)
}
inline void RecusalBuy::set_buy_id(const char* value, size_t size) {
  
  buy_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuy.buy_id)
}
inline ::std::string* RecusalBuy::mutable_buy_id() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuy.buy_id)
  return buy_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuy::release_buy_id() {
  // @@protoc_insertion_point(field_release:RecusalBuy.buy_id)
  
  return buy_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuy::set_allocated_buy_id(::std::string* buy_id) {
  if (buy_id != nullptr) {
    
  } else {
    
  }
  buy_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), buy_id);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuy.buy_id)
}

// int64 amount = 3;
inline void RecusalBuy::clear_amount() {
  amount_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 RecusalBuy::amount() const {
  // @@protoc_insertion_point(field_get:RecusalBuy.amount)
  return amount_;
}
inline void RecusalBuy::set_amount(::google::protobuf::int64 value) {
  
  amount_ = value;
  // @@protoc_insertion_point(field_set:RecusalBuy.amount)
}

// string timestamp = 4;
inline void RecusalBuy::clear_timestamp() {
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuy::timestamp() const {
  // @@protoc_insertion_point(field_get:RecusalBuy.timestamp)
  return timestamp_.GetNoArena();
}
inline void RecusalBuy::set_timestamp(const ::std::string& value) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuy.timestamp)
}
#if LANG_CXX11
inline void RecusalBuy::set_timestamp(::std::string&& value) {
  
  timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuy.timestamp)
}
#endif
inline void RecusalBuy::set_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuy.timestamp)
}
inline void RecusalBuy::set_timestamp(const char* value, size_t size) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuy.timestamp)
}
inline ::std::string* RecusalBuy::mutable_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuy.timestamp)
  return timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuy::release_timestamp() {
  // @@protoc_insertion_point(field_release:RecusalBuy.timestamp)
  
  return timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuy::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp != nullptr) {
    
  } else {
    
  }
  timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), timestamp);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuy.timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_recusal_5fbuy_2eproto