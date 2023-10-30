// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPStatsComponent.h"
#include "Components/ActorComponent.h"
#include "SPMonsterAbility.generated.h"


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOKYMONSTERS_API USPMonsterAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPMonsterAbility();
	
	UFUNCTION(BlueprintCallable)
	void AddDamageReflection(EDamageType DamageType);

	UFUNCTION()
	void ReflectDamage(float& Amount, AActor* EventSource);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	EDamageType DamageTypeToReflect;
		
};
