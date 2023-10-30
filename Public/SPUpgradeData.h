// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPMonsterAbility.h"
#include "SPUpgradeData.generated.h"
class ASPMonster;
/**
 * 
 */
USTRUCT(BlueprintType)
struct SPOOKYMONSTERS_API FSPUpgradeData : public FTableRowBase
{
	GENERATED_BODY()
public:
	FSPUpgradeData();
	~FSPUpgradeData();

	void ApplyUpgradeToMonster(ASPMonster* MonsterToUpgrade);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Desc;

	// Health Amount
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HealthMax { 0.f };

	// Percentage of damage blocked of the blood type (0-1)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BloodDefense{ 0.f };

	// Percentage of damage blocked of the bone type (0-1)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BoneDefense{ 0.f };

	// Percentage of damage blocked of the bile type (0-1)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BileDefense{ 0.f };

	// Percentage of damage blocked of the pschedelic type (0-1)
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PsychedelicDefense{ 0.f };

	// Percentage chance the attack will hit the target
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StandardAttackHitChance{ 0.0f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StandardAttackDamage{ 0.f };

	// Check if damage should be ignored from blood sources
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsImmuneToBlood{ false };

	// Check if damage should be ignored from bone sources
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsImmuneToBone{ false };

	// Check if damage should be ignored from bile sources
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsImmuneToBile{ false };

	// Check if damage should be ignored from pschedelic sources
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsImmuneToPsychedelic{ false };

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USPMonsterAbility> Ability;
};
