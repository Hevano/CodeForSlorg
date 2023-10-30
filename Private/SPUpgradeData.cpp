// Fill out your copyright notice in the Description page of Project Settings.


#include "SPUpgradeData.h"

#include "SPHealthComponent.h"
#include "SPMonster.h"
#include "SPStatsComponent.h"

FSPUpgradeData::FSPUpgradeData()
{
}

FSPUpgradeData::~FSPUpgradeData()
{
}

void FSPUpgradeData::ApplyUpgradeToMonster(ASPMonster* MonsterToUpgrade)
{
	// Health Amount
	MonsterToUpgrade->HealthComponent->SetHealthMax(MonsterToUpgrade->HealthComponent->GetHealthMax() + HealthMax);
	if(HealthMax != 0) MonsterToUpgrade->HealthComponent->HealDamage(HealthMax);
	

	// Percentage of damage blocked of the blood type (0-1)
	MonsterToUpgrade->StatsComponent->BloodDefense += BloodDefense;
	

	// Percentage of damage blocked of the bone type (0-1)
	MonsterToUpgrade->StatsComponent->BoneDefense += BoneDefense;

	// Percentage of damage blocked of the bile type (0-1)
	MonsterToUpgrade->StatsComponent->BileDefense += BileDefense;

	// Percentage of damage blocked of the pschedelic type (0-1)
	MonsterToUpgrade->StatsComponent->PsychedelicDefense += PsychedelicDefense;

	// Percentage chance the attack will hit the target
	MonsterToUpgrade->StatsComponent->StandardAttackHitChance += StandardAttackHitChance;

	MonsterToUpgrade->StatsComponent->StandardAttackDamage += StandardAttackDamage;

	// Check if damage should be ignored from blood sources
	MonsterToUpgrade->StatsComponent->bIsImmuneToBlood = MonsterToUpgrade->StatsComponent->bIsImmuneToBlood || bIsImmuneToBlood;

	// Check if damage should be ignored from bone sources
	MonsterToUpgrade->StatsComponent->bIsImmuneToBone = MonsterToUpgrade->StatsComponent->bIsImmuneToBone || bIsImmuneToBone;

	// Check if damage should be ignored from bile sources
	MonsterToUpgrade->StatsComponent->bIsImmuneToBile = MonsterToUpgrade->StatsComponent->bIsImmuneToBile || bIsImmuneToBile;

	// Check if damage should be ignored from pschedelic sources
	MonsterToUpgrade->StatsComponent->bIsImmuneToPsychedelic = MonsterToUpgrade->StatsComponent->bIsImmuneToPsychedelic || bIsImmuneToPsychedelic;

	MonsterToUpgrade->AddComponentByClass(Ability.Get(), false, {}, false);
}
