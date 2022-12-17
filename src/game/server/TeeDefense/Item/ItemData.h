#include <base/tl/array.h>
#include <vector>
#include <map>

enum
{
    START_TYPE=0,

    TYPE_MATERIAL,
    TYPE_WEAPON,
    TYPE_TOOL,
    TYPE_TURRET,
    TYPE_USE,

    END_TYPE,
    START_SOURCE=0,

    SOURCE_MINE,
    SOURCE_CRAFT,
    SOURCE_MOB,
    
    END_SOURCE,
};

// Item Base
class CItem
{
// Global
public:
    CItem();
    char m_Name[64];
    int m_Type;

    // Craft
    std::map<int, int> m_Method;
    
    // Mob
    std::map<int, int> m_MobID;

// Material
public:
    


};