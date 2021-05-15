// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: redeem_sell.proto

#ifndef PROTOBUF_INCLUDED_redeem_5fsell_2eproto
#define PROTOBUF_INCLUDED_redeem_5fsell_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_redeem_5fsell_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_redeem_5fsell_2eproto {
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
class RedeemSell;
class RedeemSellDefaultTypeInternal;
extern RedeemSellDefaultTypeInternal _RedeemSell_default_instance_;
namespace google {
namespace protobuf {
template<> ::RedeemSell* Arena::CreateMaybeMessage<::RedeemSell>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class RedeemSell :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:RedeemSell) */ {
 public:
  RedeemSell();
  virtual ~RedeemSell();

  RedeemSell(const RedeemSell& from);

  inline RedeemSell& operator=(const RedeemSell& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RedeemSell(RedeemSell&& from) noexcept
    : RedeemSell() {
    *this = ::std::move(from);
  }

  inline RedeemSell& operator=(RedeemSell&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const RedeemSell& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RedeemSell* internal_default_instance() {
    return reinterpret_cast<const RedeemSell*>(
               &_RedeemSell_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RedeemSell* other);
  friend void swap(RedeemSell& a, RedeemSell& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RedeemSell* New() const final {
    return CreateMaybeMessage<RedeemSell>(nullptr);
  }

  RedeemSell* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RedeemSell>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const RedeemSell& from);
  void MergeFrom(const RedeemSell& from);
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
  void InternalSwap(RedeemSell* other);
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

  // string sellid = 2;
  void clear_sellid();
  static const int kSellidFieldNumber = 2;
  const ::std::string& sellid() const;
  void set_sellid(const ::std::string& value);
  #if LANG_CXX11
  void set_sellid(::std::string&& value);
  #endif
  void set_sellid(const char* value);
  void set_sellid(const char* value, size_t size);
  ::std::string* mutable_sellid();
  ::std::string* release_sellid();
  void set_allocated_sellid(::std::string* sellid);

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

  // @@protoc_insertion_point(class_scope:RedeemSell)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr sellid_;
  ::google::protobuf::internal::ArenaStringPtr timestamp_;
  ::google::protobuf::int64 amount_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_redeem_5fsell_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RedeemSell

// string id = 1;
inline void RedeemSell::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RedeemSell::id() const {
  // @@protoc_insertion_point(field_get:RedeemSell.id)
  return id_.GetNoArena();
}
inline void RedeemSell::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RedeemSell.id)
}
#if LANG_CXX11
inline void RedeemSell::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RedeemSell.id)
}
#endif
inline void RedeemSell::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RedeemSell.id)
}
inline void RedeemSell::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RedeemSell.id)
}
inline ::std::string* RedeemSell::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:RedeemSell.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RedeemSell::release_id() {
  // @@protoc_insertion_point(field_release:RedeemSell.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RedeemSell::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:RedeemSell.id)
}

// string sellid = 2;
inline void RedeemSell::clear_sellid() {
  sellid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RedeemSell::sellid() const {
  // @@protoc_insertion_point(field_get:RedeemSell.sellid)
  return sellid_.GetNoArena();
}
inline void RedeemSell::set_sellid(const ::std::string& value) {
  
  sellid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RedeemSell.sellid)
}
#if LANG_CXX11
inline void RedeemSell::set_sellid(::std::string&& value) {
  
  sellid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RedeemSell.sellid)
}
#endif
inline void RedeemSell::set_sellid(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  sellid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RedeemSell.sellid)
}
inline void RedeemSell::set_sellid(const char* value, size_t size) {
  
  sellid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RedeemSell.sellid)
}
inline ::std::string* RedeemSell::mutable_sellid() {
  
  // @@protoc_insertion_point(field_mutable:RedeemSell.sellid)
  return sellid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RedeemSell::release_sellid() {
  // @@protoc_insertion_point(field_release:RedeemSell.sellid)
  
  return sellid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RedeemSell::set_allocated_sellid(::std::string* sellid) {
  if (sellid != nullptr) {
    
  } else {
    
  }
  sellid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sellid);
  // @@protoc_insertion_point(field_set_allocated:RedeemSell.sellid)
}

// int64 amount = 3;
inline void RedeemSell::clear_amount() {
  amount_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 RedeemSell::amount() const {
  // @@protoc_insertion_point(field_get:RedeemSell.amount)
  return amount_;
}
inline void RedeemSell::set_amount(::google::protobuf::int64 value) {
  
  amount_ = value;
  // @@protoc_insertion_point(field_set:RedeemSell.amount)
}

// string timestamp = 4;
inline void RedeemSell::clear_timestamp() {
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RedeemSell::timestamp() const {
  // @@protoc_insertion_point(field_get:RedeemSell.timestamp)
  return timestamp_.GetNoArena();
}
inline void RedeemSell::set_timestamp(const ::std::string& value) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RedeemSell.timestamp)
}
#if LANG_CXX11
inline void RedeemSell::set_timestamp(::std::string&& value) {
  
  timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RedeemSell.timestamp)
}
#endif
inline void RedeemSell::set_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RedeemSell.timestamp)
}
inline void RedeemSell::set_timestamp(const char* value, size_t size) {
  
  timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RedeemSell.timestamp)
}
inline ::std::string* RedeemSell::mutable_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:RedeemSell.timestamp)
  return timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RedeemSell::release_timestamp() {
  // @@protoc_insertion_point(field_release:RedeemSell.timestamp)
  
  return timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RedeemSell::set_allocated_timestamp(::std::string* timestamp) {
  if (timestamp != nullptr) {
    
  } else {
    
  }
  timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), timestamp);
  // @@protoc_insertion_point(field_set_allocated:RedeemSell.timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_redeem_5fsell_2eproto
