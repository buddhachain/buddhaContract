// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: master.proto

#ifndef PROTOBUF_INCLUDED_master_2eproto
#define PROTOBUF_INCLUDED_master_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_master_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_master_2eproto {
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
namespace identity {
class Master;
class MasterDefaultTypeInternal;
extern MasterDefaultTypeInternal _Master_default_instance_;
}  // namespace identity
namespace google {
namespace protobuf {
template<> ::identity::Master* Arena::CreateMaybeMessage<::identity::Master>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace identity {

// ===================================================================

class Master :
    public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:identity.Master) */ {
 public:
  Master();
  virtual ~Master();

  Master(const Master& from);

  inline Master& operator=(const Master& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Master(Master&& from) noexcept
    : Master() {
    *this = ::std::move(from);
  }

  inline Master& operator=(Master&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const Master& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Master* internal_default_instance() {
    return reinterpret_cast<const Master*>(
               &_Master_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Master* other);
  friend void swap(Master& a, Master& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Master* New() const final {
    return CreateMaybeMessage<Master>(nullptr);
  }

  Master* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Master>(arena);
  }
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    final;
  void CopyFrom(const Master& from);
  void MergeFrom(const Master& from);
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
  void InternalSwap(Master* other);
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

  // string head_photo = 2;
  void clear_head_photo();
  static const int kHeadPhotoFieldNumber = 2;
  const ::std::string& head_photo() const;
  void set_head_photo(const ::std::string& value);
  #if LANG_CXX11
  void set_head_photo(::std::string&& value);
  #endif
  void set_head_photo(const char* value);
  void set_head_photo(const char* value, size_t size);
  ::std::string* mutable_head_photo();
  ::std::string* release_head_photo();
  void set_allocated_head_photo(::std::string* head_photo);

  // string buddhist_name = 3;
  void clear_buddhist_name();
  static const int kBuddhistNameFieldNumber = 3;
  const ::std::string& buddhist_name() const;
  void set_buddhist_name(const ::std::string& value);
  #if LANG_CXX11
  void set_buddhist_name(::std::string&& value);
  #endif
  void set_buddhist_name(const char* value);
  void set_buddhist_name(const char* value, size_t size);
  ::std::string* mutable_buddhist_name();
  ::std::string* release_buddhist_name();
  void set_allocated_buddhist_name(::std::string* buddhist_name);

  // string sect = 4;
  void clear_sect();
  static const int kSectFieldNumber = 4;
  const ::std::string& sect() const;
  void set_sect(const ::std::string& value);
  #if LANG_CXX11
  void set_sect(::std::string&& value);
  #endif
  void set_sect(const char* value);
  void set_sect(const char* value, size_t size);
  ::std::string* mutable_sect();
  ::std::string* release_sect();
  void set_allocated_sect(::std::string* sect);

  // string creditcode = 5;
  void clear_creditcode();
  static const int kCreditcodeFieldNumber = 5;
  const ::std::string& creditcode() const;
  void set_creditcode(const ::std::string& value);
  #if LANG_CXX11
  void set_creditcode(::std::string&& value);
  #endif
  void set_creditcode(const char* value);
  void set_creditcode(const char* value, size_t size);
  ::std::string* mutable_creditcode();
  ::std::string* release_creditcode();
  void set_allocated_creditcode(::std::string* creditcode);

  // string proof = 6;
  void clear_proof();
  static const int kProofFieldNumber = 6;
  const ::std::string& proof() const;
  void set_proof(const ::std::string& value);
  #if LANG_CXX11
  void set_proof(::std::string&& value);
  #endif
  void set_proof(const char* value);
  void set_proof(const char* value, size_t size);
  ::std::string* mutable_proof();
  ::std::string* release_proof();
  void set_allocated_proof(::std::string* proof);

  // bool approved = 7;
  void clear_approved();
  static const int kApprovedFieldNumber = 7;
  bool approved() const;
  void set_approved(bool value);

  // @@protoc_insertion_point(class_scope:identity.Master)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr head_photo_;
  ::google::protobuf::internal::ArenaStringPtr buddhist_name_;
  ::google::protobuf::internal::ArenaStringPtr sect_;
  ::google::protobuf::internal::ArenaStringPtr creditcode_;
  ::google::protobuf::internal::ArenaStringPtr proof_;
  bool approved_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_master_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Master

// string id = 1;
inline void Master::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Master::id() const {
  // @@protoc_insertion_point(field_get:identity.Master.id)
  return id_.GetNoArena();
}
inline void Master::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:identity.Master.id)
}
#if LANG_CXX11
inline void Master::set_id(::std::string&& value) {
  
  id_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:identity.Master.id)
}
#endif
inline void Master::set_id(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:identity.Master.id)
}
inline void Master::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:identity.Master.id)
}
inline ::std::string* Master::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:identity.Master.id)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Master::release_id() {
  // @@protoc_insertion_point(field_release:identity.Master.id)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Master::set_allocated_id(::std::string* id) {
  if (id != nullptr) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:identity.Master.id)
}

// string head_photo = 2;
inline void Master::clear_head_photo() {
  head_photo_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Master::head_photo() const {
  // @@protoc_insertion_point(field_get:identity.Master.head_photo)
  return head_photo_.GetNoArena();
}
inline void Master::set_head_photo(const ::std::string& value) {
  
  head_photo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:identity.Master.head_photo)
}
#if LANG_CXX11
inline void Master::set_head_photo(::std::string&& value) {
  
  head_photo_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:identity.Master.head_photo)
}
#endif
inline void Master::set_head_photo(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  head_photo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:identity.Master.head_photo)
}
inline void Master::set_head_photo(const char* value, size_t size) {
  
  head_photo_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:identity.Master.head_photo)
}
inline ::std::string* Master::mutable_head_photo() {
  
  // @@protoc_insertion_point(field_mutable:identity.Master.head_photo)
  return head_photo_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Master::release_head_photo() {
  // @@protoc_insertion_point(field_release:identity.Master.head_photo)
  
  return head_photo_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Master::set_allocated_head_photo(::std::string* head_photo) {
  if (head_photo != nullptr) {
    
  } else {
    
  }
  head_photo_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), head_photo);
  // @@protoc_insertion_point(field_set_allocated:identity.Master.head_photo)
}

// string buddhist_name = 3;
inline void Master::clear_buddhist_name() {
  buddhist_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Master::buddhist_name() const {
  // @@protoc_insertion_point(field_get:identity.Master.buddhist_name)
  return buddhist_name_.GetNoArena();
}
inline void Master::set_buddhist_name(const ::std::string& value) {
  
  buddhist_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:identity.Master.buddhist_name)
}
#if LANG_CXX11
inline void Master::set_buddhist_name(::std::string&& value) {
  
  buddhist_name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:identity.Master.buddhist_name)
}
#endif
inline void Master::set_buddhist_name(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  buddhist_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:identity.Master.buddhist_name)
}
inline void Master::set_buddhist_name(const char* value, size_t size) {
  
  buddhist_name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:identity.Master.buddhist_name)
}
inline ::std::string* Master::mutable_buddhist_name() {
  
  // @@protoc_insertion_point(field_mutable:identity.Master.buddhist_name)
  return buddhist_name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Master::release_buddhist_name() {
  // @@protoc_insertion_point(field_release:identity.Master.buddhist_name)
  
  return buddhist_name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Master::set_allocated_buddhist_name(::std::string* buddhist_name) {
  if (buddhist_name != nullptr) {
    
  } else {
    
  }
  buddhist_name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), buddhist_name);
  // @@protoc_insertion_point(field_set_allocated:identity.Master.buddhist_name)
}

// string sect = 4;
inline void Master::clear_sect() {
  sect_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Master::sect() const {
  // @@protoc_insertion_point(field_get:identity.Master.sect)
  return sect_.GetNoArena();
}
inline void Master::set_sect(const ::std::string& value) {
  
  sect_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:identity.Master.sect)
}
#if LANG_CXX11
inline void Master::set_sect(::std::string&& value) {
  
  sect_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:identity.Master.sect)
}
#endif
inline void Master::set_sect(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  sect_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:identity.Master.sect)
}
inline void Master::set_sect(const char* value, size_t size) {
  
  sect_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:identity.Master.sect)
}
inline ::std::string* Master::mutable_sect() {
  
  // @@protoc_insertion_point(field_mutable:identity.Master.sect)
  return sect_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Master::release_sect() {
  // @@protoc_insertion_point(field_release:identity.Master.sect)
  
  return sect_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Master::set_allocated_sect(::std::string* sect) {
  if (sect != nullptr) {
    
  } else {
    
  }
  sect_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), sect);
  // @@protoc_insertion_point(field_set_allocated:identity.Master.sect)
}

// string creditcode = 5;
inline void Master::clear_creditcode() {
  creditcode_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Master::creditcode() const {
  // @@protoc_insertion_point(field_get:identity.Master.creditcode)
  return creditcode_.GetNoArena();
}
inline void Master::set_creditcode(const ::std::string& value) {
  
  creditcode_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:identity.Master.creditcode)
}
#if LANG_CXX11
inline void Master::set_creditcode(::std::string&& value) {
  
  creditcode_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:identity.Master.creditcode)
}
#endif
inline void Master::set_creditcode(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  creditcode_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:identity.Master.creditcode)
}
inline void Master::set_creditcode(const char* value, size_t size) {
  
  creditcode_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:identity.Master.creditcode)
}
inline ::std::string* Master::mutable_creditcode() {
  
  // @@protoc_insertion_point(field_mutable:identity.Master.creditcode)
  return creditcode_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Master::release_creditcode() {
  // @@protoc_insertion_point(field_release:identity.Master.creditcode)
  
  return creditcode_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Master::set_allocated_creditcode(::std::string* creditcode) {
  if (creditcode != nullptr) {
    
  } else {
    
  }
  creditcode_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), creditcode);
  // @@protoc_insertion_point(field_set_allocated:identity.Master.creditcode)
}

// string proof = 6;
inline void Master::clear_proof() {
  proof_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Master::proof() const {
  // @@protoc_insertion_point(field_get:identity.Master.proof)
  return proof_.GetNoArena();
}
inline void Master::set_proof(const ::std::string& value) {
  
  proof_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:identity.Master.proof)
}
#if LANG_CXX11
inline void Master::set_proof(::std::string&& value) {
  
  proof_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:identity.Master.proof)
}
#endif
inline void Master::set_proof(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  proof_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:identity.Master.proof)
}
inline void Master::set_proof(const char* value, size_t size) {
  
  proof_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:identity.Master.proof)
}
inline ::std::string* Master::mutable_proof() {
  
  // @@protoc_insertion_point(field_mutable:identity.Master.proof)
  return proof_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Master::release_proof() {
  // @@protoc_insertion_point(field_release:identity.Master.proof)
  
  return proof_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Master::set_allocated_proof(::std::string* proof) {
  if (proof != nullptr) {
    
  } else {
    
  }
  proof_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), proof);
  // @@protoc_insertion_point(field_set_allocated:identity.Master.proof)
}

// bool approved = 7;
inline void Master::clear_approved() {
  approved_ = false;
}
inline bool Master::approved() const {
  // @@protoc_insertion_point(field_get:identity.Master.approved)
  return approved_;
}
inline void Master::set_approved(bool value) {
  
  approved_ = value;
  // @@protoc_insertion_point(field_set:identity.Master.approved)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace identity

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_master_2eproto
