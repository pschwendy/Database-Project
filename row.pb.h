// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: row.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_row_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_row_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_row_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_row_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_row_2eproto;
namespace database {
class Entry;
class EntryDefaultTypeInternal;
extern EntryDefaultTypeInternal _Entry_default_instance_;
class Row;
class RowDefaultTypeInternal;
extern RowDefaultTypeInternal _Row_default_instance_;
}  // namespace database
PROTOBUF_NAMESPACE_OPEN
template<> ::database::Entry* Arena::CreateMaybeMessage<::database::Entry>(Arena*);
template<> ::database::Row* Arena::CreateMaybeMessage<::database::Row>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace database {

// ===================================================================

class Entry PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:database.Entry) */ {
 public:
  inline Entry() : Entry(nullptr) {}
  virtual ~Entry();

  Entry(const Entry& from);
  Entry(Entry&& from) noexcept
    : Entry() {
    *this = ::std::move(from);
  }

  inline Entry& operator=(const Entry& from) {
    CopyFrom(from);
    return *this;
  }
  inline Entry& operator=(Entry&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Entry& default_instance();

  static inline const Entry* internal_default_instance() {
    return reinterpret_cast<const Entry*>(
               &_Entry_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Entry& a, Entry& b) {
    a.Swap(&b);
  }
  inline void Swap(Entry* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Entry* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Entry* New() const final {
    return CreateMaybeMessage<Entry>(nullptr);
  }

  Entry* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Entry>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Entry& from);
  void MergeFrom(const Entry& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Entry* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "database.Entry";
  }
  protected:
  explicit Entry(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_row_2eproto);
    return ::descriptor_table_row_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kStrFieldNumber = 1,
    kNumFieldNumber = 3,
    kFltFieldNumber = 2,
    kBooleanFieldNumber = 4,
  };
  // optional string str = 1;
  bool has_str() const;
  private:
  bool _internal_has_str() const;
  public:
  void clear_str();
  const std::string& str() const;
  void set_str(const std::string& value);
  void set_str(std::string&& value);
  void set_str(const char* value);
  void set_str(const char* value, size_t size);
  std::string* mutable_str();
  std::string* release_str();
  void set_allocated_str(std::string* str);
  private:
  const std::string& _internal_str() const;
  void _internal_set_str(const std::string& value);
  std::string* _internal_mutable_str();
  public:

  // optional int64 num = 3;
  bool has_num() const;
  private:
  bool _internal_has_num() const;
  public:
  void clear_num();
  ::PROTOBUF_NAMESPACE_ID::int64 num() const;
  void set_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_num() const;
  void _internal_set_num(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // optional float flt = 2;
  bool has_flt() const;
  private:
  bool _internal_has_flt() const;
  public:
  void clear_flt();
  float flt() const;
  void set_flt(float value);
  private:
  float _internal_flt() const;
  void _internal_set_flt(float value);
  public:

  // optional bool boolean = 4;
  bool has_boolean() const;
  private:
  bool _internal_has_boolean() const;
  public:
  void clear_boolean();
  bool boolean() const;
  void set_boolean(bool value);
  private:
  bool _internal_boolean() const;
  void _internal_set_boolean(bool value);
  public:

  // @@protoc_insertion_point(class_scope:database.Entry)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr str_;
  ::PROTOBUF_NAMESPACE_ID::int64 num_;
  float flt_;
  bool boolean_;
  friend struct ::TableStruct_row_2eproto;
};
// -------------------------------------------------------------------

class Row PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:database.Row) */ {
 public:
  inline Row() : Row(nullptr) {}
  virtual ~Row();

  Row(const Row& from);
  Row(Row&& from) noexcept
    : Row() {
    *this = ::std::move(from);
  }

  inline Row& operator=(const Row& from) {
    CopyFrom(from);
    return *this;
  }
  inline Row& operator=(Row&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Row& default_instance();

  static inline const Row* internal_default_instance() {
    return reinterpret_cast<const Row*>(
               &_Row_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Row& a, Row& b) {
    a.Swap(&b);
  }
  inline void Swap(Row* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Row* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Row* New() const final {
    return CreateMaybeMessage<Row>(nullptr);
  }

  Row* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Row>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Row& from);
  void MergeFrom(const Row& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Row* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "database.Row";
  }
  protected:
  explicit Row(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_row_2eproto);
    return ::descriptor_table_row_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEntriesFieldNumber = 1,
  };
  // repeated .database.Entry entries = 1;
  int entries_size() const;
  private:
  int _internal_entries_size() const;
  public:
  void clear_entries();
  ::database::Entry* mutable_entries(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::database::Entry >*
      mutable_entries();
  private:
  const ::database::Entry& _internal_entries(int index) const;
  ::database::Entry* _internal_add_entries();
  public:
  const ::database::Entry& entries(int index) const;
  ::database::Entry* add_entries();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::database::Entry >&
      entries() const;

  // @@protoc_insertion_point(class_scope:database.Row)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::database::Entry > entries_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_row_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Entry

// optional string str = 1;
inline bool Entry::_internal_has_str() const {
  bool value = (_has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool Entry::has_str() const {
  return _internal_has_str();
}
inline void Entry::clear_str() {
  str_.ClearToEmpty();
  _has_bits_[0] &= ~0x00000001u;
}
inline const std::string& Entry::str() const {
  // @@protoc_insertion_point(field_get:database.Entry.str)
  return _internal_str();
}
inline void Entry::set_str(const std::string& value) {
  _internal_set_str(value);
  // @@protoc_insertion_point(field_set:database.Entry.str)
}
inline std::string* Entry::mutable_str() {
  // @@protoc_insertion_point(field_mutable:database.Entry.str)
  return _internal_mutable_str();
}
inline const std::string& Entry::_internal_str() const {
  return str_.Get();
}
inline void Entry::_internal_set_str(const std::string& value) {
  _has_bits_[0] |= 0x00000001u;
  str_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void Entry::set_str(std::string&& value) {
  _has_bits_[0] |= 0x00000001u;
  str_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:database.Entry.str)
}
inline void Entry::set_str(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  _has_bits_[0] |= 0x00000001u;
  str_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:database.Entry.str)
}
inline void Entry::set_str(const char* value,
    size_t size) {
  _has_bits_[0] |= 0x00000001u;
  str_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:database.Entry.str)
}
inline std::string* Entry::_internal_mutable_str() {
  _has_bits_[0] |= 0x00000001u;
  return str_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* Entry::release_str() {
  // @@protoc_insertion_point(field_release:database.Entry.str)
  if (!_internal_has_str()) {
    return nullptr;
  }
  _has_bits_[0] &= ~0x00000001u;
  return str_.ReleaseNonDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void Entry::set_allocated_str(std::string* str) {
  if (str != nullptr) {
    _has_bits_[0] |= 0x00000001u;
  } else {
    _has_bits_[0] &= ~0x00000001u;
  }
  str_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), str,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:database.Entry.str)
}

// optional float flt = 2;
inline bool Entry::_internal_has_flt() const {
  bool value = (_has_bits_[0] & 0x00000004u) != 0;
  return value;
}
inline bool Entry::has_flt() const {
  return _internal_has_flt();
}
inline void Entry::clear_flt() {
  flt_ = 0;
  _has_bits_[0] &= ~0x00000004u;
}
inline float Entry::_internal_flt() const {
  return flt_;
}
inline float Entry::flt() const {
  // @@protoc_insertion_point(field_get:database.Entry.flt)
  return _internal_flt();
}
inline void Entry::_internal_set_flt(float value) {
  _has_bits_[0] |= 0x00000004u;
  flt_ = value;
}
inline void Entry::set_flt(float value) {
  _internal_set_flt(value);
  // @@protoc_insertion_point(field_set:database.Entry.flt)
}

// optional int64 num = 3;
inline bool Entry::_internal_has_num() const {
  bool value = (_has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool Entry::has_num() const {
  return _internal_has_num();
}
inline void Entry::clear_num() {
  num_ = PROTOBUF_LONGLONG(0);
  _has_bits_[0] &= ~0x00000002u;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Entry::_internal_num() const {
  return num_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Entry::num() const {
  // @@protoc_insertion_point(field_get:database.Entry.num)
  return _internal_num();
}
inline void Entry::_internal_set_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _has_bits_[0] |= 0x00000002u;
  num_ = value;
}
inline void Entry::set_num(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_num(value);
  // @@protoc_insertion_point(field_set:database.Entry.num)
}

// optional bool boolean = 4;
inline bool Entry::_internal_has_boolean() const {
  bool value = (_has_bits_[0] & 0x00000008u) != 0;
  return value;
}
inline bool Entry::has_boolean() const {
  return _internal_has_boolean();
}
inline void Entry::clear_boolean() {
  boolean_ = false;
  _has_bits_[0] &= ~0x00000008u;
}
inline bool Entry::_internal_boolean() const {
  return boolean_;
}
inline bool Entry::boolean() const {
  // @@protoc_insertion_point(field_get:database.Entry.boolean)
  return _internal_boolean();
}
inline void Entry::_internal_set_boolean(bool value) {
  _has_bits_[0] |= 0x00000008u;
  boolean_ = value;
}
inline void Entry::set_boolean(bool value) {
  _internal_set_boolean(value);
  // @@protoc_insertion_point(field_set:database.Entry.boolean)
}

// -------------------------------------------------------------------

// Row

// repeated .database.Entry entries = 1;
inline int Row::_internal_entries_size() const {
  return entries_.size();
}
inline int Row::entries_size() const {
  return _internal_entries_size();
}
inline void Row::clear_entries() {
  entries_.Clear();
}
inline ::database::Entry* Row::mutable_entries(int index) {
  // @@protoc_insertion_point(field_mutable:database.Row.entries)
  return entries_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::database::Entry >*
Row::mutable_entries() {
  // @@protoc_insertion_point(field_mutable_list:database.Row.entries)
  return &entries_;
}
inline const ::database::Entry& Row::_internal_entries(int index) const {
  return entries_.Get(index);
}
inline const ::database::Entry& Row::entries(int index) const {
  // @@protoc_insertion_point(field_get:database.Row.entries)
  return _internal_entries(index);
}
inline ::database::Entry* Row::_internal_add_entries() {
  return entries_.Add();
}
inline ::database::Entry* Row::add_entries() {
  // @@protoc_insertion_point(field_add:database.Row.entries)
  return _internal_add_entries();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::database::Entry >&
Row::entries() const {
  // @@protoc_insertion_point(field_list:database.Row.entries)
  return entries_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace database

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_row_2eproto
