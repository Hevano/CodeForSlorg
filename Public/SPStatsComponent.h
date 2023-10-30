// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPStatsComponent.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8 {
	BLOOD = 0 UMETA(DisplayName = "BloodType"),
	BONE = 1 UMETA(DisplayName = "BoneType"),
	BILE = 2 UMETA(DisplayName = "BileType"),
	PSYCHEDELIC = 3 UMETA(DisplayName = "PsychedlicType"),
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPOOKYMONSTERS_API USPStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USPStatsComponent();

	inline float GetBloodDefense() const { 
		if (bIsImmuneToBlood)
			return 100.0f;
		return BloodDefense; 
	};
	inline float GetBoneDefense() const {
		if (bIsImmuneToBone)
			return 100.0f;
		return BoneDefense; 
	};
	inline float GetBileDefense() const { 
		if (bIsImmuneToBile)
			return 100.0f;
		return BileDefense;
	};
	inline float GetPsychedelicDefense() const { 
		if (bIsImmuneToPsychedelic)
			return 100.0f;
		return PsychedelicDefense; 
	};
	
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
	float StandardAttackHitChance{ 0.75f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StandardAttackDamage{ 50.f };

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

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Returns amount of actual damage taken after effects applied
	UFUNCTION(BlueprintCallable)
	float ModifyDamage(float Amount, EDamageType Type);

};
