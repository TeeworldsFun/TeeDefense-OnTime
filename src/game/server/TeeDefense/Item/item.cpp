/* 2022 - 2022 (C) Copyright ST-Chara */

#include "item.h"

CItemSys::CItemSys(CGameContext *pGameServer)
{
    m_pGameServer = pGameServer;
    thread(LoadItems);
}

/*const json_value *CItemSys::LoadJson(const char Index[64])
{
    char aFileBuf[512];
	str_format(aFileBuf, sizeof(aFileBuf), "items.json");
	const IOHANDLE File = Storage()->OpenFile(aFileBuf, IOFLAG_READ, IStorage::TYPE_ALL);
    
	if(!File)
	{
		GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "Item Loader", "Probably deleted or error when the file is invalid.");
		return;
	}
	
	const int FileSize = (int)io_length(File);
	char* pFileData = (char*)malloc(FileSize);
	io_read(File, pFileData, FileSize);
	io_close(File);

	// parse json data
	json_settings JsonSettings;
	mem_zero(&JsonSettings, sizeof(JsonSettings));
	char aError[256];
	json_value* pJsonData = json_parse_ex(&JsonSettings, pFileData, FileSize, aError);
	free(pFileData);
    if(aError)
        dbg_msg("LoadJson - Error", "Error: %s", aError);

	if(pJsonData == nullptr)
	{
		GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "LoadJson - THE FUCK!", "WHERE IS MY JSON'S DATA????");
		return;
	}

    const json_value &rStart = (*pJsonData)[Index];
    return &rStart;
}*/

void CItemSys::LoadItems()
{
    char aFileBuf[512];
	str_format(aFileBuf, sizeof(aFileBuf), "items.json");
	const IOHANDLE File = Storage()->OpenFile(aFileBuf, IOFLAG_READ, IStorage::TYPE_ALL);
    
	if(!File)
	{
		GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "Item Loader", "Probably deleted or error when the file is invalid.");
		return;
	}
	
	const int FileSize = (int)io_length(File);
	char* pFileData = (char*)malloc(FileSize);
	io_read(File, pFileData, FileSize);
	io_close(File);

	// parse json data
	json_settings JsonSettings;
	mem_zero(&JsonSettings, sizeof(JsonSettings));
	char aError[256];
	json_value* pJsonData = json_parse_ex(&JsonSettings, pFileData, FileSize, aError);
	free(pFileData);
    if(aError)
        dbg_msg("LoadJson - Error", "Error: %s", aError);

	if(pJsonData == nullptr)
	{
		GameServer()->Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "LoadJson - THE FUCK!", "WHERE IS MY JSON'S DATA????");
		return;
	}
    const json_value& rJson = (*pJsonData)["items"];
    if(rJson.type == json_array)
	{
		for(unsigned i = 0; i < rJson.u.array.length; ++i)
		{
            switch (rJson[i]["Type"].u.integer)
            {
            case TYPE_MATERIAL:
                
                break;
            
            case TYPE_WEAPON:
                /* code */
                break;
            
            case TYPE_TOOL:
                /* code */
                break;
            
            case TYPE_TURRET:
                /* code */
                break;
            
            case TYPE_USE:
                /* code */
                break;
            
            default:
                break;
            }

            
        }
    }
}