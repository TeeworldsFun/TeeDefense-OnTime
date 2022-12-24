#include <base/tl/array.h>
#include <vector>
#include <map>

enum
{
    START_TYPE = 0,

    TYPE_MATERIAL,
    TYPE_WEAPON,
    TYPE_TOOL,
    TYPE_TURRET,
    TYPE_USE,

    END_TYPE,
};

enum Callback
{
    CALLBACK_EXPLOSION,
    CALLBACK_THROW,
    CALLBACK_TICK,
    CALLBACK_GIVE,
    CALLBACK_BUFF,
};

// Item Base
class CItem
{
// Global
public:
    CItem();
    char m_Name[64];
    int m_Type;
    char m_Info[612];

    struct Source
    {
        int m_ID;
        int m_Num;
    };

    // Craft
    std::vector<Source> m_SourceMethod;

    // Mob
    std::vector<Source> m_SourceMob;

    // Weapon
    struct Weapon
    {
        int m_SnapVanilla;
        int m_Damage;
        array<int> m_WeaponEntry;
    };

    // Tool
    struct Tool
    {
        int m_Durability;
        int m_Loss;
    };

    // Turret
    struct Turret
    {
        int m_Damage;
        array<int> m_Entry;
    };

    // Use
    struct Use
    {
        int m_CallbackTick;
        void *m_CallBack;
        
    };
};