#include "tower.h"
#include <game/server/player.h>
#include <game/server/entities/character.h>
#include <engine/shared/config.h>

const int Side = 16;
const int Radius = 128;

void CTower::Rotate(vec2* vertex, float x_orig, float y_orig, float angle)
{
	// FUCK THIS MATH
	float s = sin(angle);
	float c = cos(angle);

	vertex->x -= x_orig;
	vertex->y -= y_orig;

	float xnew = vertex->x * c - vertex->y * s;
	float ynew = vertex->x * s + vertex->y * c;

	vertex->x = xnew + x_orig;
	vertex->y = ynew + y_orig;
}

CTower::CTower(CGameWorld *pGameWorld, vec2 Pos, int Team) : CEntity(pGameWorld, CGameWorld::ENTTYPE_TOWER)
{
    m_Team = Team;
    m_Pos = Pos;
    m_Health = 500;
    m_Level = 1;
    m_Worker = 0.05f;
    for (unsigned i = 0; i < Side; i ++)
    {
        int id = Server()->SnapNewID();
        m_IDs.add(id);
    }

    for(int i = 0; i < 4; i ++)
        m_CoolDotID[i] = Server()->SnapNewID();
    m_ProximityRadius = 24;
    GameWorld()->InsertEntity(this);
}

void CTower::Tick()
{
    for(CCharacter *pChr = (CCharacter*) GameWorld()->FindFirst(CGameWorld::ENTTYPE_CHARACTER); pChr; pChr = (CCharacter *)pChr->TypeNext())
    {
        if(InTower(pChr->GetCID()))
        {
            // Every Second
            if(Server()->Tick()%50 == 0)
            {
                Broadcast(pChr->GetCID());
                if(pChr->m_LatestInput.m_Fire)
                    Upgrade();
            }
        }
    }
}

void CTower::Reset()
{

}

void CTower::Snap(int SnappingClient)
{
    vec2 vertices[4] = {
		vec2(m_Pos.x - (64/2), m_Pos.y - (64/2)),
		vec2(m_Pos.x + (64/2), m_Pos.y - (64/2)),
		vec2(m_Pos.x + (64/2), m_Pos.y + (64/2)),
		vec2(m_Pos.x - (64/2), m_Pos.y + (64/2))
	};
    float AngleStep = 2.0f * 3.1415926 / Side;


    if(m_CoolAngle >= 360)
        m_CoolAngle = 0;
    
    m_CoolAngle += (float)(((float)GetLevel() / (float)g_Config.m_SvTowerLevel)/4.0f);

	// FUCK THIS MATH（twice
    for (int i=0; i<4; i++)
    {
    	Rotate(&vertices[i], m_Pos.x, m_Pos.y, m_CoolAngle);
	}

    if(GetTeam() == TEAM_BLUE)
    {
        CNetObj_Laser *pObj1 = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_CoolDotID[0], sizeof(CNetObj_Laser)));
	    CNetObj_Laser *pObj2 = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_CoolDotID[1], sizeof(CNetObj_Laser)));
	    CNetObj_Laser *pObj3 = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_CoolDotID[2], sizeof(CNetObj_Laser)));
	    CNetObj_Laser *pObj4 = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_CoolDotID[3], sizeof(CNetObj_Laser)));
	    if(!pObj1 || !pObj2 || !pObj3 || !pObj4)
	    	return;

	    pObj1->m_X = (int)vertices[1].x;
	    pObj1->m_Y = (int)vertices[1].y;
	    pObj1->m_FromX = (int)vertices[0].x;
	    pObj1->m_FromY = (int)vertices[0].y;
	    pObj2->m_X = (int)vertices[2].x;
	    pObj2->m_Y = (int)vertices[2].y;
	    pObj2->m_FromX = (int)vertices[1].x;
	    pObj2->m_FromY = (int)vertices[1].y;
	    pObj3->m_X = (int)vertices[3].x;
	    pObj3->m_Y = (int)vertices[3].y;
	    pObj3->m_FromX = (int)vertices[2].x;
	    pObj3->m_FromY = (int)vertices[2].y;
	    pObj4->m_X = (int)vertices[0].x;
	    pObj4->m_Y = (int)vertices[0].y;
	    pObj4->m_FromX = (int)vertices[3].x;
	    pObj4->m_FromY = (int)vertices[3].y;

	    pObj1->m_StartTick = Server()->Tick();
	    pObj2->m_StartTick = Server()->Tick();
	    pObj3->m_StartTick = Server()->Tick();
	    pObj4->m_StartTick = Server()->Tick();
    }
    else
    {
        CNetObj_Projectile *pObj1 = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_CoolDotID[0], sizeof(CNetObj_Projectile)));
	    CNetObj_Projectile *pObj2 = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_CoolDotID[1], sizeof(CNetObj_Projectile)));
	    CNetObj_Projectile *pObj3 = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_CoolDotID[2], sizeof(CNetObj_Projectile)));
	    CNetObj_Projectile *pObj4 = static_cast<CNetObj_Projectile *>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_CoolDotID[3], sizeof(CNetObj_Projectile)));
	    if(!pObj1 || !pObj2 || !pObj3 || !pObj4)
	    	return;

	    pObj1->m_X = (int)vertices[1].x;
	    pObj1->m_Y = (int)vertices[1].y;

	    pObj2->m_X = (int)vertices[2].x;
	    pObj2->m_Y = (int)vertices[2].y;

	    pObj3->m_X = (int)vertices[3].x;
	    pObj3->m_Y = (int)vertices[3].y;

	    pObj4->m_X = (int)vertices[0].x;
	    pObj4->m_Y = (int)vertices[0].y;

	    pObj1->m_StartTick = Server()->Tick();
	    pObj2->m_StartTick = Server()->Tick();
	    pObj3->m_StartTick = Server()->Tick();
	    pObj4->m_StartTick = Server()->Tick();

        pObj1->m_Type = WEAPON_GRENADE;
        pObj2->m_Type = WEAPON_SHOTGUN;
        pObj3->m_Type = WEAPON_RIFLE;
        pObj4->m_Type = WEAPON_GUN;
    }
    for(int i=0; i<Side; i++)
	{
		vec2 PartPosStart = m_Pos + vec2(Radius * cos(AngleStep*i), Radius * sin(AngleStep*i));
		vec2 PartPosEnd = m_Pos + vec2(Radius * cos(AngleStep*(i+1)), Radius * sin(AngleStep*(i+1)));
		
		CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_IDs[i], sizeof(CNetObj_Laser)));
		if(!pObj)
			return;

		pObj->m_X = (int)PartPosStart.x;
		pObj->m_Y = (int)PartPosStart.y;
		pObj->m_FromX = (int)PartPosEnd.x;
		pObj->m_FromY = (int)PartPosEnd.y;
		pObj->m_StartTick = Server()->Tick()+clamp(GetHealth(), 0, 7)-7;
	}
}

bool CTower::Upgrade()
{
    m_Level++;
}

void CTower::TakeDamage(int Owner, int Damage)
{

}

void CTower::FillSoul(int Num)
{

}

void CTower::Broadcast(int CID)
{
    GameServer()->SendBroadcast_VL("Tower Health: {VAL}/{VAL}" \
                                  "\nTower Level: {VAL}/{VAL}", \
                                  CID, \
                                  GetHealth(), g_Config.m_SvTowerHealth, \
                                  GetLevel(), g_Config.m_SvTowerLevel);
}

bool CTower::InTower(int ClientID)
{
    return ((GameServer()->GetPlayerChar(ClientID) && \
            distance(GameServer()->GetPlayerChar(ClientID)->m_Pos, m_Pos) < m_ProximityRadius+Radius) \
             ? true : false);
}