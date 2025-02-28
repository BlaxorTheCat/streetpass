#include "cbase.h"
#include "c_func_streetpass_swap_zone.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
IMPLEMENT_CLIENTCLASS_DT(C_FuncStreetpassSwapZone, DT_FuncStreetpassSwapZone, CFuncStreetpassSwapZone)
	RecvPropBool(RECVINFO(m_bTriggerDisabled))
END_RECV_TABLE()
