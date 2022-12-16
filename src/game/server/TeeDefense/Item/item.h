/* 2022 - 2022 (C) Copyright ST-Chara */

#ifndef TD_ITEM_ITEM_H
#define TD_ITEM_ITEM_H

#include <game/server/gamecontext.h>
#include <teeuniverses/tl/nlohmann_json.h>
#include <engine/storage.h>
#include <base/tl/array.h>

#include <vector>

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

    // Mine
    array<int> m_Mine;

    // Craft
    array<int> m_Method;
    
    // Mob
    array<int> m_MobID;

// Material
public:
    


};

class CItemSys
{
private:
    IStorage *m_pStorage;
    CGameContext *m_pGameServer;
    void LoadJson(const std::string& FileName);
    void LoadItems();
    nlohmann::json m_Json;
public:
    CGameContext *GameServer() { return m_pGameServer; }
    IStorage *Storage() { return m_pStorage; }
    
    CItemSys(CGameContext *pGameServer);

    std::vector<CItem *> m_Items;
};

#endif