// Fill out your copyright notice in the Description page of Project Settings.


#include "SPAttackActionComponent.h"

#include "SPGameMode.h"
#include "SPMonster.h"
#include "SPHealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USPAttackActionComponent::USPAttackActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USPAttackActionComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto MonsterOwner = Cast<ASPMonster>(GetOwner());
	MonsterOwner->OnTakeAction.AddDynamic(this, &USPAttackActionComponent::UseAttack);
	
}

void USPAttackActionComponent::UseAttack()
{
	auto Gm = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	const auto MonsterOwner = Cast<ASPMonster>(GetOwner());
	TArray<ASPMonster*>& ListToSelectFrom = (MonsterOwner->Team == ETeam::PLAYER) ? Gm->EnemyMonsters : Gm->PlayerMonsters;
	
	TArray<ASPMonster*> Targets;
	switch (AttackTarget)
	{
		case EAttackTargetType::RANDOM:
			{
				auto ListSubset = ListToSelectFrom.FilterByPredicate([](const auto& Monster)
				{
					return !Monster->HealthComponent->GetIsDead();
				});
				const int RandomChoice = FMath::RandRange(0, ListSubset.Num() - 1);
				if(!ListSubset.IsEmpty()) Targets.Add(ListSubset[RandomChoice]);
			}
			break;
		case EAttackTargetType::ALL:
			Targets.Append(ListToSelectFrom);
			break;
		case EAttackTargetType::FIRST:
			{
				auto SelectedMonster = ListToSelectFrom.FindByPredicate([](const auto& Monster)
			   {
				   return !Monster->HealthComponent->GetIsDead();
			   });
				if(!SelectedMonster) return;
				Targets.Add(*SelectedMonster);
			}
			break;
		case EAttackTargetType::LAST:
			{
				auto SelectedMonster = ListToSelectFrom.FindLastByPredicate([](const auto& Monster)
			   {
				   return !Monster->HealthComponent->GetIsDead();
			   });
				if(SelectedMonster == INDEX_NONE) return;
				Targets.Add(ListToSelectFrom[SelectedMonster]);
			}
			break;
		default:
			break;
	}

	for(auto Target : Targets)
	{
		//Miss if we roll higher than our hit chance (meaning chance of 1 or greater will always hit)
		const float HitRoll = FMath::FRand();
		if(HitRoll > MonsterOwner->StatsComponent->StandardAttackHitChance * HitChanceModifier)
		{
			UE_LOG(LogTemp, Warning, TEXT("ATTACK MISSED!"));
			OnAttackMiss.Broadcast();
			continue;
		}

		const float CalculatedDamage = Target->StatsComponent->ModifyDamage(MonsterOwner->StatsComponent->StandardAttackDamage * DamageModifier, DamageType);
		MonsterOwner->DamageTargetMonster(CalculatedDamage, Target);
	}
}

