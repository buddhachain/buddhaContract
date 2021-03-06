// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: redeem_sell.proto

#include "redeem_sell.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

class RedeemSellDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<RedeemSell> _instance;
} _RedeemSell_default_instance_;
static void InitDefaultsRedeemSell_redeem_5fsell_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_RedeemSell_default_instance_;
    new (ptr) ::RedeemSell();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::RedeemSell::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_RedeemSell_redeem_5fsell_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsRedeemSell_redeem_5fsell_2eproto}, {}};


// ===================================================================

void RedeemSell::InitAsDefaultInstance() {
}
class RedeemSell::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int RedeemSell::kIdFieldNumber;
const int RedeemSell::kSellidFieldNumber;
const int RedeemSell::kAmountFieldNumber;
const int RedeemSell::kTimestampFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

RedeemSell::RedeemSell()
  : ::google::protobuf::MessageLite(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:RedeemSell)
}
RedeemSell::RedeemSell(const RedeemSell& from)
  : ::google::protobuf::MessageLite(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.id().size() > 0) {
    id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.id_);
  }
  sellid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.sellid().size() > 0) {
    sellid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.sellid_);
  }
  timestamp_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.timestamp().size() > 0) {
    timestamp_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.timestamp_);
  }
  amount_ = from.amount_;
  // @@protoc_insertion_point(copy_constructor:RedeemSell)
}

void RedeemSell::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_RedeemSell_redeem_5fsell_2eproto.base);
  id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sellid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  timestamp_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  amount_ = PROTOBUF_LONGLONG(0);
}

RedeemSell::~RedeemSell() {
  // @@protoc_insertion_point(destructor:RedeemSell)
  SharedDtor();
}

void RedeemSell::SharedDtor() {
  id_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sellid_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  timestamp_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void RedeemSell::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const RedeemSell& RedeemSell::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_RedeemSell_redeem_5fsell_2eproto.base);
  return *internal_default_instance();
}


void RedeemSell::Clear() {
// @@protoc_insertion_point(message_clear_start:RedeemSell)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  sellid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  timestamp_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  amount_ = PROTOBUF_LONGLONG(0);
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* RedeemSell::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<RedeemSell*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // string id = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 10) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName(nullptr);
        object = msg->mutable_id();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      // string sellid = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName(nullptr);
        object = msg->mutable_sellid();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      // int64 amount = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 24) goto handle_unusual;
        msg->set_amount(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // string timestamp = 4;
      case 4: {
        if (static_cast<::google::protobuf::uint8>(tag) != 34) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName(nullptr);
        object = msg->mutable_timestamp();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool RedeemSell::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::LiteUnknownFieldSetter unknown_fields_setter(
      &_internal_metadata_);
  ::google::protobuf::io::StringOutputStream unknown_fields_output(
      unknown_fields_setter.buffer());
  ::google::protobuf::io::CodedOutputStream unknown_fields_stream(
      &unknown_fields_output, false);
  // @@protoc_insertion_point(parse_start:RedeemSell)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (10 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_id()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->id().data(), static_cast<int>(this->id().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "RedeemSell.id"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string sellid = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sellid()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->sellid().data(), static_cast<int>(this->sellid().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "RedeemSell.sellid"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int64 amount = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (24 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &amount_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string timestamp = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (34 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_timestamp()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->timestamp().data(), static_cast<int>(this->timestamp().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "RedeemSell.timestamp"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(
            input, tag, &unknown_fields_stream));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:RedeemSell)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:RedeemSell)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void RedeemSell::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:RedeemSell)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string id = 1;
  if (this->id().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->id().data(), static_cast<int>(this->id().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "RedeemSell.id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->id(), output);
  }

  // string sellid = 2;
  if (this->sellid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->sellid().data(), static_cast<int>(this->sellid().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "RedeemSell.sellid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->sellid(), output);
  }

  // int64 amount = 3;
  if (this->amount() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->amount(), output);
  }

  // string timestamp = 4;
  if (this->timestamp().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->timestamp().data(), static_cast<int>(this->timestamp().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "RedeemSell.timestamp");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->timestamp(), output);
  }

  output->WriteRaw(_internal_metadata_.unknown_fields().data(),
                   static_cast<int>(_internal_metadata_.unknown_fields().size()));
  // @@protoc_insertion_point(serialize_end:RedeemSell)
}

size_t RedeemSell::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:RedeemSell)
  size_t total_size = 0;

  total_size += _internal_metadata_.unknown_fields().size();

  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string id = 1;
  if (this->id().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->id());
  }

  // string sellid = 2;
  if (this->sellid().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->sellid());
  }

  // string timestamp = 4;
  if (this->timestamp().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->timestamp());
  }

  // int64 amount = 3;
  if (this->amount() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->amount());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void RedeemSell::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::google::protobuf::down_cast<const RedeemSell*>(&from));
}

void RedeemSell::MergeFrom(const RedeemSell& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:RedeemSell)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.id().size() > 0) {

    id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.id_);
  }
  if (from.sellid().size() > 0) {

    sellid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.sellid_);
  }
  if (from.timestamp().size() > 0) {

    timestamp_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.timestamp_);
  }
  if (from.amount() != 0) {
    set_amount(from.amount());
  }
}

void RedeemSell::CopyFrom(const RedeemSell& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:RedeemSell)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RedeemSell::IsInitialized() const {
  return true;
}

void RedeemSell::Swap(RedeemSell* other) {
  if (other == this) return;
  InternalSwap(other);
}
void RedeemSell::InternalSwap(RedeemSell* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  id_.Swap(&other->id_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  sellid_.Swap(&other->sellid_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  timestamp_.Swap(&other->timestamp_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(amount_, other->amount_);
}

::std::string RedeemSell::GetTypeName() const {
  return "RedeemSell";
}


// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::RedeemSell* Arena::CreateMaybeMessage< ::RedeemSell >(Arena* arena) {
  return Arena::CreateInternal< ::RedeemSell >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
