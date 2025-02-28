
#ifndef FUNC_STREETPASS_SWAP_ZONE_H
#define FUNC_STREETPASS_SWAP_ZONE_H
#ifdef _WIN32
#pragma once
#endif

#include "triggers.h"

class CPasstimeBall;

class CFuncStreetpassSwapZoneShim : public CBaseTrigger
{
public:
	virtual void StartTouch(CBaseEntity* pOther) OVERRIDE { ShimStartTouch(pOther); }
	virtual void EndTouch(CBaseEntity* pOther) OVERRIDE { ShimEndTouch(pOther); }

private:
	virtual void ShimStartTouch(CBaseEntity* pOther) = 0;
	virtual void ShimEndTouch(CBaseEntity* pOther) = 0;
};

//------------------------------------------------------------------//
//	CFuncStreetpassSwapZone
//
//	this is the trigger that will enable the swaping of sides
//	when the ball touches it
//------------------------------------------------------------------//
class CFuncStreetpassSwapZone : public CFuncStreetpassSwapZoneShim, public TAutoList<CFuncStreetpassSwapZone>
{
public:
	DECLARE_CLASS(CFuncStreetpassSwapZone, CFuncStreetpassSwapZoneShim);
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	CFuncStreetpassSwapZone();
	virtual void Spawn() OVERRIDE;
	bool IsDisabled() const { return m_bTriggerDisabled; }
	void OnTouch(int team);
private:
	virtual void ShimStartTouch(CBaseEntity* pOther) OVERRIDE;
	virtual void ShimEndTouch(CBaseEntity* pOther) OVERRIDE;
	bool CanTouchMe(CBaseEntity* pOther);
	void SwapThink();

	CNetworkVar(bool, m_bTriggerDisabled);

	int m_iAttackTeam;
};

#endif