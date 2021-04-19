// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: table.proto

#include "table.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_table_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Entry_table_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_table_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Row_table_2eproto;
namespace database {
class EntryDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Entry> _instance;
} _Entry_default_instance_;
class RowDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Row> _instance;
} _Row_default_instance_;
class TableDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Table> _instance;
} _Table_default_instance_;
}  // namespace database
static void InitDefaultsscc_info_Entry_table_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::database::_Entry_default_instance_;
    new (ptr) ::database::Entry();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Entry_table_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_Entry_table_2eproto}, {}};

static void InitDefaultsscc_info_Row_table_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::database::_Row_default_instance_;
    new (ptr) ::database::Row();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Row_table_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_Row_table_2eproto}, {
      &scc_info_Entry_table_2eproto.base,}};

static void InitDefaultsscc_info_Table_table_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::database::_Table_default_instance_;
    new (ptr) ::database::Table();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Table_table_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_Table_table_2eproto}, {
      &scc_info_Row_table_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_table_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_table_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_table_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_table_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::database::Entry, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::database::Entry, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::database::Entry, str_),
  PROTOBUF_FIELD_OFFSET(::database::Entry, flt_),
  PROTOBUF_FIELD_OFFSET(::database::Entry, num_),
  PROTOBUF_FIELD_OFFSET(::database::Entry, boolean_),
  0,
  2,
  1,
  3,
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::database::Row, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::database::Row, entries_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::database::Table, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::database::Table, rows_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, sizeof(::database::Entry)},
  { 13, -1, sizeof(::database::Row)},
  { 19, -1, sizeof(::database::Table)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::database::_Entry_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::database::_Row_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::database::_Table_default_instance_),
};

const char descriptor_table_protodef_table_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013table.proto\022\010database\"\?\n\005Entry\022\013\n\003str\030"
  "\001 \001(\t\022\013\n\003flt\030\002 \001(\002\022\013\n\003num\030\003 \001(\003\022\017\n\007boole"
  "an\030\004 \001(\010\"\'\n\003Row\022 \n\007entries\030\001 \003(\0132\017.datab"
  "ase.Entry\"$\n\005Table\022\033\n\004rows\030\001 \003(\0132\r.datab"
  "ase.Row"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_table_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_table_2eproto_sccs[3] = {
  &scc_info_Entry_table_2eproto.base,
  &scc_info_Row_table_2eproto.base,
  &scc_info_Table_table_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_table_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_table_2eproto = {
  false, false, descriptor_table_protodef_table_2eproto, "table.proto", 167,
  &descriptor_table_table_2eproto_once, descriptor_table_table_2eproto_sccs, descriptor_table_table_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_table_2eproto::offsets,
  file_level_metadata_table_2eproto, 3, file_level_enum_descriptors_table_2eproto, file_level_service_descriptors_table_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_table_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_table_2eproto)), true);
namespace database {

// ===================================================================

class Entry::_Internal {
 public:
  using HasBits = decltype(std::declval<Entry>()._has_bits_);
  static void set_has_str(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_flt(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static void set_has_num(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_boolean(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
};

Entry::Entry(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:database.Entry)
}
Entry::Entry(const Entry& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  str_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_str()) {
    str_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_str(), 
      GetArena());
  }
  ::memcpy(&num_, &from.num_,
    static_cast<size_t>(reinterpret_cast<char*>(&boolean_) -
    reinterpret_cast<char*>(&num_)) + sizeof(boolean_));
  // @@protoc_insertion_point(copy_constructor:database.Entry)
}

void Entry::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Entry_table_2eproto.base);
  str_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
      reinterpret_cast<char*>(&num_) - reinterpret_cast<char*>(this)),
      0, static_cast<size_t>(reinterpret_cast<char*>(&boolean_) -
      reinterpret_cast<char*>(&num_)) + sizeof(boolean_));
}

Entry::~Entry() {
  // @@protoc_insertion_point(destructor:database.Entry)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Entry::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  str_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Entry::ArenaDtor(void* object) {
  Entry* _this = reinterpret_cast< Entry* >(object);
  (void)_this;
}
void Entry::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Entry::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Entry& Entry::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Entry_table_2eproto.base);
  return *internal_default_instance();
}


void Entry::Clear() {
// @@protoc_insertion_point(message_clear_start:database.Entry)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    str_.ClearNonDefaultToEmpty();
  }
  if (cached_has_bits & 0x0000000eu) {
    ::memset(&num_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&boolean_) -
        reinterpret_cast<char*>(&num_)) + sizeof(boolean_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Entry::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // optional string str = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_str();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          #ifndef NDEBUG
          ::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "database.Entry.str");
          #endif  // !NDEBUG
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional float flt = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          _Internal::set_has_flt(&has_bits);
          flt_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // optional int64 num = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_num(&has_bits);
          num_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool boolean = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 32)) {
          _Internal::set_has_boolean(&has_bits);
          boolean_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Entry::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:database.Entry)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // optional string str = 1;
  if (cached_has_bits & 0x00000001u) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::VerifyUTF8StringNamedField(
      this->_internal_str().data(), static_cast<int>(this->_internal_str().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SERIALIZE,
      "database.Entry.str");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_str(), target);
  }

  // optional float flt = 2;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->_internal_flt(), target);
  }

  // optional int64 num = 3;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(3, this->_internal_num(), target);
  }

  // optional bool boolean = 4;
  if (cached_has_bits & 0x00000008u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(4, this->_internal_boolean(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:database.Entry)
  return target;
}

size_t Entry::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:database.Entry)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    // optional string str = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_str());
    }

    // optional int64 num = 3;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
          this->_internal_num());
    }

    // optional float flt = 2;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 + 4;
    }

    // optional bool boolean = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 + 1;
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Entry::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:database.Entry)
  GOOGLE_DCHECK_NE(&from, this);
  const Entry* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Entry>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:database.Entry)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:database.Entry)
    MergeFrom(*source);
  }
}

void Entry::MergeFrom(const Entry& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:database.Entry)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_set_str(from._internal_str());
    }
    if (cached_has_bits & 0x00000002u) {
      num_ = from.num_;
    }
    if (cached_has_bits & 0x00000004u) {
      flt_ = from.flt_;
    }
    if (cached_has_bits & 0x00000008u) {
      boolean_ = from.boolean_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Entry::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:database.Entry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Entry::CopyFrom(const Entry& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:database.Entry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Entry::IsInitialized() const {
  return true;
}

void Entry::InternalSwap(Entry* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  str_.Swap(&other->str_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Entry, boolean_)
      + sizeof(Entry::boolean_)
      - PROTOBUF_FIELD_OFFSET(Entry, num_)>(
          reinterpret_cast<char*>(&num_),
          reinterpret_cast<char*>(&other->num_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Entry::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class Row::_Internal {
 public:
};

Row::Row(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  entries_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:database.Row)
}
Row::Row(const Row& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      entries_(from.entries_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:database.Row)
}

void Row::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Row_table_2eproto.base);
}

Row::~Row() {
  // @@protoc_insertion_point(destructor:database.Row)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Row::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Row::ArenaDtor(void* object) {
  Row* _this = reinterpret_cast< Row* >(object);
  (void)_this;
}
void Row::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Row::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Row& Row::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Row_table_2eproto.base);
  return *internal_default_instance();
}


void Row::Clear() {
// @@protoc_insertion_point(message_clear_start:database.Row)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  entries_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Row::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .database.Entry entries = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_entries(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Row::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:database.Row)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .database.Entry entries = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_entries_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_entries(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:database.Row)
  return target;
}

size_t Row::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:database.Row)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .database.Entry entries = 1;
  total_size += 1UL * this->_internal_entries_size();
  for (const auto& msg : this->entries_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Row::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:database.Row)
  GOOGLE_DCHECK_NE(&from, this);
  const Row* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Row>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:database.Row)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:database.Row)
    MergeFrom(*source);
  }
}

void Row::MergeFrom(const Row& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:database.Row)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  entries_.MergeFrom(from.entries_);
}

void Row::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:database.Row)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Row::CopyFrom(const Row& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:database.Row)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Row::IsInitialized() const {
  return true;
}

void Row::InternalSwap(Row* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  entries_.InternalSwap(&other->entries_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Row::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class Table::_Internal {
 public:
};

Table::Table(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  rows_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:database.Table)
}
Table::Table(const Table& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      rows_(from.rows_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:database.Table)
}

void Table::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Table_table_2eproto.base);
}

Table::~Table() {
  // @@protoc_insertion_point(destructor:database.Table)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void Table::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void Table::ArenaDtor(void* object) {
  Table* _this = reinterpret_cast< Table* >(object);
  (void)_this;
}
void Table::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Table::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Table& Table::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Table_table_2eproto.base);
  return *internal_default_instance();
}


void Table::Clear() {
// @@protoc_insertion_point(message_clear_start:database.Table)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  rows_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Table::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .database.Row rows = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_rows(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* Table::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:database.Table)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .database.Row rows = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_rows_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_rows(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:database.Table)
  return target;
}

size_t Table::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:database.Table)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .database.Row rows = 1;
  total_size += 1UL * this->_internal_rows_size();
  for (const auto& msg : this->rows_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Table::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:database.Table)
  GOOGLE_DCHECK_NE(&from, this);
  const Table* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Table>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:database.Table)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:database.Table)
    MergeFrom(*source);
  }
}

void Table::MergeFrom(const Table& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:database.Table)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  rows_.MergeFrom(from.rows_);
}

void Table::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:database.Table)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Table::CopyFrom(const Table& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:database.Table)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Table::IsInitialized() const {
  return true;
}

void Table::InternalSwap(Table* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  rows_.InternalSwap(&other->rows_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Table::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace database
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::database::Entry* Arena::CreateMaybeMessage< ::database::Entry >(Arena* arena) {
  return Arena::CreateMessageInternal< ::database::Entry >(arena);
}
template<> PROTOBUF_NOINLINE ::database::Row* Arena::CreateMaybeMessage< ::database::Row >(Arena* arena) {
  return Arena::CreateMessageInternal< ::database::Row >(arena);
}
template<> PROTOBUF_NOINLINE ::database::Table* Arena::CreateMaybeMessage< ::database::Table >(Arena* arena) {
  return Arena::CreateMessageInternal< ::database::Table >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>