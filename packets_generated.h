// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_PACKETS_SPACPP_PROTOCOL_H_
#define FLATBUFFERS_GENERATED_PACKETS_SPACPP_PROTOCOL_H_

#include "flatbuffers/flatbuffers.h"

namespace spacpp {
namespace protocol {

struct vec2f;

struct RespawnRequest;
struct RespawnRequestBuilder;

struct UserInputs;
struct UserInputsBuilder;

struct Death;
struct DeathBuilder;

struct PlayerSnapshot;
struct PlayerSnapshotBuilder;

struct PlayerCellSnapshot;
struct PlayerCellSnapshotBuilder;

struct FoodCellSnapshot;
struct FoodCellSnapshotBuilder;

struct CellDelta;

struct WorldUpdate;
struct WorldUpdateBuilder;

struct Packet;
struct PacketBuilder;

enum EntitySnapshot {
  EntitySnapshot_NONE = 0,
  EntitySnapshot_PlayerSnapshot = 1,
  EntitySnapshot_PlayerCellSnapshot = 2,
  EntitySnapshot_FoodCellSnapshot = 3,
  EntitySnapshot_MIN = EntitySnapshot_NONE,
  EntitySnapshot_MAX = EntitySnapshot_FoodCellSnapshot
};

inline const EntitySnapshot (&EnumValuesEntitySnapshot())[4] {
  static const EntitySnapshot values[] = {
    EntitySnapshot_NONE,
    EntitySnapshot_PlayerSnapshot,
    EntitySnapshot_PlayerCellSnapshot,
    EntitySnapshot_FoodCellSnapshot
  };
  return values;
}

inline const char * const *EnumNamesEntitySnapshot() {
  static const char * const names[5] = {
    "NONE",
    "PlayerSnapshot",
    "PlayerCellSnapshot",
    "FoodCellSnapshot",
    nullptr
  };
  return names;
}

inline const char *EnumNameEntitySnapshot(EntitySnapshot e) {
  if (flatbuffers::IsOutRange(e, EntitySnapshot_NONE, EntitySnapshot_FoodCellSnapshot)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesEntitySnapshot()[index];
}

template<typename T> struct EntitySnapshotTraits {
  static const EntitySnapshot enum_value = EntitySnapshot_NONE;
};

template<> struct EntitySnapshotTraits<spacpp::protocol::PlayerSnapshot> {
  static const EntitySnapshot enum_value = EntitySnapshot_PlayerSnapshot;
};

template<> struct EntitySnapshotTraits<spacpp::protocol::PlayerCellSnapshot> {
  static const EntitySnapshot enum_value = EntitySnapshot_PlayerCellSnapshot;
};

template<> struct EntitySnapshotTraits<spacpp::protocol::FoodCellSnapshot> {
  static const EntitySnapshot enum_value = EntitySnapshot_FoodCellSnapshot;
};

bool VerifyEntitySnapshot(flatbuffers::Verifier &verifier, const void *obj, EntitySnapshot type);
bool VerifyEntitySnapshotVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

enum Message {
  Message_NONE = 0,
  Message_RespawnRequest = 1,
  Message_UserInputs = 2,
  Message_Death = 3,
  Message_WorldUpdate = 4,
  Message_MIN = Message_NONE,
  Message_MAX = Message_WorldUpdate
};

inline const Message (&EnumValuesMessage())[5] {
  static const Message values[] = {
    Message_NONE,
    Message_RespawnRequest,
    Message_UserInputs,
    Message_Death,
    Message_WorldUpdate
  };
  return values;
}

inline const char * const *EnumNamesMessage() {
  static const char * const names[6] = {
    "NONE",
    "RespawnRequest",
    "UserInputs",
    "Death",
    "WorldUpdate",
    nullptr
  };
  return names;
}

inline const char *EnumNameMessage(Message e) {
  if (flatbuffers::IsOutRange(e, Message_NONE, Message_WorldUpdate)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesMessage()[index];
}

template<typename T> struct MessageTraits {
  static const Message enum_value = Message_NONE;
};

template<> struct MessageTraits<spacpp::protocol::RespawnRequest> {
  static const Message enum_value = Message_RespawnRequest;
};

template<> struct MessageTraits<spacpp::protocol::UserInputs> {
  static const Message enum_value = Message_UserInputs;
};

template<> struct MessageTraits<spacpp::protocol::Death> {
  static const Message enum_value = Message_Death;
};

template<> struct MessageTraits<spacpp::protocol::WorldUpdate> {
  static const Message enum_value = Message_WorldUpdate;
};

bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type);
bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) vec2f FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;

 public:
  vec2f() {
    memset(static_cast<void *>(this), 0, sizeof(vec2f));
  }
  vec2f(float _x, float _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(vec2f, 8);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) CellDelta FLATBUFFERS_FINAL_CLASS {
 private:
  uint32_t id_;
  spacpp::protocol::vec2f position_;
  spacpp::protocol::vec2f velocity_;
  float mass_;

 public:
  CellDelta() {
    memset(static_cast<void *>(this), 0, sizeof(CellDelta));
  }
  CellDelta(uint32_t _id, const spacpp::protocol::vec2f &_position, const spacpp::protocol::vec2f &_velocity, float _mass)
      : id_(flatbuffers::EndianScalar(_id)),
        position_(_position),
        velocity_(_velocity),
        mass_(flatbuffers::EndianScalar(_mass)) {
  }
  uint32_t id() const {
    return flatbuffers::EndianScalar(id_);
  }
  bool KeyCompareLessThan(const CellDelta *o) const {
    return id() < o->id();
  }
  int KeyCompareWithValue(uint32_t val) const {
    return static_cast<int>(id() > val) - static_cast<int>(id() < val);
  }
  const spacpp::protocol::vec2f &position() const {
    return position_;
  }
  const spacpp::protocol::vec2f &velocity() const {
    return velocity_;
  }
  float mass() const {
    return flatbuffers::EndianScalar(mass_);
  }
};
FLATBUFFERS_STRUCT_END(CellDelta, 24);

struct RespawnRequest FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RespawnRequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct RespawnRequestBuilder {
  typedef RespawnRequest Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(RespawnRequest::VT_NAME, name);
  }
  explicit RespawnRequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<RespawnRequest> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RespawnRequest>(end);
    return o;
  }
};

inline flatbuffers::Offset<RespawnRequest> CreateRespawnRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  RespawnRequestBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<RespawnRequest> CreateRespawnRequestDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return spacpp::protocol::CreateRespawnRequest(
      _fbb,
      name__);
}

struct UserInputs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef UserInputsBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_MOUSE = 4,
    VT_SPLIT = 6,
    VT_EJECT = 8
  };
  const spacpp::protocol::vec2f *mouse() const {
    return GetStruct<const spacpp::protocol::vec2f *>(VT_MOUSE);
  }
  bool split() const {
    return GetField<uint8_t>(VT_SPLIT, 0) != 0;
  }
  bool eject() const {
    return GetField<uint8_t>(VT_EJECT, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<spacpp::protocol::vec2f>(verifier, VT_MOUSE) &&
           VerifyField<uint8_t>(verifier, VT_SPLIT) &&
           VerifyField<uint8_t>(verifier, VT_EJECT) &&
           verifier.EndTable();
  }
};

struct UserInputsBuilder {
  typedef UserInputs Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_mouse(const spacpp::protocol::vec2f *mouse) {
    fbb_.AddStruct(UserInputs::VT_MOUSE, mouse);
  }
  void add_split(bool split) {
    fbb_.AddElement<uint8_t>(UserInputs::VT_SPLIT, static_cast<uint8_t>(split), 0);
  }
  void add_eject(bool eject) {
    fbb_.AddElement<uint8_t>(UserInputs::VT_EJECT, static_cast<uint8_t>(eject), 0);
  }
  explicit UserInputsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<UserInputs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<UserInputs>(end);
    return o;
  }
};

inline flatbuffers::Offset<UserInputs> CreateUserInputs(
    flatbuffers::FlatBufferBuilder &_fbb,
    const spacpp::protocol::vec2f *mouse = 0,
    bool split = false,
    bool eject = false) {
  UserInputsBuilder builder_(_fbb);
  builder_.add_mouse(mouse);
  builder_.add_eject(eject);
  builder_.add_split(split);
  return builder_.Finish();
}

struct Death FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef DeathBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ALIVE = 4
  };
  int64_t alive() const {
    return GetField<int64_t>(VT_ALIVE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int64_t>(verifier, VT_ALIVE) &&
           verifier.EndTable();
  }
};

struct DeathBuilder {
  typedef Death Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_alive(int64_t alive) {
    fbb_.AddElement<int64_t>(Death::VT_ALIVE, alive, 0);
  }
  explicit DeathBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Death> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Death>(end);
    return o;
  }
};

inline flatbuffers::Offset<Death> CreateDeath(
    flatbuffers::FlatBufferBuilder &_fbb,
    int64_t alive = 0) {
  DeathBuilder builder_(_fbb);
  builder_.add_alive(alive);
  return builder_.Finish();
}

struct PlayerSnapshot FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlayerSnapshotBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_NAME = 6
  };
  uint32_t id() const {
    return GetField<uint32_t>(VT_ID, 0);
  }
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_ID) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct PlayerSnapshotBuilder {
  typedef PlayerSnapshot Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint32_t id) {
    fbb_.AddElement<uint32_t>(PlayerSnapshot::VT_ID, id, 0);
  }
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(PlayerSnapshot::VT_NAME, name);
  }
  explicit PlayerSnapshotBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<PlayerSnapshot> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerSnapshot>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerSnapshot> CreatePlayerSnapshot(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t id = 0,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  PlayerSnapshotBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_id(id);
  return builder_.Finish();
}

inline flatbuffers::Offset<PlayerSnapshot> CreatePlayerSnapshotDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t id = 0,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return spacpp::protocol::CreatePlayerSnapshot(
      _fbb,
      id,
      name__);
}

struct PlayerCellSnapshot FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PlayerCellSnapshotBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_OWNER = 6
  };
  uint32_t id() const {
    return GetField<uint32_t>(VT_ID, 0);
  }
  uint32_t owner() const {
    return GetField<uint32_t>(VT_OWNER, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_ID) &&
           VerifyField<uint32_t>(verifier, VT_OWNER) &&
           verifier.EndTable();
  }
};

struct PlayerCellSnapshotBuilder {
  typedef PlayerCellSnapshot Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint32_t id) {
    fbb_.AddElement<uint32_t>(PlayerCellSnapshot::VT_ID, id, 0);
  }
  void add_owner(uint32_t owner) {
    fbb_.AddElement<uint32_t>(PlayerCellSnapshot::VT_OWNER, owner, 0);
  }
  explicit PlayerCellSnapshotBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<PlayerCellSnapshot> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PlayerCellSnapshot>(end);
    return o;
  }
};

inline flatbuffers::Offset<PlayerCellSnapshot> CreatePlayerCellSnapshot(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t id = 0,
    uint32_t owner = 0) {
  PlayerCellSnapshotBuilder builder_(_fbb);
  builder_.add_owner(owner);
  builder_.add_id(id);
  return builder_.Finish();
}

struct FoodCellSnapshot FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef FoodCellSnapshotBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_POSITION = 6,
    VT_MASS = 8
  };
  uint32_t id() const {
    return GetField<uint32_t>(VT_ID, 0);
  }
  const spacpp::protocol::vec2f *position() const {
    return GetStruct<const spacpp::protocol::vec2f *>(VT_POSITION);
  }
  float mass() const {
    return GetField<float>(VT_MASS, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_ID) &&
           VerifyField<spacpp::protocol::vec2f>(verifier, VT_POSITION) &&
           VerifyField<float>(verifier, VT_MASS) &&
           verifier.EndTable();
  }
};

struct FoodCellSnapshotBuilder {
  typedef FoodCellSnapshot Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(uint32_t id) {
    fbb_.AddElement<uint32_t>(FoodCellSnapshot::VT_ID, id, 0);
  }
  void add_position(const spacpp::protocol::vec2f *position) {
    fbb_.AddStruct(FoodCellSnapshot::VT_POSITION, position);
  }
  void add_mass(float mass) {
    fbb_.AddElement<float>(FoodCellSnapshot::VT_MASS, mass, 0.0f);
  }
  explicit FoodCellSnapshotBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<FoodCellSnapshot> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<FoodCellSnapshot>(end);
    return o;
  }
};

inline flatbuffers::Offset<FoodCellSnapshot> CreateFoodCellSnapshot(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t id = 0,
    const spacpp::protocol::vec2f *position = 0,
    float mass = 0.0f) {
  FoodCellSnapshotBuilder builder_(_fbb);
  builder_.add_mass(mass);
  builder_.add_position(position);
  builder_.add_id(id);
  return builder_.Finish();
}

struct WorldUpdate FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef WorldUpdateBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_DELETE_ = 4,
    VT_SNAPSHOTS_TYPE = 6,
    VT_SNAPSHOTS = 8,
    VT_DELTAS = 10
  };
  const flatbuffers::Vector<uint32_t> *delete_() const {
    return GetPointer<const flatbuffers::Vector<uint32_t> *>(VT_DELETE_);
  }
  const flatbuffers::Vector<uint8_t> *snapshots_type() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_SNAPSHOTS_TYPE);
  }
  const flatbuffers::Vector<flatbuffers::Offset<void>> *snapshots() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<void>> *>(VT_SNAPSHOTS);
  }
  const flatbuffers::Vector<const spacpp::protocol::CellDelta *> *deltas() const {
    return GetPointer<const flatbuffers::Vector<const spacpp::protocol::CellDelta *> *>(VT_DELTAS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_DELETE_) &&
           verifier.VerifyVector(delete_()) &&
           VerifyOffset(verifier, VT_SNAPSHOTS_TYPE) &&
           verifier.VerifyVector(snapshots_type()) &&
           VerifyOffset(verifier, VT_SNAPSHOTS) &&
           verifier.VerifyVector(snapshots()) &&
           VerifyEntitySnapshotVector(verifier, snapshots(), snapshots_type()) &&
           VerifyOffset(verifier, VT_DELTAS) &&
           verifier.VerifyVector(deltas()) &&
           verifier.EndTable();
  }
};

struct WorldUpdateBuilder {
  typedef WorldUpdate Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_delete_(flatbuffers::Offset<flatbuffers::Vector<uint32_t>> delete_) {
    fbb_.AddOffset(WorldUpdate::VT_DELETE_, delete_);
  }
  void add_snapshots_type(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> snapshots_type) {
    fbb_.AddOffset(WorldUpdate::VT_SNAPSHOTS_TYPE, snapshots_type);
  }
  void add_snapshots(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<void>>> snapshots) {
    fbb_.AddOffset(WorldUpdate::VT_SNAPSHOTS, snapshots);
  }
  void add_deltas(flatbuffers::Offset<flatbuffers::Vector<const spacpp::protocol::CellDelta *>> deltas) {
    fbb_.AddOffset(WorldUpdate::VT_DELTAS, deltas);
  }
  explicit WorldUpdateBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<WorldUpdate> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<WorldUpdate>(end);
    return o;
  }
};

inline flatbuffers::Offset<WorldUpdate> CreateWorldUpdate(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<uint32_t>> delete_ = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> snapshots_type = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<void>>> snapshots = 0,
    flatbuffers::Offset<flatbuffers::Vector<const spacpp::protocol::CellDelta *>> deltas = 0) {
  WorldUpdateBuilder builder_(_fbb);
  builder_.add_deltas(deltas);
  builder_.add_snapshots(snapshots);
  builder_.add_snapshots_type(snapshots_type);
  builder_.add_delete_(delete_);
  return builder_.Finish();
}

inline flatbuffers::Offset<WorldUpdate> CreateWorldUpdateDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<uint32_t> *delete_ = nullptr,
    const std::vector<uint8_t> *snapshots_type = nullptr,
    const std::vector<flatbuffers::Offset<void>> *snapshots = nullptr,
    std::vector<spacpp::protocol::CellDelta> *deltas = nullptr) {
  auto delete___ = delete_ ? _fbb.CreateVector<uint32_t>(*delete_) : 0;
  auto snapshots_type__ = snapshots_type ? _fbb.CreateVector<uint8_t>(*snapshots_type) : 0;
  auto snapshots__ = snapshots ? _fbb.CreateVector<flatbuffers::Offset<void>>(*snapshots) : 0;
  auto deltas__ = deltas ? _fbb.CreateVectorOfSortedStructs<spacpp::protocol::CellDelta>(deltas) : 0;
  return spacpp::protocol::CreateWorldUpdate(
      _fbb,
      delete___,
      snapshots_type__,
      snapshots__,
      deltas__);
}

struct Packet FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef PacketBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_TIMESTAMP = 4,
    VT_MESSAGE_TYPE = 6,
    VT_MESSAGE = 8
  };
  uint64_t timestamp() const {
    return GetField<uint64_t>(VT_TIMESTAMP, 0);
  }
  spacpp::protocol::Message message_type() const {
    return static_cast<spacpp::protocol::Message>(GetField<uint8_t>(VT_MESSAGE_TYPE, 0));
  }
  const void *message() const {
    return GetPointer<const void *>(VT_MESSAGE);
  }
  template<typename T> const T *message_as() const;
  const spacpp::protocol::RespawnRequest *message_as_RespawnRequest() const {
    return message_type() == spacpp::protocol::Message_RespawnRequest ? static_cast<const spacpp::protocol::RespawnRequest *>(message()) : nullptr;
  }
  const spacpp::protocol::UserInputs *message_as_UserInputs() const {
    return message_type() == spacpp::protocol::Message_UserInputs ? static_cast<const spacpp::protocol::UserInputs *>(message()) : nullptr;
  }
  const spacpp::protocol::Death *message_as_Death() const {
    return message_type() == spacpp::protocol::Message_Death ? static_cast<const spacpp::protocol::Death *>(message()) : nullptr;
  }
  const spacpp::protocol::WorldUpdate *message_as_WorldUpdate() const {
    return message_type() == spacpp::protocol::Message_WorldUpdate ? static_cast<const spacpp::protocol::WorldUpdate *>(message()) : nullptr;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint64_t>(verifier, VT_TIMESTAMP) &&
           VerifyField<uint8_t>(verifier, VT_MESSAGE_TYPE) &&
           VerifyOffset(verifier, VT_MESSAGE) &&
           VerifyMessage(verifier, message(), message_type()) &&
           verifier.EndTable();
  }
};

template<> inline const spacpp::protocol::RespawnRequest *Packet::message_as<spacpp::protocol::RespawnRequest>() const {
  return message_as_RespawnRequest();
}

template<> inline const spacpp::protocol::UserInputs *Packet::message_as<spacpp::protocol::UserInputs>() const {
  return message_as_UserInputs();
}

template<> inline const spacpp::protocol::Death *Packet::message_as<spacpp::protocol::Death>() const {
  return message_as_Death();
}

template<> inline const spacpp::protocol::WorldUpdate *Packet::message_as<spacpp::protocol::WorldUpdate>() const {
  return message_as_WorldUpdate();
}

struct PacketBuilder {
  typedef Packet Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_timestamp(uint64_t timestamp) {
    fbb_.AddElement<uint64_t>(Packet::VT_TIMESTAMP, timestamp, 0);
  }
  void add_message_type(spacpp::protocol::Message message_type) {
    fbb_.AddElement<uint8_t>(Packet::VT_MESSAGE_TYPE, static_cast<uint8_t>(message_type), 0);
  }
  void add_message(flatbuffers::Offset<void> message) {
    fbb_.AddOffset(Packet::VT_MESSAGE, message);
  }
  explicit PacketBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Packet> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Packet>(end);
    return o;
  }
};

inline flatbuffers::Offset<Packet> CreatePacket(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint64_t timestamp = 0,
    spacpp::protocol::Message message_type = spacpp::protocol::Message_NONE,
    flatbuffers::Offset<void> message = 0) {
  PacketBuilder builder_(_fbb);
  builder_.add_timestamp(timestamp);
  builder_.add_message(message);
  builder_.add_message_type(message_type);
  return builder_.Finish();
}

inline bool VerifyEntitySnapshot(flatbuffers::Verifier &verifier, const void *obj, EntitySnapshot type) {
  switch (type) {
    case EntitySnapshot_NONE: {
      return true;
    }
    case EntitySnapshot_PlayerSnapshot: {
      auto ptr = reinterpret_cast<const spacpp::protocol::PlayerSnapshot *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case EntitySnapshot_PlayerCellSnapshot: {
      auto ptr = reinterpret_cast<const spacpp::protocol::PlayerCellSnapshot *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case EntitySnapshot_FoodCellSnapshot: {
      auto ptr = reinterpret_cast<const spacpp::protocol::FoodCellSnapshot *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyEntitySnapshotVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyEntitySnapshot(
        verifier,  values->Get(i), types->GetEnum<EntitySnapshot>(i))) {
      return false;
    }
  }
  return true;
}

inline bool VerifyMessage(flatbuffers::Verifier &verifier, const void *obj, Message type) {
  switch (type) {
    case Message_NONE: {
      return true;
    }
    case Message_RespawnRequest: {
      auto ptr = reinterpret_cast<const spacpp::protocol::RespawnRequest *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_UserInputs: {
      auto ptr = reinterpret_cast<const spacpp::protocol::UserInputs *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_Death: {
      auto ptr = reinterpret_cast<const spacpp::protocol::Death *>(obj);
      return verifier.VerifyTable(ptr);
    }
    case Message_WorldUpdate: {
      auto ptr = reinterpret_cast<const spacpp::protocol::WorldUpdate *>(obj);
      return verifier.VerifyTable(ptr);
    }
    default: return true;
  }
}

inline bool VerifyMessageVector(flatbuffers::Verifier &verifier, const flatbuffers::Vector<flatbuffers::Offset<void>> *values, const flatbuffers::Vector<uint8_t> *types) {
  if (!values || !types) return !values && !types;
  if (values->size() != types->size()) return false;
  for (flatbuffers::uoffset_t i = 0; i < values->size(); ++i) {
    if (!VerifyMessage(
        verifier,  values->Get(i), types->GetEnum<Message>(i))) {
      return false;
    }
  }
  return true;
}

inline const spacpp::protocol::Packet *GetPacket(const void *buf) {
  return flatbuffers::GetRoot<spacpp::protocol::Packet>(buf);
}

inline const spacpp::protocol::Packet *GetSizePrefixedPacket(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<spacpp::protocol::Packet>(buf);
}

inline bool VerifyPacketBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<spacpp::protocol::Packet>(nullptr);
}

inline bool VerifySizePrefixedPacketBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<spacpp::protocol::Packet>(nullptr);
}

inline void FinishPacketBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<spacpp::protocol::Packet> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedPacketBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<spacpp::protocol::Packet> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace protocol
}  // namespace spacpp

#endif  // FLATBUFFERS_GENERATED_PACKETS_SPACPP_PROTOCOL_H_