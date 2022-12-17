/* 2022 - 2022 (C) Copyright ST-Chara */

#ifndef TD_ITEM_ITEM_H
#define TD_ITEM_ITEM_H

#include <game/server/gamecontext.h>
#include <teeuniverses/tl/nlohmann_json.h>
#include <engine/storage.h>

#include "ItemData.h"
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