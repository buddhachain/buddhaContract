// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: recusal_buy_order.proto

#ifndef PROTOBUF_INCLUDED_recusal_5fbuy_5forder_2eproto
#define PROTOBUF_INCLUDED_recusal_5fbuy_5forder_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_recusal_5fbuy_5forder_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_recusal_5fbuy_5forder_2eproto {
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
class RecusalBuyOrder;
class RecusalBuyOrderDefaultTypeInternal;
extern RecusalBuyOrderDefaultTypeInternal _RecusalBuyOrder_default_instance_;
namespace google {
namespace protobuf {
template<> ::RecusalBuyOrder* Arena::CreateMaybeMessage<::RecusalBuyOrder>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class RecusalBuyOrder :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:RecusalBuyOrder) */ {
 public:
  RecusalBuyOrder();
  virtual ~RecusalBuyOrder();

  RecusalBuyOrder(const RecusalBuyOrder& from);

  inline RecusalBuyOrder& operator=(const RecusalBuyOrder& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  RecusalBuyOrder(RecusalBuyOrder&& from) noexcept
    : RecusalBuyOrder() {
    *this = ::std::move(from);
  }

  inline RecusalBuyOrder& operator=(RecusalBuyOrder&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const RecusalBuyOrder& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const RecusalBuyOrder* internal_default_instance() {
    return reinterpret_cast<const RecusalBuyOrder*>(
               &_RecusalBuyOrder_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(RecusalBuyOrder* other);
  friend void swap(RecusalBuyOrder& a, RecusalBuyOrder& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline RecusalBuyOrder* New() const final {
    return CreateMaybeMessage<RecusalBuyOrder>(nullptr);
  }

  RecusalBuyOrder* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<RecusalBuyOrder>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const RecusalBuyOrder& from);
  void MergeFrom(const RecusalBuyOrder& from);
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
  void InternalSwap(RecusalBuyOrder* other);
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

  // string order_id = 2;
  void clear_order_id();
  static const int kOrderIdFieldNumber = 2;
  const ::std::string& order_id() const;
  void set_order_id(const ::std::string& value);
  #if LANG_CXX11
  void set_order_id(::std::string&& value);
  #endif
  void set_order_id(const char* value);
  void set_order_id(const char* value, size_t size);
  ::std::string* mutable_order_id();
  ::std::string* release_order_id();
  void set_allocated_order_id(::std::string* order_id);

  // string start_timestamp = 4;
  void clear_start_timestamp();
  static const int kStartTimestampFieldNumber = 4;
  const ::std::string& start_timestamp() const;
  void set_start_timestamp(const ::std::string& value);
  #if LANG_CXX11
  void set_start_timestamp(::std::string&& value);
  #endif
  void set_start_timestamp(const char* value);
  void set_start_timestamp(const char* value, size_t size);
  ::std::string* mutable_start_timestamp();
  ::std::string* release_start_timestamp();
  void set_allocated_start_timestamp(::std::string* start_timestamp);

  // string confirm_timestamp = 5;
  void clear_confirm_timestamp();
  static const int kConfirmTimestampFieldNumber = 5;
  const ::std::string& confirm_timestamp() const;
  void set_confirm_timestamp(const ::std::string& value);
  #if LANG_CXX11
  void set_confirm_timestamp(::std::string&& value);
  #endif
  void set_confirm_timestamp(const char* value);
  void set_confirm_timestamp(const char* value, size_t size);
  ::std::string* mutable_confirm_timestamp();
  ::std::string* release_confirm_timestamp();
  void set_allocated_confirm_timestamp(::std::string* confirm_timestamp);

  // int64 state = 3;
  void clear_state();
  static const int kStateFieldNumber = 3;
  ::google::protobuf::int64 state() const;
  void set_state(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:RecusalBuyOrder)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr order_id_;
  ::google::protobuf::internal::ArenaStringPtr start_timestamp_;
  ::google::protobuf::internal::ArenaStringPtr confirm_timestamp_;
  ::google::protobuf::int64 state_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_recusal_5fbuy_5forder_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// RecusalBuyOrder

// string id = 1;
inline void RecusalBuyOrder::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuyOrder::id() const {
  // @@protoc_insertion_point(field_get:RecusalBuyOrder.id)
  return id_.GetNoArena();
}
inline void RecusalBuyOrder::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuyOrder.id)
}
#if LANG_CXX11
inline void RecusalBuyOrder::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuyOrder.id)
}
#endif
inline void RecusalBuyOrder::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuyOrder.id)
}
inline void RecusalBuyOrder::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuyOrder.id)
}
inline ::std::string* RecusalBuyOrder::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuyOrder.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuyOrder::release_id() {
  // @@protoc_insertion_point(field_release:RecusalBuyOrder.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuyOrder::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuyOrder.id)
}

// string order_id = 2;
inline void RecusalBuyOrder::clear_order_id() {
  order_id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuyOrder::order_id() const {
  // @@protoc_insertion_point(field_get:RecusalBuyOrder.order_id)
  return order_id_.GetNoArena();
}
inline void RecusalBuyOrder::set_order_id(const ::std::string& value) {
  
  order_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuyOrder.order_id)
}
#if LANG_CXX11
inline void RecusalBuyOrder::set_order_id(::std::string&& value) {
  
  order_id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuyOrder.order_id)
}
#endif
inline void RecusalBuyOrder::set_order_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  order_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuyOrder.order_id)
}
inline void RecusalBuyOrder::set_order_id(const char* value, size_t size) {
  
  order_id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuyOrder.order_id)
}
inline ::std::string* RecusalBuyOrder::mutable_order_id() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuyOrder.order_id)
  return order_id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuyOrder::release_order_id() {
  // @@protoc_insertion_point(field_release:RecusalBuyOrder.order_id)
  
  return order_id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuyOrder::set_allocated_order_id(::std::string* order_id) {
  if (order_id != nullptr) {
    
  } else {
    
  }
  order_id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), order_id);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuyOrder.order_id)
}

// int64 state = 3;
inline void RecusalBuyOrder::clear_state() {
  state_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 RecusalBuyOrder::state() const {
  // @@protoc_insertion_point(field_get:RecusalBuyOrder.state)
  return state_;
}
inline void RecusalBuyOrder::set_state(::google::protobuf::int64 value) {
  
  state_ = value;
  // @@protoc_insertion_point(field_set:RecusalBuyOrder.state)
}

// string start_timestamp = 4;
inline void RecusalBuyOrder::clear_start_timestamp() {
  start_timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuyOrder::start_timestamp() const {
  // @@protoc_insertion_point(field_get:RecusalBuyOrder.start_timestamp)
  return start_timestamp_.GetNoArena();
}
inline void RecusalBuyOrder::set_start_timestamp(const ::std::string& value) {
  
  start_timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuyOrder.start_timestamp)
}
#if LANG_CXX11
inline void RecusalBuyOrder::set_start_timestamp(::std::string&& value) {
  
  start_timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuyOrder.start_timestamp)
}
#endif
inline void RecusalBuyOrder::set_start_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  start_timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuyOrder.start_timestamp)
}
inline void RecusalBuyOrder::set_start_timestamp(const char* value, size_t size) {
  
  start_timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuyOrder.start_timestamp)
}
inline ::std::string* RecusalBuyOrder::mutable_start_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuyOrder.start_timestamp)
  return start_timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuyOrder::release_start_timestamp() {
  // @@protoc_insertion_point(field_release:RecusalBuyOrder.start_timestamp)
  
  return start_timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuyOrder::set_allocated_start_timestamp(::std::string* start_timestamp) {
  if (start_timestamp != nullptr) {
    
  } else {
    
  }
  start_timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), start_timestamp);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuyOrder.start_timestamp)
}

// string confirm_timestamp = 5;
inline void RecusalBuyOrder::clear_confirm_timestamp() {
  confirm_timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& RecusalBuyOrder::confirm_timestamp() const {
  // @@protoc_insertion_point(field_get:RecusalBuyOrder.confirm_timestamp)
  return confirm_timestamp_.GetNoArena();
}
inline void RecusalBuyOrder::set_confirm_timestamp(const ::std::string& value) {
  
  confirm_timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:RecusalBuyOrder.confirm_timestamp)
}
#if LANG_CXX11
inline void RecusalBuyOrder::set_confirm_timestamp(::std::string&& value) {
  
  confirm_timestamp_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:RecusalBuyOrder.confirm_timestamp)
}
#endif
inline void RecusalBuyOrder::set_confirm_timestamp(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  confirm_timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:RecusalBuyOrder.confirm_timestamp)
}
inline void RecusalBuyOrder::set_confirm_timestamp(const char* value, size_t size) {
  
  confirm_timestamp_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:RecusalBuyOrder.confirm_timestamp)
}
inline ::std::string* RecusalBuyOrder::mutable_confirm_timestamp() {
  
  // @@protoc_insertion_point(field_mutable:RecusalBuyOrder.confirm_timestamp)
  return confirm_timestamp_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* RecusalBuyOrder::release_confirm_timestamp() {
  // @@protoc_insertion_point(field_release:RecusalBuyOrder.confirm_timestamp)
  
  return confirm_timestamp_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void RecusalBuyOrder::set_allocated_confirm_timestamp(::std::string* confirm_timestamp) {
  if (confirm_timestamp != nullptr) {
    
  } else {
    
  }
  confirm_timestamp_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), confirm_timestamp);
  // @@protoc_insertion_point(field_set_allocated:RecusalBuyOrder.confirm_timestamp)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_recusal_5fbuy_5forder_2eproto