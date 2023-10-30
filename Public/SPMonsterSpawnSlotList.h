// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InterpToMovementComponent.h"
#include "GameFramework/Actor.h"
#include "SPMonsterSpawnSlotList.generated.h"

UCLASS()
class SPOOKYMONSTERS_API ASPMonsterSpawnSlotList : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FVector> SpawnSlots;
	
	// Sets default values for this actor's properties
	ASPMonsterSpawnSlotList();
	
	UFUNCTION(BlueprintCallable)
	FVector GetSlotLocation(int SlotIndex);

};
