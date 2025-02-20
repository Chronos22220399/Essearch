// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: query.proto
// Protobuf C++ Version: 5.29.2

#ifndef query_2eproto_2epb_2eh
#define query_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5029002
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_reflection.h"
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_query_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_query_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_query_2eproto;
class QueryRequest;
struct QueryRequestDefaultTypeInternal;
extern QueryRequestDefaultTypeInternal _QueryRequest_default_instance_;
class QueryResponse;
struct QueryResponseDefaultTypeInternal;
extern QueryResponseDefaultTypeInternal _QueryResponse_default_instance_;
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

enum QueryMode : int {
  Normal = 0,
  Advanced = 1,
  QueryMode_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  QueryMode_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool QueryMode_IsValid(int value);
extern const uint32_t QueryMode_internal_data_[];
constexpr QueryMode QueryMode_MIN = static_cast<QueryMode>(0);
constexpr QueryMode QueryMode_MAX = static_cast<QueryMode>(1);
constexpr int QueryMode_ARRAYSIZE = 1 + 1;
const ::google::protobuf::EnumDescriptor*
QueryMode_descriptor();
template <typename T>
const std::string& QueryMode_Name(T value) {
  static_assert(std::is_same<T, QueryMode>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to QueryMode_Name().");
  return QueryMode_Name(static_cast<QueryMode>(value));
}
template <>
inline const std::string& QueryMode_Name(QueryMode value) {
  return ::google::protobuf::internal::NameOfDenseEnum<QueryMode_descriptor,
                                                 0, 1>(
      static_cast<int>(value));
}
inline bool QueryMode_Parse(absl::string_view name, QueryMode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<QueryMode>(
      QueryMode_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class QueryResponse final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:QueryResponse) */ {
 public:
  inline QueryResponse() : QueryResponse(nullptr) {}
  ~QueryResponse() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(QueryResponse* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(QueryResponse));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR QueryResponse(
      ::google::protobuf::internal::ConstantInitialized);

  inline QueryResponse(const QueryResponse& from) : QueryResponse(nullptr, from) {}
  inline QueryResponse(QueryResponse&& from) noexcept
      : QueryResponse(nullptr, std::move(from)) {}
  inline QueryResponse& operator=(const QueryResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline QueryResponse& operator=(QueryResponse&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const QueryResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const QueryResponse* internal_default_instance() {
    return reinterpret_cast<const QueryResponse*>(
        &_QueryResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(QueryResponse& a, QueryResponse& b) { a.Swap(&b); }
  inline void Swap(QueryResponse* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(QueryResponse* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  QueryResponse* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<QueryResponse>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const QueryResponse& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const QueryResponse& from) { QueryResponse::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(QueryResponse* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "QueryResponse"; }

 protected:
  explicit QueryResponse(::google::protobuf::Arena* arena);
  QueryResponse(::google::protobuf::Arena* arena, const QueryResponse& from);
  QueryResponse(::google::protobuf::Arena* arena, QueryResponse&& from) noexcept
      : QueryResponse(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kDocIdFieldNumber = 1,
  };
  // repeated uint32 docId = 1;
  int docid_size() const;
  private:
  int _internal_docid_size() const;

  public:
  void clear_docid() ;
  ::uint32_t docid(int index) const;
  void set_docid(int index, ::uint32_t value);
  void add_docid(::uint32_t value);
  const ::google::protobuf::RepeatedField<::uint32_t>& docid() const;
  ::google::protobuf::RepeatedField<::uint32_t>* mutable_docid();

  private:
  const ::google::protobuf::RepeatedField<::uint32_t>& _internal_docid() const;
  ::google::protobuf::RepeatedField<::uint32_t>* _internal_mutable_docid();

  public:
  // @@protoc_insertion_point(class_scope:QueryResponse)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      0, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const QueryResponse& from_msg);
    ::google::protobuf::RepeatedField<::uint32_t> docid_;
    ::google::protobuf::internal::CachedSize _docid_cached_byte_size_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_query_2eproto;
};
// -------------------------------------------------------------------

class QueryRequest final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:QueryRequest) */ {
 public:
  inline QueryRequest() : QueryRequest(nullptr) {}
  ~QueryRequest() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(QueryRequest* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(QueryRequest));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR QueryRequest(
      ::google::protobuf::internal::ConstantInitialized);

  inline QueryRequest(const QueryRequest& from) : QueryRequest(nullptr, from) {}
  inline QueryRequest(QueryRequest&& from) noexcept
      : QueryRequest(nullptr, std::move(from)) {}
  inline QueryRequest& operator=(const QueryRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline QueryRequest& operator=(QueryRequest&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const QueryRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const QueryRequest* internal_default_instance() {
    return reinterpret_cast<const QueryRequest*>(
        &_QueryRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(QueryRequest& a, QueryRequest& b) { a.Swap(&b); }
  inline void Swap(QueryRequest* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(QueryRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  QueryRequest* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<QueryRequest>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const QueryRequest& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const QueryRequest& from) { QueryRequest::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(QueryRequest* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "QueryRequest"; }

 protected:
  explicit QueryRequest(::google::protobuf::Arena* arena);
  QueryRequest(::google::protobuf::Arena* arena, const QueryRequest& from);
  QueryRequest(::google::protobuf::Arena* arena, QueryRequest&& from) noexcept
      : QueryRequest(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kQueryContentFieldNumber = 2,
    kQueryModeFieldNumber = 1,
  };
  // string queryContent = 2;
  void clear_querycontent() ;
  const std::string& querycontent() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_querycontent(Arg_&& arg, Args_... args);
  std::string* mutable_querycontent();
  PROTOBUF_NODISCARD std::string* release_querycontent();
  void set_allocated_querycontent(std::string* value);

  private:
  const std::string& _internal_querycontent() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_querycontent(
      const std::string& value);
  std::string* _internal_mutable_querycontent();

  public:
  // .QueryMode queryMode = 1;
  void clear_querymode() ;
  ::QueryMode querymode() const;
  void set_querymode(::QueryMode value);

  private:
  ::QueryMode _internal_querymode() const;
  void _internal_set_querymode(::QueryMode value);

  public:
  // @@protoc_insertion_point(class_scope:QueryRequest)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      1, 2, 0,
      33, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const QueryRequest& from_msg);
    ::google::protobuf::internal::ArenaStringPtr querycontent_;
    int querymode_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_query_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// QueryRequest

// .QueryMode queryMode = 1;
inline void QueryRequest::clear_querymode() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.querymode_ = 0;
}
inline ::QueryMode QueryRequest::querymode() const {
  // @@protoc_insertion_point(field_get:QueryRequest.queryMode)
  return _internal_querymode();
}
inline void QueryRequest::set_querymode(::QueryMode value) {
  _internal_set_querymode(value);
  // @@protoc_insertion_point(field_set:QueryRequest.queryMode)
}
inline ::QueryMode QueryRequest::_internal_querymode() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return static_cast<::QueryMode>(_impl_.querymode_);
}
inline void QueryRequest::_internal_set_querymode(::QueryMode value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.querymode_ = value;
}

// string queryContent = 2;
inline void QueryRequest::clear_querycontent() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.querycontent_.ClearToEmpty();
}
inline const std::string& QueryRequest::querycontent() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:QueryRequest.queryContent)
  return _internal_querycontent();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void QueryRequest::set_querycontent(Arg_&& arg,
                                                     Args_... args) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.querycontent_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:QueryRequest.queryContent)
}
inline std::string* QueryRequest::mutable_querycontent() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_querycontent();
  // @@protoc_insertion_point(field_mutable:QueryRequest.queryContent)
  return _s;
}
inline const std::string& QueryRequest::_internal_querycontent() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.querycontent_.Get();
}
inline void QueryRequest::_internal_set_querycontent(const std::string& value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.querycontent_.Set(value, GetArena());
}
inline std::string* QueryRequest::_internal_mutable_querycontent() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _impl_.querycontent_.Mutable( GetArena());
}
inline std::string* QueryRequest::release_querycontent() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  // @@protoc_insertion_point(field_release:QueryRequest.queryContent)
  return _impl_.querycontent_.Release();
}
inline void QueryRequest::set_allocated_querycontent(std::string* value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.querycontent_.SetAllocated(value, GetArena());
  if (::google::protobuf::internal::DebugHardenForceCopyDefaultString() && _impl_.querycontent_.IsDefault()) {
    _impl_.querycontent_.Set("", GetArena());
  }
  // @@protoc_insertion_point(field_set_allocated:QueryRequest.queryContent)
}

// -------------------------------------------------------------------

// QueryResponse

// repeated uint32 docId = 1;
inline int QueryResponse::_internal_docid_size() const {
  return _internal_docid().size();
}
inline int QueryResponse::docid_size() const {
  return _internal_docid_size();
}
inline void QueryResponse::clear_docid() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.docid_.Clear();
}
inline ::uint32_t QueryResponse::docid(int index) const {
  // @@protoc_insertion_point(field_get:QueryResponse.docId)
  return _internal_docid().Get(index);
}
inline void QueryResponse::set_docid(int index, ::uint32_t value) {
  _internal_mutable_docid()->Set(index, value);
  // @@protoc_insertion_point(field_set:QueryResponse.docId)
}
inline void QueryResponse::add_docid(::uint32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _internal_mutable_docid()->Add(value);
  // @@protoc_insertion_point(field_add:QueryResponse.docId)
}
inline const ::google::protobuf::RepeatedField<::uint32_t>& QueryResponse::docid() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:QueryResponse.docId)
  return _internal_docid();
}
inline ::google::protobuf::RepeatedField<::uint32_t>* QueryResponse::mutable_docid()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:QueryResponse.docId)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _internal_mutable_docid();
}
inline const ::google::protobuf::RepeatedField<::uint32_t>&
QueryResponse::_internal_docid() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.docid_;
}
inline ::google::protobuf::RepeatedField<::uint32_t>* QueryResponse::_internal_mutable_docid() {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return &_impl_.docid_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::QueryMode> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::QueryMode>() {
  return ::QueryMode_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // query_2eproto_2epb_2eh
