#include "cbase.h"
#include "convar.h"
#include "entitylist.h"
#include "asw_weapon.h"
#include "asw_marine.h"
#include "asw_health_regen.h"
#include "asw_marine_profile.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar asw_health_regen_interval("asw_health_regen_interval", "5", FCVAR_NONE, "Interval between health regeneration", true, 0.01f, false, 0.0f);
ConVar asw_health_regen_amount("asw_health_regen_amount", "5", FCVAR_NONE, "amount of health regenerating");

LINK_ENTITY_TO_CLASS( asw_health_regen, CASW_Health_Regen );

CASW_Health_Regen::CASW_Health_Regen()
{
}

CASW_Health_Regen::~CASW_Health_Regen()
{
}

void CASW_Health_Regen::Spawn()
{
	BaseClass::Spawn();
	SetNextThink( gpGlobals->curtime ); // Think now
}

void CASW_Health_Regen::Think()
{
	BaseClass::Think();
	CBaseEntity* pEntity = NULL;
	while ((pEntity = gEntList.FindEntityByClassname( pEntity, "asw_marine" )) != NULL)
	{
		CASW_Marine *pMarine = dynamic_cast<CASW_Marine*>(pEntity);
		if (pMarine)
		{
			int cur_health = pMarine->GetHealth();
			int max_health = pMarine->GetMaxHealth();
			int regen_ammount = asw_health_regen_amount.GetInt();

			if (cur_health < max_health)
			{
				//Check if this marine is dead.
				if (cur_health < 1)
					continue;
				
				int result_health = cur_health + regen_ammount;
				if (result_health > max_health)
					result_health = max_health;
				
				pMarine->SetHealth(result_health);
			}
		}
	}

	SetNextThink( gpGlobals->curtime + asw_health_regen_interval.GetFloat());
}