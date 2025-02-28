#include "cbase.h"
#include "func_streetpass_swap_zone.h"
#include "tf_passtime_ball.h"
#include "tf_passtime_logic.h"
#include "passtime_convars.h"
#include "tf_team.h"
#include "tf_player.h"
#include "tf_gamerules.h"
#include "tf_gamestats.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
BEGIN_DATADESC(CFuncStreetpassSwapZone)
	DEFINE_FUNCTION(CFuncStreetpassSwapZoneShim::StartTouch),
	DEFINE_FUNCTION(CFuncStreetpassSwapZoneShim::EndTouch)
END_DATADESC()

//-----------------------------------------------------------------------------
LINK_ENTITY_TO_CLASS(func_streetpass_swap_zone, CFuncStreetpassSwapZone);

//-----------------------------------------------------------------------------
IMPLEMENT_SERVERCLASS_ST(CFuncStreetpassSwapZone, DT_FuncStreetpassSwapZone)
	SendPropBool(SENDINFO(m_bTriggerDisabled))
END_SEND_TABLE()

//-----------------------------------------------------------------------------
CFuncStreetpassSwapZone::CFuncStreetpassSwapZone()
{
	m_bTriggerDisabled = false;
	m_iAttackTeam = TF_TEAM_BLUE;
}

void CFuncStreetpassSwapZone::Spawn()
{
	// HACK spawnflags to work around initially wrong understanding of how triggers work; needs rewrite and map changes
	AddSpawnFlags(GetSpawnFlags() << 24);
	RemoveSpawnFlags(0xffffff);
	AddSpawnFlags(SF_TRIGGER_ALLOW_PHYSICS);
	//AddSpawnFlags(SF_TRIGGER_ALLOW_CLIENTS | SF_TRIGGER_ALLOW_PHYSICS);

	InitTrigger();
	m_bTriggerDisabled = m_bDisabled;
	m_iAttackTeam = TF_TEAM_BLUE;
	SetThink( &CFuncStreetpassSwapZone::SwapThink );
	SetNextThink(gpGlobals->curtime);
}

void CFuncStreetpassSwapZone::SwapThink()
{
	SetNextThink(gpGlobals->curtime);
	m_bTriggerDisabled = m_bDisabled;
}

bool CFuncStreetpassSwapZone::CanTouchMe(CBaseEntity* pOther)
{
	bool isBall = false;
	if (CPasstimeBall* pBall = dynamic_cast<CPasstimeBall*>(pOther))
		isBall = true;

	return !m_bDisabled
		&& (pOther != 0)
		&& (g_pPasstimeLogic != 0)
		&& isBall;
}

void CFuncStreetpassSwapZone::ShimStartTouch(CBaseEntity* pOther)
{
	if (!CanTouchMe(pOther))
	{
		return;
	}

	CPasstimeBall* pBall = ToBall(pOther);
	Msg("BALL TEAM: %d\nATTACK TEAM: %d\n", pBall->m_iLaunchTeam, m_iAttackTeam);

	if (pBall->m_iLaunchTeam == m_iAttackTeam || pBall->m_iLaunchTeam == 0)
	{
		return;
	}

	//CALL, ACTIVATOR, CALLER
	variant_t emptyVariant;
	g_pPasstimeLogic->AcceptInput("SpawnBall", pOther, this, emptyVariant, 0);
	g_pPasstimeLogic->AcceptInput("SwapSides", pOther, this, emptyVariant, 0);

	m_iAttackTeam = pBall->m_iLaunchTeam;
}

void CFuncStreetpassSwapZone::ShimEndTouch(CBaseEntity* pOther)
{
	if (!CanTouchMe(pOther))
	{
		return;
	}
}