
#ifndef C_FUNC_STREETPASS_SWAP_ZONE_H
#define C_FUNC_STREETPASS_SWAP_ZONE_H
#ifdef _WIN32
#pragma once
#endif

#include "util_shared.h"
#include "c_baseentity.h"

//------------------------------------------------------------------//
class C_FuncStreetpassSwapZone : public C_BaseEntity, public TAutoList<C_FuncStreetpassSwapZone>
{
public:
	DECLARE_CLASS(C_FuncStreetpassSwapZone, C_BaseEntity);
	DECLARE_CLIENTCLASS();
	bool BSwapZoneDisabled() { return m_bTriggerDisabled; }
private:
	CNetworkVar(bool, m_bTriggerDisabled);
};

#endif