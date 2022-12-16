/* 2022 - 2022 (C) Copyright ST-Chara */

#ifndef TD_ITEM_ITEM_H
#define TD_ITEM_ITEM_H

#include <game/server/gamecontext.h>
#include <engine/external/json-parser/json.h>
#include <engine/storage.h>

#include <bits/stdc++.h>
using namespace std;

enum Type
{
    TYPE_MATERIAL=0,
    TYPE_WEAPON,
    TYPE_TOOL,
    TYPE_TURRET,
    TYPE_USE,
};

enum Source
{
    SOURCE_MINE,
    SOURCE_CRAFT,
    SOURCE_MOB,
};

// Item Base
class CItem
{
private:
    char m_Name[64];
    const int m_Type;
public:
    const char *GetName() const { return m_Name; };
    const int GetType() const { return m_Type; }    
};

class CItemWeapon : public CItem
{
public:
    int M_TRST;
};

class CItemSys
{
private:
    IStorage *m_pStorage;
    CGameContext *m_pGameServer;
    //const json_value *LoadJson(const char Index[64]);
    void LoadItems();
public:
    CGameContext *GameServer() { return m_pGameServer; }
    IStorage *Storage() { return m_pStorage; }
    CItemSys(CGameContext *pGameServer);

    vector<CItem *> m_Items;
};

#endif