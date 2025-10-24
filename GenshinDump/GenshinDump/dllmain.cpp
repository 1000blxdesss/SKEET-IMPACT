#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define STB_IMAGE_IMPLEMENTATION
#define UTF8(str) u8##str
#include <Windows.h>
#include "Logger/Logger.h"
#include "MinHook/include/MinHook.h"
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <memory>
#include <map>
#include <queue>
#include "UnityUtils/il2cpp-api-types.h"
#include <codecvt>
#include <regex>

//offsets
enum Offsets {
    OFJHCHDOJGL = 0xb3f39f0,
    Find = 0x11127fd0,
    GetChild = 0x111445e0,
    GetChildCount = 0x111445f0,
    get_gameObject = 0x111280d0,
    get_active = 0x11127d20,
    get_name = 0x1113ed40,
    get_transform = 0x11127cf0,
    set_collisionDetectionMode = 0x11194e70,
    Transform_get_forward = 0x11142b20,
    Transform_get_right = 0x11142780,
    Transform_get_up = 0x11142950,
    Rigidbody_get_position = 0x11195100,
    Time_get_deltaTime = 0x1112a3d0,
    Rigidbody_set_velocity = 0x11194cd0,
    Rigidbody_MovePosition = 0x11195210,
    set_enabled = 0x111192b0,
    get_enabled = 0x111192a0,
    set_position = 0x11142360,
    Transform_SetParent = 0x111423a0,
    Transform_set_localPosition = 0x11142f80,
    GetSingletonInstance = 0x51e3660,
    get_eulerAngles = 0x11142420,
    set_eulerAngles = 0x11142560,
    Rotate = 0x11143ad0,
    get_velocity = 0x11194c70,
    set_velocity2 = 0x11194cd0,
    KEJFKEBJBBP = 0x71dd830,
    set_speed = 0x11114b20,
    AGLLPMOLOBE = 0xb402770,
    DGOFICCGJCN = 0x6e030,
    set_localScale = 0x11142d90,
    get_localScale = 0x11142d30,
    Text_set_text = 0x11170030,
    Time_get_timeScale = 0x1112a4b0,
    Time_set_timeScale = 0x1112a4c0,
    SetAvatarPos = 0xc7ec690,
    SyncEntityPos = 0xc7dff60,
    NGLNINJGHCB_fn = 0xc3ddd80,
    DPLHPDBOOND_fn = 0xb409b50,
    get_mapBackground_ = 0x9d71120,
    ScreenPointToLocalPointInRectangle_ = 0x111dfd20,
    get_mapRect_ = 0x9d708a0,
    GenWorldPos_ = 0xc0fb550,
    GetRelativePosition_ = 0x538cdf0,
    CalcCurrentGroundHeight_ = 0xc0ef2e0,
    OIENPCIJIHH_fn = 0xcc9d150,
    CHHJOIIHAHD_fn = 0xb25b090,
    BBCBOICBDIG_fn = 0xb25b760,

    UnityEngine_Vector3_WorldToScreenPoint = 0x11137e10,
    UnityEngine_Camera_get_main = 0x111381f0,
    UnityEngine_Transform_get_position = 0x11142300,
    Object_Instantiate = 0x1111b710,
    BEJFLLLFKJC_EFJJBJMJEPC = 0x71f4530,
    BEJFLLLFKJC_PNIIKPACAJM = 0x7200220,
    BEJFLLLFKJC_NJEDPEIHJEH = 0x71ebc80,
    GameObject_GetComponentByName = 0x11127990,
    InteropServices_Marshal_PtrToStringAnsi = 0x10b09790,
    SingletonManager_get_Instance = 0x51e3720,
    CollisionFlags_Move = 0x11188650,
    UnityEngine_Screen_get_width = 0x1114e390,
    UnityEngine_Screen_get_height = 0x1114e3a0,
    UnityEngine_Camera_get_pixelWidth = 0x11137780,
    UnityEngine_Camera_get_pixelHeight = 0x11137790,
    Scene_GetRootGameObjects = 0x3e77a0,
    SceneManager_GetActiveScene = 0x1114dd90,
    GUI_set_color = 0x111623d0,
    GUI_set_backgroundColor = 0x111624b0,
    GUI_get_skin = 0x111631f0,
    GUIContent_Temp = 0x11163580,
    GUI_Toggle = 0x11165520,
    GUI_Slider = 0x11165720,
    GUISkin_get_toggle = 0x11173350,
    GUISkin_get_horizontalSlider = 0x11173410,
    GUISkin_get_horizontalSliderThumb = 0x11173470,
    GUI_BOX = 0x111646b0,
    GUI_Label = 0x11163470,
    GUI_BUTTON = 0x11164aa0,
    GUISkin_get_scrollView = 0x11173890,
    GUISkin_get_horizontalScrollbar = 0x11173590,
    GUISkin_get_verticalScrollbar = 0x11173710,
    GUI_BeginScrollView = 0x111672e0,
    GUI_EndScrollView = 0x11168420,
    GUISkin_get_button = 0x111732f0,
    GUI_Button2 = 0x11164bb0,
    GUISkin_get_textField = 0x11173230,

    UnityEvent_AddListener = 0x11125ea0,
    OptionsMenu_SetupView = 0x65c9ef0,
    OptionsMenu_OnContextCloseFinal = 0x65cb100,
};

enum HookOffsets
{
    BEJFLLLFKJC_ADBNDFCIION = 0x71d1b80,
    BEJFLLLFKJC_ACGLIMPHAIC = 0x7200bc0,
    BEJFLLLFKJC_BHAAEAGOGLF = 0x7203820,
    DNEFDLJAEBM_BPMDIBJJFKF = 0xcc16550,
    KBBLJHGMNLJ_IJEGLKJBGMB = 0x943f230,
    LHMDIPAIAAK_CHOJPBDPNGJ = 0xaa61e30,
    EEIMHEGPLAE_DCAHCDGAPKD = 0x8588430,
    EEIMHEGPLAE_GAIEPJNEFGM = 0x858da90,
    Update_hook = 0x9d1a340,
    LateTick_hook = 0x9440790,
    KDHNELOMKLG_hook = 0x658c890,
    PointerUIBase_OnGUI = 0x1123b4e0,
    HONBCFDAJEI_hook_ = 0x8b53940,
    SetupView_hook_ = 0xb25bc20,
    UpdateView_hook_ = 0xb25d690,
    ClearView_hook_ = 0xb25dc10,
    CGOKDLDFFLA_hook_ = 0xb8543a0,
    CheckTargetAttackable_hook_ = 0xc0cee20,
    HHEDHEFMKMM_hook_ = 0x950fc50,
};

// stucts
struct Vector3 {
    float x = 0, y = 0, z = 0;
    float distance(Vector3 b) const { return sqrtf(powf(x - b.x, 2) + powf(y - b.y, 2) + powf(z - b.z, 2)); }
    bool zero() { return (x == 0 && y == 0 && z == 0); }
    Vector3 operator *(float k) { return { x * k, y * k, z * k }; }
    Vector3 operator -(Vector3 B) { return { x - B.x, y - B.y, z - B.z }; }
    Vector3 operator +(Vector3 B) { return { x + B.x, y + B.y, z + B.z }; }
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3() {}
    static Vector3 Null() { return { 0, 0, 0 }; }
};

struct Vector2 { float x, y; };
struct Rect {
    float x, y, width, height;
    Rect() : x(0), y(0), width(0), height(0) {}
    Rect(float x, float y, float w, float h) : x(x), y(y), width(w), height(h) {}
};

struct Quaternion {
    float x;
    float y;
    float z;
    float w;
};
struct MoveSyncTask {
    struct Vector3 position;
    struct Vector3 velocity;
    struct Vector3 forward;
    struct Vector3 up;
    struct Quaternion rotation;
    int32_t motion;
    int32_t paramNumber;
    struct Vector3 param0;
    struct Vector3 param1;
    struct Vector3 param2;
    struct Vector3 param3;
    uint32_t time;
    uint32_t reliableSeq;
    uint32_t clientSequenceId;
    uint32_t subSequenceId;
    bool reliable;
    bool isFake;
    struct Vector3 refPosition;
    uint32_t refEntityId;
    uint32_t refEntityTimestamp;
    bool hasValue;
    struct Vector3 positionRS;
    struct Vector3 positionRSLocal;
    uint32_t randomDelay;
    int32_t frameCountWhenAddTask;
};

struct Color { float r, g, b, a; };
struct GenericList { void* klass; void* monitor; void* items; int32_t size; int32_t version; };
struct UnityScene { uint32_t handle; uint32_t pad0; uint64_t pad1; };

enum EntityType
{
    None = 0,
    Avatar = 1,
    Monster = 2,
    Bullet = 3,
    AttackPhyisicalUnit = 4,
    AOE = 5,
    Camera = 6,
    EnviroArea = 7,
    Equip = 8,
    MonsterEquip = 9,
    Grass = 10,
    Level = 11,
    NPC = 12,
    TransPointFirst = 13,
    TransPointFirstGadget = 14,
    TransPointSecond = 15,
    TransPointSecondGadget = 16,
    DropItem = 17,
    Field = 18,
    Gadget = 19,
    Water = 20,
    GatherPoint = 21,
    GatherObject = 22,
    AirflowField = 23,
    SpeedupField = 24,
    Gear = 25,
    Chest = 26,
    EnergyBall = 27,
    ElemCrystal = 28,
    Timeline = 29,
    Worktop = 30,
    Team = 31,
    Platform = 32,
    AmberWind = 33,
    EnvAnimal = 34,
    SealGadget = 35,
    Tree = 36,
    Bush = 37,
    QuestGadget = 38,
    Lightning = 39,
    RewardPoint = 40,
    RewardStatue = 41,
    MPLevel = 42,
    WindSeed = 43,
    MpPlayRewardPoint = 44,
    ViewPoint = 45,
    RemoteAvatar = 46,
    GeneralRewardPoint = 47,
    PlayTeam = 48,
    OfferingGadget = 49,
    EyePoint = 50,
    MiracleRing = 51,
    Foundation = 52,
    WidgetGadget = 53,
    Vehicle = 54,
    DangerZone = 55,
    EchoShell = 56,
    HomeGatherObject = 57,
    Projector = 58,
    Screen = 59,
    CustomTile = 60,
    FishPool = 61,
    FishRod = 62,
    CustomGadget = 63,
    RoguelikeOperatorGadget = 64,
    ActivityInteractGadget = 65,
    BlackMud = 66,
    SubEquip = 67,
    UIInteractGadget = 68,
    NightCrowGadget = 69,
    Partner = 70,
    DeshretObeliskGadget = 71,
    CoinCollectLevelGadget = 72,
    UgcSpecialGadget = 73,
    UgcTowerLevelUpGadget = 74,
    JourneyGearOperatorGadget = 75,
    CurveMoveGadget = 76,
    MagnetPlant = 77,
    PlaceHolder = 99
};

// globals (2671.916260, 238.451691, -1082.727661)
Vector3 static testTP = { 0, 0, 0 };
uintptr_t GameBase = NULL;
std::vector<void*> g_hooks;
std::vector<void*> chestList;
static float origGameSpeed = 1.0f;
std::vector<uint32_t> blacklistedChests; // or BHAAEAGOGLF_hook && ACGLIMPHAIC_hook


// proto
void Floatinggggggg();

namespace UnityUtils {
    inline Il2CppClass* il2cpp_class_from_name(const Il2CppImage* image, const char* namespaze, const char* name) {
        if (!image || !namespaze || !name) return nullptr;
        static auto fn = (Il2CppClass * (__fastcall*)(const Il2CppImage*, const char*, const char*))(GameBase + ClassFromName);
        return fn ? fn(image, namespaze, name) : nullptr;
    }

    inline Vector3 WorldToScreenPoint(void* __this, Vector3 position) {
        static auto fn = (Vector3(__fastcall*)(void*, Vector3))(GameBase + Offsets::UnityEngine_Vector3_WorldToScreenPoint);
        return fn ? fn(__this, position) : Vector3{ 0,0,0 };
    }

    inline void* get_main() {
        static auto fn = (void* (*)())(GameBase + Offsets::UnityEngine_Camera_get_main);
        return fn ? fn() : nullptr;
    }

    inline Vector3 get_position(void* _this) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::UnityEngine_Transform_get_position);
        return fn ? fn(_this) : Vector3{ 0,0,0 };
    }

    std::string Utf16ToUtf8(const char16_t* data, int32_t len) {
        if (!data || len <= 0) return {};
        int needed = WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)data, len, NULL, 0, NULL, NULL);
        if (needed <= 0) return {};
        std::string out; out.resize(needed);
        WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)data, len, out.data(), needed, NULL, NULL);
        return out;
    }

    inline void* GetComponentByName(void* __this, Il2CppString* typeName) {
        static auto fn = (void* (__fastcall*)(void*, Il2CppString*))(GameBase + Offsets::GameObject_GetComponentByName);
        return fn ? fn(__this, typeName) : nullptr;
    }

    inline Il2CppString* PtrToStringAnsi(void* ptr) {
        static auto fn = (Il2CppString * (*)(void*))(GameBase + Offsets::InteropServices_Marshal_PtrToStringAnsi);
        return fn ? fn(ptr) : nullptr;
    }

    inline void* get_SingletonManager() {
        static auto fn = (void* (*)())(GameBase + Offsets::SingletonManager_get_Instance);
        return fn ? fn() : nullptr;
    }

    inline int Screen_get_width() {
        static auto fn = (int(*)())(GameBase + Offsets::UnityEngine_Screen_get_width);
        return fn ? fn() : 1920;
    }

    inline int Screen_get_height() {
        static auto fn = (int(*)())(GameBase + Offsets::UnityEngine_Screen_get_height);
        return fn ? fn() : 1080;
    }

    inline int Camera_get_pixelWidth(void* camera) {
        static auto fn = (int(__fastcall*)(void*))(GameBase + Offsets::UnityEngine_Camera_get_pixelWidth);
        return fn ? fn(camera) : 1920;
    }

    inline int Camera_get_pixelHeight(void* camera) {
        static auto fn = (int(__fastcall*)(void*))(GameBase + Offsets::UnityEngine_Camera_get_pixelHeight);
        return fn ? fn(camera) : 1080;
    }

    inline Vector3 sub_1471f4530(void* __this) {
        static auto fn = (Vector3(*)(void*))((uintptr_t)GameBase + Offsets::BEJFLLLFKJC_EFJJBJMJEPC);
        return fn ? fn(__this) : Vector3();
    }

    inline int64_t sub_147202AF0(void* __this) {
        static auto fn = (int64_t(*)(void*))((uintptr_t)GameBase + Offsets::BEJFLLLFKJC_PNIIKPACAJM);
        return fn ? fn(__this) : 0;
    }

    inline void* get_rootGameObject(void* __this) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::BEJFLLLFKJC_NJEDPEIHJEH);
        return fn ? fn(__this) : nullptr;
    }

    inline void* OFJHCHDOJGL(void* __this) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::OFJHCHDOJGL);
        return fn ? fn(__this) : nullptr;
    }

    inline void* Find(Il2CppString* name) {
        static auto fn = (void* (__fastcall*)(Il2CppString*))(GameBase + Offsets::Find);
        if (!fn) return nullptr;
        Il2CppString* str = UnityUtils::PtrToStringAnsi((void*)name);
        return fn(str);
    }

    inline void* GetChild(void* transform, int index) {
        static auto fn = (void* (__fastcall*)(void*, int))(GameBase + Offsets::GetChild);
        return fn ? fn(transform, index) : nullptr;
    }

    inline int GetChildCount(void* transform) {
        static auto fn = (int(__fastcall*)(void*))(GameBase + Offsets::GetChildCount);
        return fn ? fn(transform) : 0;
    }

    inline void* get_gameObject(void* component) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::get_gameObject);
        return fn ? fn(component) : nullptr;
    }

    inline bool get_active(void* gameObject) {
        static auto fn = (bool(__fastcall*)(void*))(GameBase + Offsets::get_active);
        return fn ? fn(gameObject) : false;
    }

    inline Il2CppString* get_name(void* gameObject) {
        static auto fn = (Il2CppString * (__fastcall*)(void*))(GameBase + Offsets::get_name);
        return fn ? fn(gameObject) : nullptr;
    }

    inline void* get_transform(void* gameObject) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::get_transform);
        return fn ? fn(gameObject) : nullptr;
    }

    inline void set_collisionDetectionMode(void* rigidbody, int value) {
        static auto fn = (void(__fastcall*)(void*, int))(GameBase + Offsets::set_collisionDetectionMode);
        if (fn) fn(rigidbody, value);
    }

    inline Vector3 Transform_get_forward(void* transform) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::Transform_get_forward);
        return fn ? fn(transform) : Vector3{};
    }

    inline Vector3 Transform_get_right(void* transform) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::Transform_get_right);
        return fn ? fn(transform) : Vector3{};
    }

    inline Vector3 Transform_get_up(void* transform) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::Transform_get_up);
        return fn ? fn(transform) : Vector3{};
    }

    inline Vector3 Rigidbody_get_position(void* transform) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::Rigidbody_get_position);
        return fn ? fn(transform) : Vector3{};
    }

    inline float Time_get_deltaTime() {
        static auto fn = (float(*)())(GameBase + Offsets::Time_get_deltaTime);
        return fn ? fn() : 0.0f;
    }

    inline void Rigidbody_set_velocity(void* rigidbody, Vector3 value) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::Rigidbody_set_velocity);
        if (fn) fn(rigidbody, value);
    }

    inline void Rigidbody_MovePosition(void* rigidbody, Vector3 position) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::Rigidbody_MovePosition);
        if (fn) fn(rigidbody, position);
    }

    inline void set_enabled(void* collider, bool value) {
        static auto fn = (void(__fastcall*)(void*, bool))(GameBase + Offsets::set_enabled);
        if (fn) fn(collider, value);
    }

    inline bool get_enabled(void* collider) {
        static auto fn = (bool(__fastcall*)(void*))(GameBase + Offsets::get_enabled);
        return fn ? fn(collider) : false;
    }

    inline void set_position(void* transform, Vector3 value) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::set_position);
        if (fn) fn(transform, value);
    }

    inline void set_localPosition(void* transform, Vector3 value) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::Transform_set_localPosition);
        if (fn) fn(transform, value);
    }

    inline void SetParent(void* transform, void* parent, bool worldPositionStays) {
        static auto fn = (void(__fastcall*)(void*, void*, bool))(GameBase + Offsets::Transform_SetParent);
        if (fn) fn(transform, parent, worldPositionStays);
    }

    inline bool SceneManager_GetActiveScene(UnityScene& outScene) {
        static auto fn = (void(__fastcall*)(UnityScene*))(GameBase + Offsets::SceneManager_GetActiveScene);
        if (!fn) return false;
        fn(&outScene);
        return true;
    }

    inline Il2CppArray* Scene_GetRootGameObjects(UnityScene& scene) {
        static auto fn = (Il2CppArray * (__fastcall*)(UnityScene*))(GameBase + Offsets::Scene_GetRootGameObjects);
        return fn ? fn(&scene) : nullptr;
    }

    inline void* Instantiate(void* original) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::Object_Instantiate);
        return fn ? fn(original) : nullptr;
    }

    inline void Text_set_text(void* textComponent, Il2CppString* value) {
        static auto fn = (void(__fastcall*)(void*, Il2CppString*))(GameBase + Offsets::Text_set_text);
        if (fn) fn(textComponent, value);
    }

    inline void* GetSingletonInstance(void* singletonManager, Il2CppString* typeName) {
        static auto fn = (void* (__fastcall*)(void*, Il2CppString*))(GameBase + Offsets::GetSingletonInstance);
        return fn ? fn(singletonManager, typeName) : nullptr;
    }

    inline void* GetEntityManager() {
        void* singletonManager = UnityUtils::get_SingletonManager();
        if (!singletonManager) return nullptr;
        Il2CppString* entityManagerName = UnityUtils::PtrToStringAnsi((void*)"CACMBFKPFIC");
        return GetSingletonInstance(singletonManager, entityManagerName);
    }

    inline Vector3 get_eulerAngles(void* transform) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::get_eulerAngles);
        return fn ? fn(transform) : Vector3();
    }

    inline void set_eulerAngles(void* transform, Vector3 angles) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::set_eulerAngles);
        if (fn) fn(transform, angles);
    }

    inline void Rotate(void* transform, Vector3 axis, float angle) {
        static auto fn = (void(__fastcall*)(void*, Vector3, float))(GameBase + Offsets::Rotate);
        if (fn) fn(transform, axis, angle);
    }

    inline Vector3 get_velocity(void* rigidbody) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::get_velocity);
        return fn ? fn(rigidbody) : Vector3{};
    }

    inline void set_velocity2(void* rigidbody, Vector3 value) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::set_velocity2);
        if (fn) fn(rigidbody, value);
    }

    inline void* KEJFKEBJBBP(void* __this) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::KEJFKEBJBBP);
        return fn ? fn(__this) : nullptr;
    }

    inline void set_speed(void* animator, float value) {
        static auto fn = (void(__fastcall*)(void*, float))(GameBase + Offsets::set_speed);
        if (fn) fn(animator, value);
    }

    inline void* AGLLPMOLOBE(void* __this) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::AGLLPMOLOBE);
        return fn ? fn(__this) : nullptr;
    }

    inline float DGOFICCGJCN(void* __this) {
        static auto fn = (float(__fastcall*)(void*))(GameBase + Offsets::DGOFICCGJCN);
        return fn ? fn(__this) : 0.0f;
    }

    inline void set_localScale(void* transform, Vector3 value) {
        static auto fn = (void(__fastcall*)(void*, Vector3))(GameBase + Offsets::set_localScale);
        if (fn) fn(transform, value);
    }

    inline Vector3 get_localScale(void* transform) {
        static auto fn = (Vector3(__fastcall*)(void*))(GameBase + Offsets::get_localScale);
        return fn ? fn(transform) : Vector3{};
    }

    inline float get_timeScale() {
        static auto fn = (float(*)())(GameBase + Offsets::Time_get_timeScale);
        return fn ? fn() : 0.0f;
    }

    inline float set_timeScale(float value) {
        static auto fn = (float(__fastcall*)(float))(GameBase + Offsets::Time_set_timeScale);
        return fn ? fn(value) : 0.0f;
    }

    inline void SetAvatarPos(Vector3 pos) {
        static auto fn = (float(__fastcall*)(Vector3))(GameBase + Offsets::SetAvatarPos);
        if (fn) fn(pos);
    }

    inline void SyncEntityPos_(void* entity, int state, uint32_t mainQuestId) {
        static auto fn = (float(__fastcall*)(void*, int, uint32_t))(GameBase + Offsets::SyncEntityPos);
        if (fn) fn(entity, state, mainQuestId);
    }

    inline void Box(Rect rect, Il2CppString* text) {
        static auto fn = (void(__fastcall*)(Rect, Il2CppString*))(GameBase + Offsets::GUI_BOX);
        if (fn) fn(rect, text);
    }

    inline void Label(Rect rect, Il2CppString* text) {
        static auto fn = (void(__fastcall*)(Rect, Il2CppString*))(GameBase + Offsets::GUI_Label);
        if (fn) fn(rect, text);
    }

    inline bool Button(Rect rect, Il2CppString* text) {
        static auto fn = (bool(__fastcall*)(Rect, Il2CppString*))(GameBase + Offsets::GUI_BUTTON);
        return fn ? fn(rect, text) : false;
    }

    inline void GUI_set_color_(Color color) {
        static auto fn = (void(__fastcall*)(Color))(GameBase + Offsets::GUI_set_color);
        if (fn) fn(color);
    }

    inline void GUI_set_backgroundColor_(Color color) {
        static auto fn = (void(__fastcall*)(Color))(GameBase + Offsets::GUI_set_backgroundColor);
        if (fn) fn(color);
    }

    inline void* GUI_get_skin_() {
        static auto fn = (void* (*)())(GameBase + Offsets::GUI_get_skin);
        return fn ? fn() : nullptr;
    }

    inline void* GUIContent_Temp_(Il2CppString* text) {
        static auto fn = (void* (__fastcall*)(Il2CppString*))(GameBase + Offsets::GUIContent_Temp);
        return fn ? fn(text) : nullptr;
    }

    inline void* GUISkin_get_toggle_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_toggle);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline void* GUISkin_get_horizontalSlider_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_horizontalSlider);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline void* GUISkin_get_horizontalSliderThumb_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_horizontalSliderThumb);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline bool GUI_Toggle_(Rect rect, bool value, const char* label) {
        static auto fn = (bool(__fastcall*)(Rect, bool, void*, void*))(GameBase + Offsets::GUI_Toggle);
        if (!fn) return value;
        void* skin = GUI_get_skin_();
        void* style = GUISkin_get_toggle_(skin);
        void* content = GUIContent_Temp_(PtrToStringAnsi((void*)label));
        return (style && content) ? fn(rect, value, content, style) : value;
    }

    inline float GUI_HorizontalSlider(Rect rect, float value, float left, float right, int id) {
        static auto fn = (float(__fastcall*)(Rect, float, float, float, float, void*, void*, bool, int))(GameBase + Offsets::GUI_Slider);
        if (!fn) return value;
        void* skin = GUI_get_skin_();
        void* slider = GUISkin_get_horizontalSlider_(skin);
        void* thumb = GUISkin_get_horizontalSliderThumb_(skin);
        return (slider && thumb) ? fn(rect, value, 0.0f, left, right, slider, thumb, true, id) : value;
    }

    inline void* GUISkin_get_scrollView_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_scrollView);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline void* GUISkin_get_horizontalScrollbar_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_horizontalScrollbar);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline void* GUISkin_get_verticalScrollbar_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_verticalScrollbar);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline Vector2 GUI_BeginScrollView_(Rect position, Vector2 scrollPosition, Rect viewRect, bool alwaysShowHorizontal, bool alwaysShowVertical) {
        static auto fn = (Vector2(__fastcall*)(Rect, Vector2, Rect, bool, bool, void*, void*, void*))(GameBase + Offsets::GUI_BeginScrollView);
        if (!fn) return Vector2{ 0.0f, 0.0f };
        void* skin = GUI_get_skin_();
        if (!skin) return Vector2{ 0.0f, 0.0f };
        void* horizontalScrollbar = GUISkin_get_horizontalScrollbar_(skin);
        void* verticalScrollbar = GUISkin_get_verticalScrollbar_(skin);
        void* scrollViewStyle = GUISkin_get_scrollView_(skin);
        return (horizontalScrollbar && verticalScrollbar && scrollViewStyle) ?
            fn(position, scrollPosition, viewRect, alwaysShowHorizontal, alwaysShowVertical, horizontalScrollbar, verticalScrollbar, scrollViewStyle) :
            Vector2{ 0.0f, 0.0f };
    }

    inline void GUI_EndScrollView_(bool handleScrollWheel) {
        static auto fn = (void(__fastcall*)(bool))(GameBase + Offsets::GUI_EndScrollView);
        if (fn) fn(handleScrollWheel);
    }

    inline void* GUISkin_get_button_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_button);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline bool GUI_Button_(Rect position, const char* text) {
        static auto fn = (bool(__fastcall*)(Rect, void*, void*))(GameBase + Offsets::GUI_Button2);
        if (!fn) return false;
        void* skin = GUI_get_skin_();
        void* buttonStyle = GUISkin_get_button_(skin);
        return buttonStyle ? fn(position, PtrToStringAnsi((void*)text), buttonStyle) : false;
    }

    inline void* GUISkin_get_textField_(void* skin) {
        static auto fn = (void* (__fastcall*)(void*))(GameBase + Offsets::GUISkin_get_textField);
        return (fn && skin) ? fn(skin) : nullptr;
    }

    inline void NGLNINJGHCB(void* __this, uint32_t KOLILCCMADM) {
        static auto fn = (void(__fastcall*)(void* __this, uint32_t KOLILCCMADM))(GameBase + Offsets::NGLNINJGHCB_fn);
        if (!fn) return;
        fn(__this, KOLILCCMADM);
    }

    inline void* DPLHPDBOOND(void* __this) {
        static auto fn = (void* (__fastcall*)(void* __this))(GameBase + Offsets::DPLHPDBOOND_fn);
        if (!fn) return nullptr;
        return fn(__this);
    }

    inline void* get_mapBackground(void* __this) {
        static auto fn = (void* (__fastcall*)(void* __this))(GameBase + Offsets::get_mapBackground_);
        if (!fn) return nullptr;
        return fn(__this);
    }
    inline bool ScreenPointToLocalPointInRectangle(void* rect, Vector2 screenPoint, void* cam, Vector2* localPoint) {
        static auto fn = (bool(__fastcall*)(void* rect, Vector2 screenPoint, void* cam, Vector2 * localPoint))(GameBase + Offsets::ScreenPointToLocalPointInRectangle_);
        if (!fn) return false;
        return fn(rect, screenPoint, cam, localPoint);
    }
    inline Rect get_mapRect(void* __this) {
        static auto fn = (Rect(__fastcall*)(void* __this))(GameBase + Offsets::get_mapRect_);
        if (!fn) return Rect{};
        return fn(__this);
    }
    inline Vector3 GenWorldPos(Vector2 levelMapPos) {
        static auto fn = (Vector3(__fastcall*)(Vector2 levelMapPos))(GameBase + Offsets::GenWorldPos_);
        if (!fn) return Vector3{};
        return fn(levelMapPos);
    }

    inline Vector3 GetRelativePosition(Vector3 pos) {
        static auto fn = (Vector3(__fastcall*)(Vector3 pos))(GameBase + Offsets::GetRelativePosition_);
        if (!fn) return Vector3{};
        return fn(pos);
    }

    inline float CalcCurrentGroundHeight(float x, float z) {
        static auto fn = (float(__fastcall*)(float x, float z))(GameBase + Offsets::CalcCurrentGroundHeight_);
        if (!fn) return 0.0f;
        return fn(x, z);
    }

    inline void OIENPCIJIHH(void* __this, int32_t index)
    {
        static auto fn = (void(__fastcall*)(void* __this, int32_t index))(GameBase + Offsets::OIENPCIJIHH_fn);
        if (fn) fn(__this, index);
    }

    inline void CHHJOIIHAHD(void* __this)
    {
        static auto fn = (void(__fastcall*)(void* __this))(GameBase + Offsets::CHHJOIIHAHD_fn);
        if (fn) fn(__this);  
    }

    inline void BBCBOICBDIG(void* __this)
    {
        static auto fn = (void(__fastcall*)(void* __this))(GameBase + Offsets::BBCBOICBDIG_fn);
        if (fn) fn(__this);
    }
}
using namespace UnityUtils;
namespace GuiState {
    struct CombatFlags {
        bool attackMultiplier = true, infUltimate = true, infE = true, killaura = false, fakeRayCastHit = false, drawRadius = false, godMode = true;
        int damageCount = 20;
        float killauraRange = 5.0f;
    };

    struct MovementFlags {
        bool infStamina = true, enablePersistentStamina = true, enableTemporaryStamina = true, enableDiveStamina = true;
        bool sprintCD = true, FakeFloating = false, noclip = false, speed = false, harkoSpin = false;
        int staminaThreshold = 3, restoreValue = 10000, noclipSpeed = 20;
        float FakeFloatingHeightX = 0.0f, FakeFloatingHeightY = 0.0f, FakeFloatingHeightZ = 0.0f;
        float speedMultiplier = 1.5f, harkoSpinSpeed = 5.0f;
        bool teleporterEnabled = true, showTeleportUI = true;
        std::vector<Vector3> teleportPoints;
        int currentTeleportIndex = 0;
    };

    struct VisualFlags {
        bool ESP = false, FPS = false, SkeletonESP = false, RayCast = false, WndProc = false;
    };

    struct MiscsFlags {
        bool dialogEnabled = false, autoSelect = false, autoSkip = false;
        float dialogSpeed = 1.0f;
        bool autoDestroy = false;
        float radiusDestory = 50.0f;
		bool autoPickUp = false;
		bool autoOpenChests = false;
		float radiusOpen = 50.0f;
    };

    inline CombatFlags combat;
    inline VisualFlags visual;
    inline MovementFlags movement;
    inline MiscsFlags miscs;
    inline int selectedTab = 0;
}

namespace OtherUtils 
{
    // some vibecocoding
    inline Vector3 WorldToScreenPointCorrected(void* camera, Vector3 worldPos) {
        Vector3 screenPos = UnityUtils::WorldToScreenPoint(camera, worldPos);

        if (screenPos.z <= 0) return screenPos;

        static int realScreenW = UnityUtils::Screen_get_width();
        static int realScreenH = UnityUtils::Screen_get_height();
        static int cameraPixelW = 0;
        static int cameraPixelH = 0;
        static int refreshCounter = 0;


        if (refreshCounter++ > 60) {
            realScreenW = UnityUtils::Screen_get_width();
            realScreenH = UnityUtils::Screen_get_height();
            if (camera) {
                cameraPixelW = UnityUtils::Camera_get_pixelWidth(camera);
                cameraPixelH = UnityUtils::Camera_get_pixelHeight(camera);
            }
            refreshCounter = 0;
        }

        if (cameraPixelW == 0 || cameraPixelH == 0) {
            cameraPixelW = realScreenW;
            cameraPixelH = realScreenH;
        }

        float scaleX = (float)realScreenW / (float)cameraPixelW;
        float scaleY = (float)realScreenH / (float)cameraPixelH;

        screenPos.x *= scaleX;
        screenPos.y *= scaleY;

        return screenPos;
    }
    inline void* AvatarManager() 
    {
        auto entityManager = UnityUtils::GetEntityManager();
        if (!entityManager) return nullptr;

        auto localAvatar = UnityUtils::OFJHCHDOJGL(entityManager);
        if (!localAvatar) return nullptr;
		return localAvatar;
    }
	inline void* EntityManager()
	{
        auto entityManager = UnityUtils::GetEntityManager();
        if (!entityManager) return nullptr;

        auto entitiesList = UnityUtils::AGLLPMOLOBE(entityManager);
        if (!entitiesList) return nullptr;
		return entitiesList;
	}
    inline void* SingletonManager(std::string name)
    {
        void* singletonManager = UnityUtils::get_SingletonManager();
        if (!singletonManager) return nullptr;

        void* singleton = UnityUtils::GetSingletonInstance(singletonManager, UnityUtils::PtrToStringAnsi((void*)name.c_str()));
        if (!singleton) return nullptr;

        return singleton;
    }
}

void RenderGUI()
{
    static bool menuVisible = false;
    static bool insertHeld = false;

    const bool insertDown = (GetAsyncKeyState(VK_INSERT) & 0x8000) != 0;
    if (insertDown && !insertHeld) {
        menuVisible = !menuVisible;
    }
    insertHeld = insertDown;
    
    if (GuiState::movement.FakeFloating) Floatinggggggg();

    if (GuiState::movement.teleporterEnabled && GuiState::movement.showTeleportUI) {
        const float overlayX = 20.0f; const float overlayY = 20.0f;
        const float overlayWidth = 350.0f; const float overlayHeight = 200.0f;
        
        Rect overlayBg(overlayX, overlayY, overlayWidth, overlayHeight);
        UnityUtils::GUI_set_color_({ 0.08f, 0.08f, 0.12f, 0.95f });
        UnityUtils::Box(overlayBg, UnityUtils::PtrToStringAnsi((void*)""));

        UnityUtils::GUI_set_color_({ 0.32f, 0.52f, 0.96f, 1.0f });
        Rect headerRect(overlayX + 5.0f, overlayY + 5.0f, overlayWidth - 10.0f, 25.0f);
        UnityUtils::Box(headerRect, UnityUtils::PtrToStringAnsi((void*)""));

        UnityUtils::GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        UnityUtils::Label(Rect(overlayX + 15.0f, overlayY + 10.0f, overlayWidth - 30.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"TELEPORTER"));

        float yPos = overlayY + 40.0f;

        if (!GuiState::movement.teleportPoints.empty()) {
            int total = (int)GuiState::movement.teleportPoints.size();
            int current = GuiState::movement.currentTeleportIndex + 1;

            char infoText[128];
            _snprintf_s(infoText, sizeof(infoText), _TRUNCATE, "Point: %d / %d", current, total);

            UnityUtils::GUI_set_color_({ 0.8f, 0.9f, 1.0f, 1.0f });
            UnityUtils::Label(Rect(overlayX + 15.0f, yPos, overlayWidth - 30.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)infoText));
            yPos += 25.0f;

            Vector3 pos = GuiState::movement.teleportPoints[GuiState::movement.currentTeleportIndex];
            char coordText[128];
            _snprintf_s(coordText, sizeof(coordText), _TRUNCATE,
                "X: %.1f", pos.x);
            UnityUtils::Label(Rect(overlayX + 15.0f, yPos, overlayWidth - 30.0f, 16.0f), UnityUtils::PtrToStringAnsi((void*)coordText));
            yPos += 18.0f;

            _snprintf_s(coordText, sizeof(coordText), _TRUNCATE, "Y: %.1f", pos.y);
            UnityUtils::Label(Rect(overlayX + 15.0f, yPos, overlayWidth - 30.0f, 16.0f), UnityUtils::PtrToStringAnsi((void*)coordText));
            yPos += 18.0f;

            _snprintf_s(coordText, sizeof(coordText), _TRUNCATE, "Z: %.1f", pos.z);
            UnityUtils::Label(Rect(overlayX + 15.0f, yPos, overlayWidth - 30.0f, 16.0f), UnityUtils::PtrToStringAnsi((void*)coordText));
            yPos += 25.0f;
        }
        else {
            UnityUtils::GUI_set_color_({ 1.0f, 0.5f, 0.5f, 1.0f });
            UnityUtils::Label(Rect(overlayX + 15.0f, yPos, overlayWidth - 30.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"Empty list"));
            yPos += 25.0f;
        }
        UnityUtils::GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
    }


    if (!menuVisible) return;


    const float WINDOW_SPACING = 20.0f;
    const float PADDING = 12.0f;
    const float HEADER_HEIGHT = 34.0f;
    const float ITEM_HEIGHT = 24.0f;
    const float ITEM_SPACING = 28.0f;
    const float LABEL_HEIGHT = 25.0f;
    const float SLIDER_SPACING = 44.0f;

    const Color BG_COLOR = { 0.09f, 0.11f, 0.15f, 0.92f };
    const Color HEADER_COLOR = { 0.32f, 0.52f, 0.96f, 0.90f };
    const Color ACTIVE_COLOR = { 0.82f, 0.25f, 0.25f, 1.0f };
    const Color INACTIVE_COLOR = { 0.23f, 0.23f, 0.23f, 1.0f };

    float currentX = 400.0f;
    const float currentY = 40.0f;

    // ============================================
    // COMBAT WINDOW
    // ============================================
    {
        const float panelWidth = 340.0f;
        const float panelHeight = 350.0f;
        const float contentHeight = 300.0f;

        Rect mainRect(currentX, currentY, panelWidth, panelHeight);
        UnityUtils::GUI_set_color_(BG_COLOR);
        UnityUtils::Box(mainRect, UnityUtils::PtrToStringAnsi((void*)""));

        Rect headerRect(currentX + 8.0f, currentY + 8.0f, panelWidth - 16.0f, HEADER_HEIGHT);
        GUI_set_color_(HEADER_COLOR);
        Box(headerRect, PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        Label(Rect(headerRect.x + 10.0f, headerRect.y + 7.0f, headerRect.width - 20.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"COMBAT"));

        const float scrollAreaX = currentX + PADDING;
        const float scrollAreaY = currentY + 50.0f;
        const float scrollAreaWidth = panelWidth - PADDING * 2;
        const float scrollAreaHeight = panelHeight - 60.0f;

        Rect scrollRect(scrollAreaX, scrollAreaY, scrollAreaWidth, scrollAreaHeight);
        Rect viewRect(0.0f, 0.0f, scrollAreaWidth - 20.0f, contentHeight);

        GUI_set_color_({ 0.42f, 0.18f, 0.18f, 0.55f });
        Box(scrollRect, PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });

        static Vector2 combatScrollPos{ 0.0f, 0.0f };
        combatScrollPos = GUI_BeginScrollView_(scrollRect, combatScrollPos, viewRect, false, true);

        float y = 15.0f;
        const float contentWidth = viewRect.width - 20.0f;

        GUI_set_backgroundColor_(GuiState::combat.attackMultiplier ? ACTIVE_COLOR : INACTIVE_COLOR);
        GuiState::combat.attackMultiplier = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT),GuiState::combat.attackMultiplier, "Attack Multiplier");
        y += ITEM_SPACING;

        if (GuiState::combat.attackMultiplier) {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Damage Count"));
            y += 25.0f;

            GuiState::combat.damageCount = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), GuiState::combat.damageCount, 1.0f, 100.0f, 0xA11CF);

            char damageText[64];
            _snprintf_s(damageText, sizeof(damageText), _TRUNCATE, "Value: %d", (int)GuiState::combat.damageCount);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT),
                UnityUtils::PtrToStringAnsi((void*)damageText));
            y += SLIDER_SPACING;
        }

        GUI_set_backgroundColor_(GuiState::combat.infUltimate ? Color{ 0.82f, 0.55f, 0.25f, 1.0f } : INACTIVE_COLOR);
        GuiState::combat.infUltimate = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT),
        GuiState::combat.infUltimate, "Infinite Ultimate");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::combat.infE ? Color{ 0.82f, 0.55f, 0.25f, 1.0f } : INACTIVE_COLOR);
        GuiState::combat.infE = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT),GuiState::combat.infE, "Infinite E Ability");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::combat.killaura ? Color{ 0.62f, 0.25f, 0.82f, 1.0f } : INACTIVE_COLOR);
        GuiState::combat.killaura = GUI_Toggle_( Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::combat.killaura, "Killaura");
        y += ITEM_SPACING;

        if (GuiState::combat.killaura) 
        {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Killaura Range"));
            y += 25.0f;

            GuiState::combat.killauraRange = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT),
                GuiState::combat.killauraRange, 0.0f, 100.0f, 0xA11D0);

            char rangeText[64];
            _snprintf_s(rangeText, sizeof(rangeText), _TRUNCATE, "Range: %.1f", GuiState::combat.killauraRange);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)rangeText));
            y += SLIDER_SPACING;
        }
   
        GUI_set_backgroundColor_(GuiState::combat.godMode ? ACTIVE_COLOR : INACTIVE_COLOR);
        GuiState::combat.godMode = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::combat.godMode, "God Mode");
        y += ITEM_SPACING;

        GUI_EndScrollView_(true);
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        GUI_set_backgroundColor_({ 1.0f, 1.0f, 1.0f, 1.0f });

        currentX += panelWidth + WINDOW_SPACING;
    }

    // ============================================
    // MOVEMENT WINDOW
    // ============================================
    {
        const float panelWidth = 340.0f;
        const float panelHeight = 450.0f;
        const float contentHeight = 900.0f;

        Rect mainRect(currentX, currentY, panelWidth, panelHeight);
        GUI_set_color_(BG_COLOR);
        Box(mainRect, UnityUtils::PtrToStringAnsi((void*)""));

        Rect headerRect(currentX + 8.0f, currentY + 8.0f, panelWidth - 16.0f, HEADER_HEIGHT);
        GUI_set_color_(HEADER_COLOR);
        Box(headerRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        Label(Rect(headerRect.x + 10.0f, headerRect.y + 7.0f, headerRect.width - 20.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"MOVEMENT"));

        const float scrollAreaX = currentX + PADDING;
        const float scrollAreaY = currentY + 50.0f;
        const float scrollAreaWidth = panelWidth - PADDING * 2;
        const float scrollAreaHeight = panelHeight - 60.0f;

        Rect scrollRect(scrollAreaX, scrollAreaY, scrollAreaWidth, scrollAreaHeight);
        Rect viewRect(0.0f, 0.0f, scrollAreaWidth - 20.0f, contentHeight);

        GUI_set_color_({ 0.18f, 0.28f, 0.42f, 0.55f });
        Box(scrollRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });

        static Vector2 movementScrollPos{ 0.0f, 0.0f };
        movementScrollPos = GUI_BeginScrollView_(scrollRect, movementScrollPos, viewRect, false, true);

        float y = 15.0f;
        const float contentWidth = viewRect.width - 20.0f;

        Label(Rect(10.0f, y, contentWidth, 18.0f),UnityUtils::PtrToStringAnsi((void*)"Sprint Settings"));
        y += 25.0f;

        GUI_set_backgroundColor_(GuiState::movement.infStamina ? Color{ 0.25f, 0.55f, 0.82f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.infStamina = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT),GuiState::movement.infStamina, "Infinite Stamina");
        y += ITEM_SPACING;

        if (GuiState::movement.infStamina) {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Restore Threshold"));
            y += 25.0f;

            GuiState::movement.staminaThreshold = (int)GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT),(float)GuiState::movement.staminaThreshold, 0.0f, 10000.0f, 0xA11D1);

            char thresholdText[64];
            _snprintf_s(thresholdText, sizeof(thresholdText), _TRUNCATE, "Threshold: %d", GuiState::movement.staminaThreshold);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)thresholdText));
            y += SLIDER_SPACING;

            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Restore Value"));
            y += 25.0f;

            GuiState::movement.restoreValue = (int)GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), (float)GuiState::movement.restoreValue, 0.0f, 10000.0f, 0xA11D4);

            char restoreText[64];
            _snprintf_s(restoreText, sizeof(restoreText), _TRUNCATE, "Value: %d", GuiState::movement.restoreValue);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)restoreText));
            y += SLIDER_SPACING;
        }

        Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Stamina Types:"));
        y += 25.0f;

        GUI_set_backgroundColor_(GuiState::movement.enablePersistentStamina ? Color{ 0.8f, 0.8f, 0.2f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.enablePersistentStamina = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.enablePersistentStamina, "Persistent Stamina (10011)");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::movement.enableTemporaryStamina ? Color{ 0.8f, 0.8f, 0.2f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.enableTemporaryStamina = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.enableTemporaryStamina, "Temporary Stamina (10012)");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::movement.enableDiveStamina ? Color{ 0.8f, 0.8f, 0.2f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.enableDiveStamina = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.enableDiveStamina, "Dive Stamina (10050)");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::movement.sprintCD ? Color{ 0.25f, 0.55f, 0.82f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.sprintCD = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.sprintCD, "No Sprint CD");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::movement.FakeFloating ? Color{ 0.25f, 0.55f, 0.82f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.FakeFloating = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.FakeFloating, "Floating");
        y += ITEM_SPACING;

        if (GuiState::movement.FakeFloating) {
            const char* axes[] = { "X", "Y", "Z" };
            float* heights[] = {
                &GuiState::movement.FakeFloatingHeightX,
                &GuiState::movement.FakeFloatingHeightY,
                &GuiState::movement.FakeFloatingHeightZ
            };
            int ids[] = { 0xA11D5, 0xA11D6, 0xA11D7 };
            for (int i = 0; i < 3; i++) {
                char labelText[32];
                _snprintf_s(labelText, sizeof(labelText), _TRUNCATE, "Floating %s", axes[i]);
                Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)labelText));
                y += 25.0f;

                *heights[i] = GUI_HorizontalSlider(
                    Rect(10.0f, y, contentWidth, LABEL_HEIGHT), *heights[i], -10.0f, 10.0f, ids[i]);

                char valueText[64];
                _snprintf_s(valueText, sizeof(valueText), _TRUNCATE, "%s: %.1f", axes[i], *heights[i]);
                Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)valueText));
                y += SLIDER_SPACING;
            }
        }

        Label(Rect(10.0f, y, contentWidth, 18.0f), UnityUtils::PtrToStringAnsi((void*)"Noclip"));
        y += 25.0f;

        GUI_set_backgroundColor_(GuiState::movement.noclip ? Color{ 0.25f, 0.62f, 0.35f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.noclip = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.noclip, "Noclip");
        y += ITEM_SPACING;

        if (GuiState::movement.noclip) {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Noclip Speed"));
            y += 25.0f;

            GuiState::movement.noclipSpeed = (int)GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), (float)GuiState::movement.noclipSpeed, 0.0f, 100.0f, 0xA11D2);

            char speedText[64];
            _snprintf_s(speedText, sizeof(speedText), _TRUNCATE, "Speed: %d", GuiState::movement.noclipSpeed);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)speedText));
            y += SLIDER_SPACING;
        }

        Label(Rect(10.0f, y, contentWidth, 18.0f), UnityUtils::PtrToStringAnsi((void*)"Speed Multiplier"));
        y += 25.0f;

        bool newSpeedState = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::movement.speed, "Speed Multiplier");

        GUI_set_backgroundColor_(newSpeedState ? Color{ 0.25f, 0.62f, 0.35f, 1.0f } : INACTIVE_COLOR);

        GuiState::movement.speed = newSpeedState;
        y += ITEM_SPACING;

        if (GuiState::movement.speed) {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Speed Value"));
            y += 25.0f;

            GuiState::movement.speedMultiplier = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT),GuiState::movement.speedMultiplier, 1.0f, 5.0f, 0xA11D3);

            char multText[64];
            _snprintf_s(multText, sizeof(multText), _TRUNCATE, "Value: %.1f", GuiState::movement.speedMultiplier);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT),UnityUtils::PtrToStringAnsi((void*)multText));
        }

        GUI_EndScrollView_(true);
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        GUI_set_backgroundColor_({ 1.0f, 1.0f, 1.0f, 1.0f });

        currentX += panelWidth + WINDOW_SPACING;
    }

    // ============================================
    // VISUAL WINDOW
    // ============================================
    {
        const float panelWidth = 340.0f;
        const float panelHeight = 350.0f;
        const float contentHeight = 200.0f;

        Rect mainRect(currentX, currentY, panelWidth, panelHeight);
        GUI_set_color_(BG_COLOR);
        Box(mainRect, UnityUtils::PtrToStringAnsi((void*)""));

        Rect headerRect(currentX + 8.0f, currentY + 8.0f, panelWidth - 16.0f, HEADER_HEIGHT);
        GUI_set_color_(HEADER_COLOR);
        Box(headerRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        Label(Rect(headerRect.x + 10.0f, headerRect.y + 7.0f, headerRect.width - 20.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"VISUAL"));

        const float scrollAreaX = currentX + PADDING;
        const float scrollAreaY = currentY + 50.0f;
        const float scrollAreaWidth = panelWidth - PADDING * 2;
        const float scrollAreaHeight = panelHeight - 60.0f;

        Rect scrollRect(scrollAreaX, scrollAreaY, scrollAreaWidth, scrollAreaHeight);
        Rect viewRect(0.0f, 0.0f, scrollAreaWidth - 20.0f, contentHeight);

        GUI_set_color_({ 0.34f, 0.24f, 0.42f, 0.55f });
        Box(scrollRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });

        static Vector2 visualScrollPos{ 0.0f, 0.0f };
        visualScrollPos = GUI_BeginScrollView_(scrollRect, visualScrollPos, viewRect, false, true);

        float y = 15.0f;
        const float contentWidth = viewRect.width - 20.0f;
        const Color VISUAL_ACTIVE = { 0.62f, 0.36f, 0.78f, 1.0f };

        const char* visualOptions[] = { "ESP", "FPS", "Skeleton ESP", "WndProc" };
        bool* visualStates[] = {
            &GuiState::visual.ESP,
            &GuiState::visual.FPS,
            &GuiState::visual.SkeletonESP,
            &GuiState::visual.WndProc
        };

        for (int i = 0; i < 4; i++) {
            GUI_set_backgroundColor_(*visualStates[i] ? VISUAL_ACTIVE : INACTIVE_COLOR);
            *visualStates[i] = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT),*visualStates[i], visualOptions[i]);
            y += ITEM_SPACING;
        }

        GUI_EndScrollView_(true);
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        GUI_set_backgroundColor_({ 1.0f, 1.0f, 1.0f, 1.0f });
    }

    // ============================================
    // FUN WINDOW
    // ============================================
    {
        const float panelWidth = 340.0f;
        const float panelHeight = 180.0f;
        const float contentHeight = 150.0f;
        const float funX = 400.0f;
        const float funY = currentY + 350.0f + WINDOW_SPACING;

        Rect mainRect(funX, funY, panelWidth, panelHeight);
        GUI_set_color_(BG_COLOR);
        Box(mainRect, UnityUtils::PtrToStringAnsi((void*)""));

        Rect headerRect(funX + 8.0f, funY + 8.0f, panelWidth - 16.0f, HEADER_HEIGHT);
        GUI_set_color_(HEADER_COLOR);
        Box(headerRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        Label(Rect(headerRect.x + 10.0f, headerRect.y + 7.0f, headerRect.width - 20.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"FUN"));

        const float scrollAreaX = funX + PADDING;
        const float scrollAreaY = funY + 50.0f;
        const float scrollAreaWidth = panelWidth - PADDING * 2;
        const float scrollAreaHeight = panelHeight - 60.0f;

        Rect scrollRect(scrollAreaX, scrollAreaY, scrollAreaWidth, scrollAreaHeight);
        Rect viewRect(0.0f, 0.0f, scrollAreaWidth - 20.0f, contentHeight);

        GUI_set_color_({ 0.42f, 0.32f, 0.18f, 0.55f });
        Box(scrollRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });

        static Vector2 funScrollPos{ 0.0f, 0.0f };
        funScrollPos = GUI_BeginScrollView_(scrollRect, funScrollPos, viewRect, false, true);

        float y = 15.0f;
        const float contentWidth = viewRect.width - 20.0f;

        GUI_set_backgroundColor_(GuiState::movement.harkoSpin ? Color{ 0.82f, 0.65f, 0.25f, 1.0f } : INACTIVE_COLOR);
        GuiState::movement.harkoSpin = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT),GuiState::movement.harkoSpin, "Spin");
        y += ITEM_SPACING;

        if (GuiState::movement.harkoSpin) {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT),UnityUtils::PtrToStringAnsi((void*)"Spin Speed"));
            y += 25.0f;

            GuiState::movement.harkoSpinSpeed = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT),GuiState::movement.harkoSpinSpeed, 0.0f, 100.0f, 0xA11E0);

            char speedText[64];
            _snprintf_s(speedText, sizeof(speedText), _TRUNCATE, "Speed: %.0f", GuiState::movement.harkoSpinSpeed);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)speedText));
            y += SLIDER_SPACING;
        }

        static bool boobaEnabled = false;
        GUI_set_backgroundColor_(boobaEnabled ? Color{ 0.82f, 0.65f, 0.25f, 1.0f } : Color{ 0.23f, 0.23f, 0.23f, 1.0f });
        boobaEnabled = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), boobaEnabled, "Booba");
        y += ITEM_SPACING;

        static bool penisDrawEnabled = false;
        GUI_set_backgroundColor_(penisDrawEnabled ? Color{ 0.82f, 0.65f, 0.25f, 1.0f } : Color{ 0.23f, 0.23f, 0.23f, 1.0f });
        penisDrawEnabled = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), penisDrawEnabled, "Penis Draw");
        y += ITEM_SPACING;

        static bool noCensoredEnabled = false;
        GUI_set_backgroundColor_(noCensoredEnabled ? Color{ 0.82f, 0.65f, 0.25f, 1.0f } : Color{ 0.23f, 0.23f, 0.23f, 1.0f });
        noCensoredEnabled = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), noCensoredEnabled, "No Censored");
        y += ITEM_SPACING;

        GUI_EndScrollView_(true);
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        GUI_set_backgroundColor_({ 1.0f, 1.0f, 1.0f, 1.0f });
    }

    // ============================================
    // MISC WINDOW
    // ============================================
    {
        const float panelWidth = 340.0f;
        const float panelHeight = 250.0f;
        const float contentHeight = 220.0f;
        const float miscX = 400.0f;
        const float miscY = currentY + 350.0f + 180.0f + WINDOW_SPACING * 2;

        Rect mainRect(miscX, miscY, panelWidth, panelHeight);
        GUI_set_color_(BG_COLOR);
        Box(mainRect, UnityUtils::PtrToStringAnsi((void*)""));

        Rect headerRect(miscX + 8.0f, miscY + 8.0f, panelWidth - 16.0f, HEADER_HEIGHT);
        GUI_set_color_(HEADER_COLOR);
        Box(headerRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        Label(Rect(headerRect.x + 10.0f, headerRect.y + 7.0f, headerRect.width - 20.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"MISC"));

        const float scrollAreaX = miscX + PADDING;
        const float scrollAreaY = miscY + 50.0f;
        const float scrollAreaWidth = panelWidth - PADDING * 2;
        const float scrollAreaHeight = panelHeight - 60.0f;

        Rect scrollRect(scrollAreaX, scrollAreaY, scrollAreaWidth, scrollAreaHeight);
        Rect viewRect(0.0f, 0.0f, scrollAreaWidth - 20.0f, contentHeight);

        GUI_set_color_({ 0.18f, 0.42f, 0.28f, 0.55f });
        Box(scrollRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });

        static Vector2 miscScrollPos{ 0.0f, 0.0f };
        miscScrollPos = GUI_BeginScrollView_(scrollRect, miscScrollPos, viewRect, false, true);

        float y = 15.0f;
        const float contentWidth = viewRect.width - 20.0f;

        // место для чилла (если вы это читаете, то пришлите скриншот awesomemember._50407 и получите бесплатный ключ)


        const Color MISC_ACTIVE = { 0.25f, 0.82f, 0.35f, 1.0f };

        GUI_set_backgroundColor_(GuiState::miscs.dialogEnabled ? MISC_ACTIVE : INACTIVE_COLOR);
        GuiState::miscs.dialogEnabled = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::miscs.dialogEnabled, "Dialog");
        y += ITEM_SPACING;

        if (GuiState::miscs.dialogEnabled) {
            GUI_set_backgroundColor_(GuiState::miscs.autoSelect ? MISC_ACTIVE : INACTIVE_COLOR);
            GuiState::miscs.autoSelect = GUI_Toggle_(Rect(20.0f, y, contentWidth - 10.0f, 20.0f), GuiState::miscs.autoSelect, "Auto Select");
            y += 25.0f;
            GUI_set_backgroundColor_(GuiState::miscs.autoSkip ? MISC_ACTIVE : INACTIVE_COLOR);
            GuiState::miscs.autoSkip = GUI_Toggle_(Rect(20.0f, y, contentWidth - 10.0f, 20.0f), GuiState::miscs.autoSkip, "Auto Skip");
            y += 25.0f;

            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Dialog Speed"));
            y += 25.0f;

            GuiState::miscs.dialogSpeed = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), GuiState::miscs.dialogSpeed, 0.1f, 5.0f, 0xA11E1);

            char speedText[64];
            _snprintf_s(speedText, sizeof(speedText), _TRUNCATE, "Speed: %.1fx", GuiState::miscs.dialogSpeed);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)speedText));
            y += SLIDER_SPACING;
        }

        GUI_set_backgroundColor_(GuiState::miscs.autoDestroy ? MISC_ACTIVE : INACTIVE_COLOR);
        GuiState::miscs.autoDestroy = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::miscs.autoDestroy, "Auto Destroy");
        y += ITEM_SPACING;

        if (GuiState::miscs.autoDestroy) {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Speed Multiplier"));
            y += 25.0f;

            GuiState::miscs.radiusDestory = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), GuiState::miscs.radiusDestory, 0.1f, 5.0f, 0xA11E3);

            char destroyText[64];
            _snprintf_s(destroyText, sizeof(destroyText), _TRUNCATE, "Value: %.1fx", GuiState::miscs.radiusDestory);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)destroyText));
            y += SLIDER_SPACING;
        }


        GUI_set_backgroundColor_(GuiState::miscs.autoPickUp ? MISC_ACTIVE : INACTIVE_COLOR);
        GuiState::miscs.autoPickUp = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::miscs.autoPickUp, "Auto Pick Up");
        y += ITEM_SPACING;

        GUI_set_backgroundColor_(GuiState::miscs.autoOpenChests ? MISC_ACTIVE : INACTIVE_COLOR);
        GuiState::miscs.autoOpenChests = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), GuiState::miscs.autoOpenChests, "Open Chest");
        y += ITEM_SPACING;

        if (GuiState::miscs.autoOpenChests)
        {
            Label(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)"Radius"));
            y += 25.0f;

            GuiState::miscs.radiusOpen = GUI_HorizontalSlider(Rect(10.0f, y, contentWidth, LABEL_HEIGHT), GuiState::miscs.radiusOpen, 0.1f, 50.0f, 0xA11E4);

            char destroyText[64];
            _snprintf_s(destroyText, sizeof(destroyText), _TRUNCATE, "Value: %.1f", GuiState::miscs.radiusOpen);
            Label(Rect(10.0f, y + 20.0f, contentWidth, LABEL_HEIGHT), UnityUtils::PtrToStringAnsi((void*)destroyText));
            y += SLIDER_SPACING;
        }
        
        GUI_EndScrollView_(true);
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        GUI_set_backgroundColor_({ 1.0f, 1.0f, 1.0f, 1.0f });
    }

    // ============================================
    // DEBUG WINDOW
    // ============================================
    {
        const float panelWidth = 340.0f;
        const float panelHeight = 400.0f;
        const float contentHeight = 500.0f;
        const float debugX = 400.0f + 340.0f + WINDOW_SPACING;
        const float debugY = currentY + 450.0f + WINDOW_SPACING;

        Rect mainRect(debugX, debugY, panelWidth, panelHeight);
        GUI_set_color_(BG_COLOR);
        Box(mainRect, UnityUtils::PtrToStringAnsi((void*)""));

        Rect headerRect(debugX + 8.0f, debugY + 8.0f, panelWidth - 16.0f, HEADER_HEIGHT);
        GUI_set_color_(HEADER_COLOR);
        Box(headerRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        Label(Rect(headerRect.x + 10.0f, headerRect.y + 7.0f, headerRect.width - 20.0f, 20.0f), UnityUtils::PtrToStringAnsi((void*)"DEBUG"));

        const float scrollAreaX = debugX + PADDING;
        const float scrollAreaY = debugY + 50.0f;
        const float scrollAreaWidth = panelWidth - PADDING * 2;
        const float scrollAreaHeight = panelHeight - 60.0f;

        Rect scrollRect(scrollAreaX, scrollAreaY, scrollAreaWidth, scrollAreaHeight);
        Rect viewRect(0.0f, 0.0f, scrollAreaWidth - 20.0f, contentHeight);

        GUI_set_color_({ 0.28f, 0.18f, 0.32f, 0.55f });
        Box(scrollRect, UnityUtils::PtrToStringAnsi((void*)""));
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });

        static Vector2 debugScrollPos{ 0.0f, 0.0f };
        debugScrollPos = GUI_BeginScrollView_(scrollRect, debugScrollPos, viewRect, false, true);

        float y = 15.0f;
        const float contentWidth = viewRect.width - 20.0f;
;
        const Color DEBUG_ACTIVE = { 0.72f, 0.36f, 0.88f, 1.0f };

        Label(Rect(10.0f, y, contentWidth, 18.0f), UnityUtils::PtrToStringAnsi((void*)"TP Script"));
        y += 25.0f;

        static bool tpScriptEnabled = false;
        static float tpX = 0.0f;
        static float tpY = 0.0f;
        static float tpZ = 0.0f;

        GUI_set_backgroundColor_(tpScriptEnabled ? DEBUG_ACTIVE : INACTIVE_COLOR);
        tpScriptEnabled = GUI_Toggle_(Rect(10.0f, y, contentWidth, ITEM_HEIGHT), tpScriptEnabled, "TP Script");
        y += ITEM_SPACING;

        if (tpScriptEnabled) 
        {
        }

        GUI_EndScrollView_(true);
        GUI_set_color_({ 1.0f, 1.0f, 1.0f, 1.0f });
        GUI_set_backgroundColor_({ 1.0f, 1.0f, 1.0f, 1.0f });
    }
}

namespace TeleportManager {
    inline std::string TELEPORT_FILE = "C:\\Users\\guick\\Downloads\\teleports.txt";

    inline bool LoadTeleports() {
        GuiState::movement.teleportPoints.clear();
        std::ifstream file(TELEPORT_FILE);
        if (!file.is_open()) {
            Logger::log_err("Failed to open " + TELEPORT_FILE);
            return false;
        }

        std::string line;
        int pointsLoaded = 0;

        while (std::getline(file, line)) {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            if (line.empty() || line[0] == '#') continue;

            if (line[0] == '(' && line.find(')') != std::string::npos) {
                size_t end = line.find(')');
                std::string content = line.substr(1, end - 1);
                std::replace(content.begin(), content.end(), ',', '.');

                std::istringstream iss(content);
                std::string xStr, yStr, zStr;

                if (std::getline(iss, xStr, ';') && std::getline(iss, yStr, ';') && std::getline(iss, zStr, ';')) {
                    try {
                        float x = std::stof(xStr), y = std::stof(yStr), z = std::stof(zStr);
                        GuiState::movement.teleportPoints.push_back({ x, y, z });
                        pointsLoaded++;
                    }
                    catch (...) {}
                }
            }
        }
        file.close();
        if (GuiState::movement.teleportPoints.empty()) return false;
        GuiState::movement.currentTeleportIndex = 0;
        return true;
    }

    inline void TeleportToCurrent() {
        if (GuiState::movement.teleportPoints.empty()) return;
        Vector3 targetPos = GuiState::movement.teleportPoints[GuiState::movement.currentTeleportIndex];

        auto entityManager = UnityUtils::GetEntityManager();
        if (!entityManager) return;

        auto localAvatar = UnityUtils::OFJHCHDOJGL(entityManager);
        if (!localAvatar) return;

        UnityUtils::SetAvatarPos(targetPos);
    }

    inline void NextPoint() {
        if (GuiState::movement.teleportPoints.empty()) return;
        GuiState::movement.currentTeleportIndex++;
        if (GuiState::movement.currentTeleportIndex >= GuiState::movement.teleportPoints.size())
            GuiState::movement.currentTeleportIndex = 0;
        TeleportToCurrent();
    }

    inline void PrevPoint() {
        if (GuiState::movement.teleportPoints.empty()) return;
        GuiState::movement.currentTeleportIndex--;
        if (GuiState::movement.currentTeleportIndex < 0)
            GuiState::movement.currentTeleportIndex = (int)GuiState::movement.teleportPoints.size() - 1;
        TeleportToCurrent();
    }

    inline void RefreshTeleports() { LoadTeleports(); }
}

void hook_function(uint64_t offset, LPVOID detour, void* original) {
    MH_STATUS create_hook = MH_CreateHook((LPVOID)(GameBase + offset), detour, (LPVOID*)original);
    if (create_hook == MH_OK) {
        MH_EnableHook((LPVOID)(GameBase + offset));
        g_hooks.push_back((LPVOID)(GameBase + offset));
    }
    else {
        std::stringstream hexified;
        hexified << std::hex << offset;
        Logger::log_err("Min failed to hook to offset 0x" + hexified.str() + "! (Status: " + std::to_string(create_hook) + ")");
    }
}

void SpinHero()
{
    auto avatarGameObject = UnityUtils::get_rootGameObject(OtherUtils::AvatarManager());
    if (!avatarGameObject) return;

    auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject, UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!avatarTransform) return;

    static float rotationAngle = 0.0f;
    rotationAngle += GuiState::movement.harkoSpinSpeed;
    if (rotationAngle > 360.0f) rotationAngle = 0.0f;


    Vector3 newRotation = { 0, rotationAngle, 0 };
    UnityUtils::set_eulerAngles(avatarTransform, newRotation);
}

void SpeedChange()
{
    auto avatarGameObject = UnityUtils::get_rootGameObject(OtherUtils::AvatarManager());
    if (!avatarGameObject) return;

    auto rigidbody = UnityUtils::GetComponentByName(avatarGameObject, UnityUtils::PtrToStringAnsi((void*)("Rigidbody")));
    if (!rigidbody) return;

    auto animator = UnityUtils::KEJFKEBJBBP(OtherUtils::AvatarManager());
    if (!animator) return;
    if (GuiState::movement.speed) UnityUtils::set_speed(animator, GuiState::movement.speedMultiplier);
}

void Floatinggggggg() {

    auto avatarGameObject = UnityUtils::get_rootGameObject(OtherUtils::AvatarManager());
    if (!avatarGameObject) return;
    auto rigidbody = UnityUtils::GetComponentByName(avatarGameObject, UnityUtils::PtrToStringAnsi((void*)"Rigidbody"));
    if (!rigidbody) return;

    Vector3 vel = UnityUtils::get_velocity(rigidbody);
    UnityUtils::set_velocity2(rigidbody, Vector3{
        vel.x * GuiState::movement.FakeFloatingHeightX,
        vel.y * GuiState::movement.FakeFloatingHeightY,
        vel.z * GuiState::movement.FakeFloatingHeightZ
        });
}

void noClip()
{
    static bool wasNoClipEnabled = false;

    auto entityManager = UnityUtils::GetEntityManager();
    if (!entityManager) return;

    auto localAvatar = UnityUtils::OFJHCHDOJGL(entityManager);
    if (!localAvatar) return;

    auto avatarGameObject = UnityUtils::get_rootGameObject(localAvatar);
    if (!avatarGameObject) return;

    auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject, UnityUtils::PtrToStringAnsi((void*)("Transform")));
    if (!avatarTransform) return;

    void* cameraEntity = DPLHPDBOOND(entityManager);
    void* cameraTransform = nullptr;

    if (cameraEntity) 
    {
        auto cameraGameObject = UnityUtils::get_rootGameObject(cameraEntity);
        if (cameraGameObject) cameraTransform = UnityUtils::GetComponentByName(cameraGameObject, UnityUtils::PtrToStringAnsi((void*)("Transform")));
    }

    auto rigidbody = UnityUtils::GetComponentByName(avatarGameObject, UnityUtils::PtrToStringAnsi((void*)("Rigidbody")));

    if (rigidbody && wasNoClipEnabled != GuiState::movement.noclip) {
        if (GuiState::movement.noclip) {
            UnityUtils::set_collisionDetectionMode(rigidbody, 0);
            UnityUtils::set_enabled(rigidbody, false);
           
        }
        else {
            UnityUtils::set_collisionDetectionMode(rigidbody, 1); 
            UnityUtils::set_enabled(rigidbody, true);
        }
        wasNoClipEnabled = GuiState::movement.noclip;
    }

    if (!GuiState::movement.noclip) return;

    Vector3 currentPos = UnityUtils::get_position(avatarTransform);
    if (currentPos.zero()) return;

    Vector3 dir = {};

    if (GetAsyncKeyState('W') & 0x8000) dir = dir + UnityUtils::Transform_get_forward(cameraTransform);
    if (GetAsyncKeyState('S') & 0x8000) dir = dir - UnityUtils::Transform_get_forward(cameraTransform);
    if (GetAsyncKeyState('D') & 0x8000) dir = dir + UnityUtils::Transform_get_right(cameraTransform);
    if (GetAsyncKeyState('A') & 0x8000) dir = dir - UnityUtils::Transform_get_right(cameraTransform);

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) dir.y += 1.0f;
    if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) dir.y -= 1.0f;

    if (dir.zero()) return;

    float length = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (length > 0.001f) {
        dir.x /= length;
        dir.y /= length;
        dir.z /= length;
    }

    float deltaTime = UnityUtils::Time_get_deltaTime();
    Vector3 moveDelta = dir * (float)GuiState::movement.noclipSpeed * deltaTime;
    Vector3 newPos = currentPos + moveDelta;

    if (rigidbody) { UnityUtils::Rigidbody_MovePosition(rigidbody, newPos); }
}

inline void* (*Update_original)(void* __this);
inline void* Update_hook_(void* __this)
{
    if (!GuiState::miscs.autoOpenChests) return Update_original(__this);
    static int frameCount = 0;
    frameCount++;

    if (frameCount % 100 != 0) {
        return Update_original(__this);
    }

    auto entityManager = UnityUtils::GetEntityManager();
    if (!entityManager) return Update_original(__this);

    auto entitiesList = UnityUtils::AGLLPMOLOBE(entityManager);
    if (!entitiesList) return Update_original(__this);
    auto list = reinterpret_cast<GenericList*>(entitiesList);
    auto itemsArray = reinterpret_cast<Il2CppArray*>(list->items);

    if (!itemsArray) return Update_original(__this);

    void* singletonManager = UnityUtils::get_SingletonManager();
    if (!singletonManager) return Update_original(__this);

    void* itemModule = UnityUtils::GetSingletonInstance(singletonManager, UnityUtils::PtrToStringAnsi((void*)"GHLLOIKMALP"));
    if (!itemModule) return Update_original(__this);

    Vector3 playerPos = { 0, 0, 0 };
    auto avatar = OtherUtils::AvatarManager();
    if (avatar) {
        auto avatarGameObject = UnityUtils::get_rootGameObject(avatar);
        if (avatarGameObject) {
            auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject, UnityUtils::PtrToStringAnsi((void*)("Transform")));
            if (avatarTransform) {
                playerPos = UnityUtils::get_position(avatarTransform);
            }
        }
    }

    for (int i = 0; i < list->size; i++)
    {
        void* entity = itemsArray->vector[i];
        if (!entity) continue;

        EntityType entityType = (EntityType)(*(uint32_t*)((uintptr_t)entity + 0x39c));

        if (entityType == EntityType::Chest)
        {
            Vector3 chestPos = { 0, 0, 0 };
            auto chestGameObject = UnityUtils::get_rootGameObject(entity);
            if (chestGameObject) {
                auto chestTransform = UnityUtils::GetComponentByName(chestGameObject, UnityUtils::PtrToStringAnsi((void*)("Transform")));
                if (chestTransform) {
                    chestPos = UnityUtils::get_position(chestTransform);
                }
            }

            float distance = playerPos.distance(chestPos);

            if (distance <= GuiState::miscs.radiusOpen) {
                uint32_t runtimeID = *(uint32_t*)((uintptr_t)entity + 0x3c4);
                NGLNINJGHCB(itemModule, runtimeID);
            }
        }
    }
    return Update_original(__this);
}

void (*LateTick_original)(void*, float);
void LateTick_hook_(void* __this, float a) {
    static bool leftHeld = false, rightHeld = false, homeHeld = false;

    if (GuiState::movement.teleporterEnabled) {
        bool leftDown = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
        bool rightDown = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
        bool homeDown = (GetAsyncKeyState(VK_HOME) & 0x8000) != 0;

        if (homeDown && !homeHeld) TeleportManager::RefreshTeleports();
        homeHeld = homeDown;
        if (leftDown && !leftHeld) TeleportManager::PrevPoint();
        leftHeld = leftDown;
        if (rightDown && !rightHeld) TeleportManager::NextPoint();
        rightHeld = rightDown;
    }

    if (GuiState::movement.harkoSpin) SpinHero();
    if (GuiState::movement.speedMultiplier != 1.0f) SpeedChange();
    if (GuiState::movement.noclip) { noClip(); return; }

    LateTick_original(__this, a);
}
// get public UnityEngine.Vector3 position; // 0x10 from MoleMole.MoveSyncTask
// //get protected MoleMole.MoveSyncTask MKFJEFAOLOH; // 0x148 __this+0x148
//hook // RVA: 0x658d3b0 VA: 0x7ff7d965d3b0 private System.Void KDHNELOMKLG() {}
Vector3 currentPlayerPos = { 0,0,0 };
Vector3 currentPosFix = { 0,0,0 };
Vector3 currentEnemyPosFix = { 0,0,0 };
static Vector3 g_PrevAvatarPosition = { 0, 0, 0 };
static int64_t g_PrevSyncTime = 0;
static bool g_IsNoClipEnabled = false;

inline void* (*KDHNELOMKLG_original)(void* __this);
inline void* KDHNELOMKLG_hook_(void* __this)
{
    MoveSyncTask* moveSyncTask = (MoveSyncTask*)((uintptr_t)__this + 0x148);


    // fld protected KLHBHFIDCGG OCMBDPICNAD; // 0x18 from GMLOEPALBOG (BaseComponentPlugin)
    void* baseComponentPlugin = *(void**)((uintptr_t)__this + 0x18);
    // fld public System.UInt32 INBMEOGACCC; // 0x14 from KLHBHFIDCGG (runrimeID)
    uint32_t entityId = *(uint32_t*)((uintptr_t)baseComponentPlugin + 0x14);
    // protected BEJFLLLFKJC HBFJBCOHDIJ; // 0x28
    void* baseEntity = *(void**)((uintptr_t)baseComponentPlugin + 0x28);
    int64_t ret = UnityUtils::sub_147202AF0(baseEntity);
    if (ret != 0) {
        Il2CppString* s = reinterpret_cast<Il2CppString*>((void*)ret);
        if (s && s->length > 0) {
            std::string utf8 = UnityUtils::Utf16ToUtf8(s->chars, s->length);

            if (utf8.find("entityType:Avatar") != std::string::npos)
            {
                currentPlayerPos = moveSyncTask->position;
                auto avatarGameObject = UnityUtils::get_rootGameObject(baseEntity);
                if (!avatarGameObject) return KDHNELOMKLG_original(__this);
                auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
                    UnityUtils::PtrToStringAnsi((void*)("Transform")));
                if (!avatarTransform) return KDHNELOMKLG_original(__this);
                currentPosFix = UnityUtils::get_position(avatarTransform);
                if (currentPosFix.zero()) return KDHNELOMKLG_original(__this);
                return KDHNELOMKLG_original(__this);
            }
            auto otherEntityGameObject = UnityUtils::get_rootGameObject(baseEntity);
            if (!otherEntityGameObject) return KDHNELOMKLG_original(__this);
            auto otherEntityTransform = UnityUtils::GetComponentByName(otherEntityGameObject,
                UnityUtils::PtrToStringAnsi((void*)("Transform")));
            if (!otherEntityTransform) return KDHNELOMKLG_original(__this);
            currentEnemyPosFix = UnityUtils::get_position(otherEntityTransform);

            float distance = currentPlayerPos.distance(moveSyncTask->position);


            if (GuiState::combat.killaura && distance <= GuiState::combat.killauraRange)
            {
                

                moveSyncTask->position.x = 1000000.0f;
                moveSyncTask->position.y = 1000000.0f;
                moveSyncTask->position.z = 1000000.0f;

               
            }

        }
    }

    return KDHNELOMKLG_original(__this);
}

void* (*HONBCFDAJEI_orig)(void*, Vector2);
void* HONBCFDAJEI_hook(void* __this, Vector2 param)
{
    void* pageMono = *(void**)((uintptr_t)__this + 0x2c0);
    auto mapBackground = get_mapBackground(pageMono);
    void* singletonManager = UnityUtils::get_SingletonManager();
    Il2CppString* UIManagername = UnityUtils::PtrToStringAnsi((void*)"KPOPKDNOIFK");
    auto uimanager = UnityUtils::GetSingletonInstance(singletonManager, UIManagername);

    auto screenCamera = *(void**)((uintptr_t)uimanager + 0xb8);
    Vector2 mapPosition{};
    bool result = ScreenPointToLocalPointInRectangle(mapBackground, param, screenCamera, &mapPosition);
    auto mapRect = get_mapRect(*(void**)((uintptr_t)__this + 0x2c0));
    Rect mapViewRect = *(Rect*)((uintptr_t)__this + 0x4f4);

    mapPosition.x = (mapPosition.x - mapRect.x) / mapRect.width;
    mapPosition.x = (mapPosition.x * mapViewRect.width) + mapViewRect.x;

    mapPosition.y = (mapPosition.y - mapRect.y) / mapRect.height;
    mapPosition.y = (mapPosition.y * mapViewRect.height) + mapViewRect.y;

    auto worldPosition = GenWorldPos(mapPosition);
    auto relativePos = GetRelativePosition(worldPosition);
    auto groundHeight = CalcCurrentGroundHeight(relativePos.x, relativePos.z);
    testTP = {
        worldPosition.x,
        groundHeight > 0 ? groundHeight + 5 : 300.0f,
        worldPosition.z
    };

    UnityUtils::SetAvatarPos(testTP);
    return HONBCFDAJEI_orig(__this, param);
}

// RVA: 0xb25bc20 VA: 0x7ff7de32bc20 public override System.Void SetupView() {}
void* (*SetupView_orig)(void*);
void* SetupView_hook(void* __this)
{
    origGameSpeed = UnityUtils::get_timeScale();
    if (GuiState::miscs.dialogSpeed>1.0f) UnityUtils::set_timeScale(origGameSpeed * 2.0f);
    
    return SetupView_orig(__this);
}

// RVA: 0xb25d690 VA: 0x7ff7de32d690 public override System.Void UpdateView() {}
void* (*UpdateView_orig)(void*);
void* UpdateView_hook(void* __this)
{
    // private TalkDialogContext _talkDialog ; (ACJPHIHCBIF; // 0x1e8)
    void* talkDialog = *(void**)((uintptr_t)__this + 0x1e8);
    if (talkDialog != nullptr)
    {
        // private System.Boolean PLIKDFDCIFK; // 0x291 or 0x2b3
        bool _inSelect = *(void**)((uintptr_t)talkDialog + 0x291);
        if (GuiState::miscs.autoSkip) CHHJOIIHAHD(__this);
        if (_inSelect && GuiState::miscs.autoSelect)  OIENPCIJIHH(talkDialog, 0);
        // f_talk_dialog = talkDialog;
    }
    return UpdateView_orig(__this);
}
// RVA: 0xb25dc10 VA: 0x7ff7de32dc10 public override System.Void ClearView() {}
void* (*ClearView_orig)(void*);
void* ClearView_hook(void* __this)
{
    UnityUtils::set_timeScale(origGameSpeed);
    return ClearView_orig(__this);
}

// RVA: 0x111f3cc0 VA: 0x7ff7e42c3cc0 public System.Int32 get_value() {}
int (*get_value_orig)(void* __this);
int get_value_hook(void* __this) 
{
    Logger::log_info("1");
    return get_value_orig(__this);
}

// RVA: 0xb8543a0 VA: 0x7ff7de9243a0 private System.Void CGOKDLDFFLA(System.Int32 BIIAHDMOLIC, System.Single LFBELJAMFHM, System.Nullable<System.Single> NHGNMEFNADN) {}
void (*CGOKDLDFFLA_orig)(void*, int, float, void*);
void CGOKDLDFFLA_hook(void* _this, int modifierDurabilityIndex, float reduceDurability, void* deltaTime) 
{
    // class -> LCBase -> BaseComponent
    void* baseEntity = *(void**)((uintptr_t)_this + 0x28);

    if (baseEntity && GuiState::miscs.autoDestroy) {
        auto entityGameObject = UnityUtils::get_rootGameObject(baseEntity);
        if (entityGameObject) {
            auto entityTransform = UnityUtils::GetComponentByName(entityGameObject,
                UnityUtils::PtrToStringAnsi((void*)"Transform"));

            if (entityTransform) {
                Vector3 entityPos = UnityUtils::get_position(entityTransform);

                auto entityManager = UnityUtils::GetEntityManager();
                if (entityManager) {
                    auto localAvatar = UnityUtils::OFJHCHDOJGL(entityManager);
                    if (localAvatar) {
                        auto avatarGameObject = UnityUtils::get_rootGameObject(localAvatar);
                        if (avatarGameObject) {
                            auto avatarTransform = UnityUtils::GetComponentByName(avatarGameObject,
                                UnityUtils::PtrToStringAnsi((void*)"Transform"));
                            if (avatarTransform) {
                                Vector3 playerPos = UnityUtils::get_position(avatarTransform);

                                float distance = playerPos.distance(entityPos);

                                if (distance <= GuiState::miscs.radiusDestory) {

                                    CGOKDLDFFLA_orig(_this, modifierDurabilityIndex, 1000.0f, deltaTime);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// RVA: 0xc0cee20 VA: 0x7ff7df19ee20
// public static System.Boolean CheckTargetAttackable(BEJFLLLFKJC attacker, GGPDMFMDNKM target, System.Boolean checkBackstage) {}
bool (*CheckTargetAttackable_orig)(void* attacker, void* target, bool checkBackstage);
bool CheckTargetAttackable_hook(void* attacker, void* target, bool checkBackstage)
{
    if (GuiState::combat.godMode && target) {
        auto entityManager = UnityUtils::GetEntityManager();
        if (entityManager) {
            auto localAvatar = UnityUtils::OFJHCHDOJGL(entityManager);
            if (localAvatar == target) {
                return false;
            }
        }
    }

    return CheckTargetAttackable_orig(attacker, target, checkBackstage);
}

// RVA: 0x950fc50 VA: 0x7ff7dc5dfc50 private System.Void HHEDHEFMKMM(BEJFLLLFKJC MLGGGKJHLCF) {}
void* (*HHEDHEFMKMM_orig)(void*, void*);
void* HHEDHEFMKMM_hook(void* __this, void* entity)
{
	if (!GuiState::miscs.autoPickUp) return HHEDHEFMKMM_orig(__this, entity);
    void* singletonManager = UnityUtils::get_SingletonManager();
    if (singletonManager) 
    {
        void* itemModule = UnityUtils::GetSingletonInstance(singletonManager,UnityUtils::PtrToStringAnsi((void*)"GHLLOIKMALP"));
        if (itemModule) 
        {
            uint32_t CMCEMNBKNGC = *(uint32_t*)((uintptr_t)entity + 0x3c4); //
            NGLNINJGHCB(itemModule, CMCEMNBKNGC);
        } 
    }
    

    return HHEDHEFMKMM_orig(__this, entity);
}
inline void (*PointerUIBase_OnGUI_original)(void* __this);
inline void PointerUIBase_OnGUI_hook(void* __this)
{
    if (PointerUIBase_OnGUI_original) {
        PointerUIBase_OnGUI_original(__this);
    }

    RenderGUI();
}

// RVA: 0xcc16550 VA: 0x7ff7dfce6550 public virtual System.Void BPMDIBJJFKF(System.UInt32 KJJPJFNIPPO, System.Int64 MMLPIIDGCJD, HGEBEPHCCGJ DACAPNLIJLJ) {}
void* (*BPMDIBJJFKF_original)(void*, uint32_t, int64_t, void*);
void* BPMDIBJJFKF_hook(void* __this, uint32_t a, int64_t b, void* c) {
    if (!GuiState::movement.infStamina) return BPMDIBJJFKF_original(__this, a, b, c);

    if ((a == 10011 && GuiState::movement.enablePersistentStamina) ||
        (a == 10012 && GuiState::movement.enableTemporaryStamina) ||
        (a == 10050 && GuiState::movement.enableDiveStamina)) {
        if (b <= GuiState::movement.staminaThreshold) b = GuiState::movement.restoreValue;
    }
    return BPMDIBJJFKF_original(__this, a, b, c);
}

// RVA: 0xaa61e30 VA: 0x7ff7ddb31e30 public System.Void CHOJPBDPNGJ(System.UInt32 OBBGEEHEJKP, IIOGGHPECKN MBBDBMKAFFL) {}
void* (*CHOJPBDPNGJ_original)(void* __this, uint32_t, void*);
void* CHOJPBDPNGJ_hook(void* __this, uint32_t attackeeRuntimeID, void* attackResult)
{
    if (GuiState::combat.attackMultiplier)
    {
        for (int i = 0;i < GuiState::combat.damageCount;i++) CHOJPBDPNGJ_original(__this, attackeeRuntimeID, attackResult);
    }

    return CHOJPBDPNGJ_original(__this, attackeeRuntimeID, attackResult);
}

// RVA: 0x8588430 VA: 0x7ff7db658430 private System.Void DCAHCDGAPKD(System.Single NHGNMEFNADN) {}
void* (*DCAHCDGAPKD_original)(void* __this, float);
void* DCAHCDGAPKD_hook(void* __this, float a) {
    if (GuiState::combat.infE) a = 0.9f;
    return DCAHCDGAPKD_original(__this, a);
}
// RVA: 0x943f230 VA: 0x7ff7dc50f230 public System.Void IJEGLKJBGMB(System.Single NHGNMEFNADN) {}
void* (*IJEGLKJBGMB_original)(void* __this, float);
void* IJEGLKJBGMB_hook(void* __this, float a) {
    if (GuiState::movement.sprintCD)a = 0.5f;
    return IJEGLKJBGMB_original(__this, a);
}

// RVA: 0x858c7c0 VA: 0x7ff7db65c7c0 public System.Boolean IHILHPOAPCK() {}
bool (*GAIEPJNEFGM_original)(void* __this);
bool GAIEPJNEFGM_hook(void* __this) {
    if (GuiState::combat.infUltimate)return true;
    return GAIEPJNEFGM_original(__this);
}

void init_hooks() {
    MH_STATUS status = MH_Initialize();
    if (status != MH_OK) {
        return;
    }
    hook_function(0x111f3cc0, &get_value_hook, &get_value_orig);

    //UpdateTick
    //hook_function(0x71f3f60, &MHPCHKLMBLI_hook, &MHPCHKLMBLI_orig);
    //hook_function(HookOffsets::BEJFLLLFKJC_ADBNDFCIION, &ADBNDFCIION_hook, &ADBNDFCIION_original);

   hook_function(HookOffsets::Update_hook, &Update_hook_, &Update_original);
    hook_function(HookOffsets::LateTick_hook, &LateTick_hook_, &LateTick_original);

    //Clean (work)
   /* hook_function(HookOffsets::BEJFLLLFKJC_ACGLIMPHAIC, &ACGLIMPHAIC_hook, &ACGLIMPHAIC_original);
    hook_function(HookOffsets::BEJFLLLFKJC_BHAAEAGOGLF, &BHAAEAGOGLF_hook, &BHAAEAGOGLF_original);*/
  
    //movement
    hook_function(HookOffsets::DNEFDLJAEBM_BPMDIBJJFKF, &BPMDIBJJFKF_hook, &BPMDIBJJFKF_original); // inf stamina
    hook_function(HookOffsets::KBBLJHGMNLJ_IJEGLKJBGMB, &IJEGLKJBGMB_hook, &IJEGLKJBGMB_original); // cd

    //moveSync
    hook_function(HookOffsets::KDHNELOMKLG_hook, &KDHNELOMKLG_hook_, &KDHNELOMKLG_original);

    // TP
    hook_function(HookOffsets::HONBCFDAJEI_hook_, &HONBCFDAJEI_hook, &HONBCFDAJEI_orig); // set mark
    //hook_function(0xae91850, &JLDLLCJJMLE_hook, &JLDLLCJJMLE_orig);

    // gui
    hook_function(HookOffsets::PointerUIBase_OnGUI, &PointerUIBase_OnGUI_hook, &PointerUIBase_OnGUI_original);
    // hook_function(0x11125EA0, &Button_AddListener_hook, &Button_AddListener_orig);

     // chat
     hook_function(HookOffsets::SetupView_hook_, &SetupView_hook, &SetupView_orig);
     hook_function(HookOffsets::UpdateView_hook_, &UpdateView_hook, &UpdateView_orig);
     hook_function(HookOffsets::ClearView_hook_, &ClearView_hook, &ClearView_orig);
     //hook_function(0xcc92be0, &OnNotify_hook, &OnNotify_orig);

     // anti-cheat (do not use)
     //hook_function(0xafa1650, &LGFMDEEHOPJ_hook, &LGFMDEEHOPJ_orig); // md5 // game data (cut)
     //hook_function(0xafa1c50, &BGGEGJOFGPL_hook, &BGGEGJOFGPL_orig); // report lua
     //hook_function(0x478560, &sub_140478560_hook, &sub_140478560_orig);

     //attack
    hook_function(HookOffsets::LHMDIPAIAAK_CHOJPBDPNGJ, &CHOJPBDPNGJ_hook, &CHOJPBDPNGJ_original); // multi hit
    hook_function(HookOffsets::EEIMHEGPLAE_DCAHCDGAPKD, &DCAHCDGAPKD_hook, &DCAHCDGAPKD_original); // TickSkillCd
    hook_function(HookOffsets::EEIMHEGPLAE_GAIEPJNEFGM, &GAIEPJNEFGM_hook, &GAIEPJNEFGM_original); // inf ult

    // destroy
    hook_function(HookOffsets::CGOKDLDFFLA_hook_, &CGOKDLDFFLA_hook, &CGOKDLDFFLA_orig);

    //godmode
    hook_function(HookOffsets::CheckTargetAttackable_hook_, &CheckTargetAttackable_hook, &CheckTargetAttackable_orig);

    //item
    hook_function(HookOffsets::HHEDHEFMKMM_hook_, &HHEDHEFMKMM_hook, &HHEDHEFMKMM_orig);
}

void Cleanup() 
{
    MH_DisableHook(MH_ALL_HOOKS);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    for (void* hookAddress : g_hooks) {
        MH_RemoveHook(hookAddress);
    }
    g_hooks.clear();

    MH_Uninitialize();
}

DWORD WINAPI UnloadThread(LPVOID param) {
    Sleep(500);
    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}

void initIl2cp() {
    GameBase = (uintptr_t)GetModuleHandleA(NULL);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
    AllocConsole();
    FILE* console;
    freopen_s(&console, "CONOUT$", "w", stdout);
    Logger::console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Logger::console, 0x000F);

    initIl2cp();
    init_hooks();

    while (true) {
        if (GetAsyncKeyState(VK_END)) break;

    }

    Cleanup();
    if (console) fclose(console);
    FreeConsole();
    CreateThread(nullptr, 0, UnloadThread, lpReserved, 0, nullptr);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(module);
        CreateThread(nullptr, 0, MainThread, module, 0, nullptr);
    }
    return TRUE;

}
