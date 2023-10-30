// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "SPMonster.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPreDealDamageEvent, float&, DamageAmount, ASPMonster*, DamageTarget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPostDealDamageEvent, float, DamageAmount, ASPMonster*, DamageTarget);


UENUM(BlueprintType)
enum class ETeam : uint8 {
	PLAYER = 0 UMETA(DisplayName = "PlayerTeam"),
	ENEMY = 1  UMETA(DisplayName = "EnemyTeam"),
};

/**
 * 
 */
UCLASS()
class SPOOKYMONSTERS_API ASPMonster : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class USPHealthComponent* HealthComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class USPStatsComponent* StatsComponent;

	//Determines if this is an enemy monster or a monster on the player's team
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ETeam Team;
	
	UPROPERTY(BlueprintAssignable)
	FActionEvent OnTakeAction;

	//Called before monster deals damage, can modify amount of damage done
	UPROPERTY(BlueprintAssignable)
	FPreDealDamageEvent OnPreDealDamage;

	//Called when monster deals damage
	UPROPERTY(BlueprintAssignable)
	FPostDealDamageEvent OnDealDamage;

	//Logic to run when monster takes their action
	UFUNCTION(BlueprintCallable)
	virtual void TakeAction();

	//Logic to run when character dies
	UFUNCTION(BlueprintCallable)
	virtual void Die(AActor* CauseOfDeath);

	//Convenience function deal damage with reference to target's health component
	UFUNCTION(BlueprintCallable)
	float DamageTargetMonsterHealth(float Amount, USPHealthComponent* TargetHealthComponent);

	//Returns actual damage done after effects are applied
	UFUNCTION(BlueprintCallable)
	float DamageTargetMonster(float Amount, ASPMonster* Target);

	ASPMonster();

	
	
};
