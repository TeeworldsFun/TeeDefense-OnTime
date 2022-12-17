#ifndef TD_TOWER_H
#define TD_TOWER_H

#include <game/server/entity.h>
#include <game/server/gamecontext.h>

class CTower : public CEntity
{
private:
    int m_Team;
    int m_Health;
    int m_Level;
    int m_Soul;

    int m_CoolDotID[4];
    float m_CoolAngle;
    float m_Worker; // USELESS, I CAN USE ANOTHER FUCTION BUT IDK WHAT IS IT..................
public:
    CTower(CGameWorld *pGameWorld, vec2 Pos, int Team);

    // Core
    virtual void Tick();
    virtual void Reset();
	virtual void Snap(int SnappingClient);

    // Val
    int GetTeam() { return m_Team; };
    int GetHealth() { return m_Health; };
    int GetLevel() { return m_Level; };

    // Event
    bool Upgrade(); 
    void TakeDamage(int Owner, int Damage);
    void FillSoul(int Num);
    void Broadcast(int CID);
    bool InTower(int ClientID);
    array<int > m_IDs;

    // SOME COOL THINGS!
    void Rotate(vec2* vertex, float x_orig, float y_orig, float angle);
};

#endif