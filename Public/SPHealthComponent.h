// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPHealthComponent.generated.h"

//Event Signatures
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPreHealthEvent, float&, Amount, AActor*, EventSource);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPostHealthEvent, float, Amount, AActor*, DamageSource);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathEvent, AActor*, CauseOfDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOKYMONSTERS_API USPHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPHealthComponent();

	//Called before taking damage, can modify amount of damage taken
	UPROPERTY(BlueprintAssignable)
	FPreHealthEvent OnPreTakeDamage;

	//Called before healing damage, can modify amount of damage healed
	UPROPERTY(BlueprintAssignable)
	FPreHealthEvent OnPreHealDamage;

	//Called after taking damage
	UPROPERTY(BlueprintAssignable)
	FPostHealthEvent OnTakeDamage;

	//Called after healing damage
	UPROPERTY(BlueprintAssignable)
	FPostHealthEvent OnHealDamage;

	inline float GetHealthMax() const { return HealthMax; };
	inline float GetHealthCurrent() const { return HealthCurrent; };
	inline bool GetIsDead() const { return bIsDead; };

	inline void SetHealthMax(float NewHealthMax) { HealthMax = NewHealthMax; };
	inline void SetHealthCurrent(float NewHealthCurrent) { HealthCurrent = NewHealthCurrent; };



	//Called the first time health = 0
	UPROPERTY(BlueprintAssignable)
	FDeathEvent OnDeath;

	//Called if healing revives a dead monster
	UPROPERTY(BlueprintAssignable)
	FDeathEvent OnRevive;
	
protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HealthMax { 100.f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float HealthCurrent { 100.f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsDead { false };

	//Determines if healing can remove the isDead flag
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsRevivable { false };
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Returns amount of actual damage taken after effects applied
	UFUNCTION(BlueprintCallable)
	float TakeDamage(float Amount, AActor* Source = nullptr);

	//Returns amount of actual health restored after effects applied
	UFUNCTION(BlueprintCallable)
	float HealDamage(float Amount, AActor* Source = nullptr);
};
