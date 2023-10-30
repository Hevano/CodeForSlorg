// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPUpgradeData.h"
#include "GameFramework/PlayerController.h"
#include "SPPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMonsterSelectEvent, ASPMonster*, OldMonster, ASPMonster*, NewMonster);

class ASPMonster;
/**
 * 
 */
UCLASS()
class SPOOKYMONSTERS_API ASPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TWeakObjectPtr<ASPMonster> SelectedMonster;

	UPROPERTY(BlueprintAssignable)
	FMonsterSelectEvent OnMonsterSelect;

	UFUNCTION(BlueprintCallable)
	void GetSelectionForUpgrade(FSPUpgradeData UpgradeData);

	UFUNCTION(BlueprintCallable)
	void SelectMonster(ASPMonster* MonsterToSelect);

protected:
	UFUNCTION()
	void UpgradeSelectCallback(ASPMonster* OldMonster, ASPMonster* NewMonster);
	
private:
	TUniquePtr<FSPUpgradeData> PendingUpgradeData; 
};
