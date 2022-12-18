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
};

// Item Base
class CItem
{
// Global
public:
    CItem();
    char m_Name[64];
    int m_Type;

    struct Source
    {
        int m_ID;
        int m_Num;
    };
    
    // Craft
    std::vector<Source > m_SourceMethod;
    
    // Mob
    std::vector<Source > m_SourceMob;

// Material
public:
    


};