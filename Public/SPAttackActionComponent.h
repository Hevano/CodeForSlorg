// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPStatsComponent.h"
#include "SPAttackActionComponent.generated.h"

UENUM(BlueprintType)
enum class EAttackTargetType : uint8 {
	RANDOM = 0,
	ALL = 1,
	FIRST = 2,
	LAST = 3,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMissEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOKYMONSTERS_API USPAttackActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPAttackActionComponent();


	FText AttackTitle = FText::FromString("Default Attack");

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EDamageType DamageType { EDamageType::BONE };

	//Determines who will be the target of this attack
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EAttackTargetType AttackTarget { EAttackTargetType::RANDOM };;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageModifier { 1.f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HitChanceModifier { 1.f };

	UPROPERTY(BlueprintAssignable)
	FMissEvent OnAttackMiss;
	
	UFUNCTION(BlueprintCallable)
	void UseAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
		
};
