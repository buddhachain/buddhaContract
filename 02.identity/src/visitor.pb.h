// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: visitor.proto

#ifndef PROTOBUF_INCLUDED_visitor_2eproto
#define PROTOBUF_INCLUDED_visitor_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_visitor_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_visitor_2eproto {
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
class Visitor;
class VisitorDefaultTypeInternal;
extern VisitorDefaultTypeInternal _Visitor_default_instance_;
namespace google {
namespace protobuf {
template<> ::Visitor* Arena::CreateMaybeMessage<::Visitor>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class Visitor :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Visitor) */ {
 public:
  Visitor();
  virtual ~Visitor();

  Visitor(const Visitor& from);

  inline Visitor& operator=(const Visitor& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Visitor(Visitor&& from) noexcept
    : Visitor() {
    *this = ::std::move(from);
  }

  inline Visitor& operator=(Visitor&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const Visitor& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Visitor* internal_default_instance() {
    return reinterpret_cast<const Visitor*>(
               &_Visitor_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Visitor* other);
  friend void swap(Visitor& a, Visitor& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Visitor* New() const final {
    return CreateMaybeMessage<Visitor>(nullptr);
  }

  Visitor* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Visitor>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const Visitor& from);
  void MergeFrom(const Visitor& from);
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
  void InternalSwap(Visitor* other);
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

  // string nickname = 2;
  void clear_nickname();
  static const int kNicknameFieldNumber = 2;
  const ::std::string& nickname() const;
  void set_nickname(const ::std::string& value);
  #if LANG_CXX11
  void set_nickname(::std::string&& value);
  #endif
  void set_nickname(const char* value);
  void set_nickname(const char* value, size_t size);
  ::std::string* mutable_nickname();
  ::std::string* release_nickname();
  void set_allocated_nickname(::std::string* nickname);

  // int64 wechat = 3;
  void clear_wechat();
  static const int kWechatFieldNumber = 3;
  ::google::protobuf::int64 wechat() const;
  void set_wechat(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:Visitor)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr nickname_;
  ::google::protobuf::int64 wechat_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_visitor_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Visitor

// string id = 1;
inline void Visitor::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Visitor::id() const {
  // @@protoc_insertion_point(field_get:Visitor.id)
  return id_.GetNoArena();
}
inline void Visitor::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Visitor.id)
}
#if LANG_CXX11
inline void Visitor::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Visitor.id)
}
#endif
inline void Visitor::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Visitor.id)
}
inline void Visitor::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Visitor.id)
}
inline ::std::string* Visitor::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:Visitor.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Visitor::release_id() {
  // @@protoc_insertion_point(field_release:Visitor.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Visitor::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:Visitor.id)
}

// string nickname = 2;
inline void Visitor::clear_nickname() {
  nickname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Visitor::nickname() const {
  // @@protoc_insertion_point(field_get:Visitor.nickname)
  return nickname_.GetNoArena();
}
inline void Visitor::set_nickname(const ::std::string& value) {
  
  nickname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Visitor.nickname)
}
#if LANG_CXX11
inline void Visitor::set_nickname(::std::string&& value) {
  
  nickname_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Visitor.nickname)
}
#endif
inline void Visitor::set_nickname(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  nickname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Visitor.nickname)
}
inline void Visitor::set_nickname(const char* value, size_t size) {
  
  nickname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Visitor.nickname)
}
inline ::std::string* Visitor::mutable_nickname() {
  
  // @@protoc_insertion_point(field_mutable:Visitor.nickname)
  return nickname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Visitor::release_nickname() {
  // @@protoc_insertion_point(field_release:Visitor.nickname)
  
  return nickname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Visitor::set_allocated_nickname(::std::string* nickname) {
  if (nickname != nullptr) {
    
  } else {
    
  }
  nickname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), nickname);
  // @@protoc_insertion_point(field_set_allocated:Visitor.nickname)
}

// int64 wechat = 3;
inline void Visitor::clear_wechat() {
  wechat_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Visitor::wechat() const {
  // @@protoc_insertion_point(field_get:Visitor.wechat)
  return wechat_;
}
inline void Visitor::set_wechat(::google::protobuf::int64 value) {
  
  wechat_ = value;
  // @@protoc_insertion_point(field_set:Visitor.wechat)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_visitor_2eproto
