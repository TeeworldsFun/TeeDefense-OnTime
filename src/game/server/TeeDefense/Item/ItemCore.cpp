/* 2022 - 2022 (C) Copyright ST-Chara */

#include "ItemCore.h"

#include <fstream>
#include <string>
#include <sstream>

CItemSys::CItemSys(CGameContext *pGameServer)
{
    m_pGameServer = pGameServer;
    dbg_msg("Test", "asdhgwkhdagsd");
    LoadJson("items.json");
	LoadItems();
}

void CItemSys::LoadJson(const std::string& FileName)
{
    using nlohmann::json;
    std::ifstream i(FileName);
    if(i.is_open())
    {
        m_Json.parse(i);
        i.close();
    }
    else
    {
        std::stringstream ss;
        ss << "could not open file '" << FileName << "'!";
        GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_DEBUG, "json", ss.str().c_str());
    }
}

void CItemSys::LoadItems()
{
	using nlohmann::json;
    json j = m_Json["Items"];

    if(j.is_array())
	{
        dbg_msg("Test", "Type = %s, size = %d", j.type_name(), j.size());
		for(unsigned i = 0; i < j.size(); ++i)
		{
            json Json = j[i];
            CItem TmpItem;
			dbg_msg("Test", "%d: %d", i, Json.value("Type", 0));
            
            //str_copy(TmpItem->m_Name, Json.value("Name", "SB").c_str(), sizeof(TmpItem->m_Name));
            TmpItem.m_Type = Json.value("Type", 0);
            
            if(!Json["Method"].empty())
            {
                json From = Json["Method"];
                for(json::iterator it = From.begin(); it; it++)
                {
                    json TempJson = From[j];
                    
                       
                    dbg_msg("Test", "%d: %d", string_to_int(TempJson.begin().key().c_str()), string_to_int(TempJson.begin().value().dump().c_str()));
                    // WORKING
                }
                // Assert for testing
                dbg_assert(false, "Test done.");
            }
            else if(!Json["MobID"].empty())
            {
                json From = Json["MobID"];
            }

            switch(TmpItem.m_Type)
            {

                // Material
                case TYPE_MATERIAL:

                break;

                // Weapon
                case TYPE_WEAPON:
                
                break;

                // Tool
                case TYPE_TOOL:
                
                break;

                // Turret
                case TYPE_TURRET:
                
                break;
                
                // Use
                case TYPE_USE:
                
                break;
            }
            m_Items.push_back(&TmpItem);
        }
    }
}