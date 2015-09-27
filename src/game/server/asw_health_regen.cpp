#include "cbase.h"
#include "convar.h"
#include "entitylist.h"
#include "asw_weapon.h"
#include "asw_marine.h"
#include "asw_health_regen.h"
#include "asw_marine_profile.h"
#include "asw_gamerules.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar rm_health_regen_interval("rm_health_regen_interval", "5", FCVAR_NONE, "Interval between health regeneration", true, 0.01f, false, 0.0f);
ConVar rm_health_regen_amount("rm_health_regen_amount", "5", FCVAR_NONE, "Amount of health regenerating");
ConVar rm_health_decrease_amount("rm_health_decrease_amount", "7", FCVAR_NONE, "Amount of health decreasing during incapacitated");

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
			int regen_ammount = rm_health_regen_amount.GetInt();

			if (cur_health < max_health)
			{
				//Check if this marine is dead.
				if (cur_health < 1)
					continue;
				
				int result_health = cur_health + regen_ammount;
				if (result_health > max_health)
					result_health = max_health;
				
// 				if (pMarine->m_bKnockedOut)
// 				{
// 					result_health = cur_health - 3;
// 					if (result_health <= 0)
// 					{
// 						CTakeDamageInfo info(
// 							pMarine, 
// 							pMarine, 
// 							Vector(0,0,0), 
// 							GetAbsOrigin(), 
// 							100, 
// 							DMG_NEVERGIB);
// 						pMarine->TakeDamage(info);
// 					}
// 					else
// 					{
// 						pMarine->SetHealth(result_health);
// 					}
// 				}
// 				else
// 				{
					if (!pMarine->m_bKnockedOut && ASWGameRules()->m_iHpRegen)
						pMarine->SetHealth(result_health);

					// riflemod: incapacitated marines have decreasing hp
					if (pMarine->m_bKnockedOut)
					{
						int decreased_hp = pMarine->GetHealth() - rm_health_decrease_amount.GetInt();
						if (decreased_hp <= 0)
						{
							pMarine->SetKnockedOut(false);
							pMarine->SetHealth(1);
							// HACK
							int allow_revive = ASWGameRules()->m_iAllowRevive;
							ASWGameRules()->m_iAllowRevive = 0;
							CTakeDamageInfo info(this, this, Vector(0, 0, 0), GetAbsOrigin(), 100,
								DMG_NEVERGIB);
							pMarine->TakeDamage(info);
							ASWGameRules()->m_iAllowRevive = allow_revive;
						}
						else
							pMarine->SetHealth(decreased_hp);

					}
//				}
			}
		}
	}

	SetNextThink( gpGlobals->curtime + rm_health_regen_interval.GetFloat());
}
