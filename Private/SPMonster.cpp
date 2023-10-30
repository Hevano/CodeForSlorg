// Fill out your copyright notice in the Description page of Project Settings.


#include "SPMonster.h"
#include "SPHealthComponent.h"
#include "SPStatsComponent.h"

ASPMonster::ASPMonster()
{
	HealthComponent = CreateDefaultSubobject<USPHealthComponent>(TEXT("Health"));
	StatsComponent = CreateDefaultSubobject<USPStatsComponent>(TEXT("Stats"));
	HealthComponent->OnDeath.AddDynamic(this, &ASPMonster::Die);
}

void ASPMonster::TakeAction()
{
	if(HealthComponent->GetIsDead()) return;
	OnTakeAction.Broadcast();
}

void ASPMonster::Die(AActor* CauseOfDeath)
{
	//Todo: Death logic
}

float ASPMonster::DamageTargetMonsterHealth(float Amount, USPHealthComponent* TargetHealthComponent)
{
	const auto CompOwner = Cast<ASPMonster>(TargetHealthComponent->GetOwner());
	return DamageTargetMonster(Amount, CompOwner);
}

float ASPMonster::DamageTargetMonster(float Amount, ASPMonster* Target)
{
	//TODO: Think of a way to prevent infinite looping if two monsters with thorns-style effects impact each other (maybe once-per-turn limit?)
	OnPreDealDamage.Broadcast(Amount, Target);
	const float OriginalHealth = Target->HealthComponent->GetHealthCurrent();
	Target->HealthComponent->TakeDamage(Amount, this);
	OnDealDamage.Broadcast(Amount, Target);

	return OriginalHealth - Target->HealthComponent->GetHealthCurrent();
}
