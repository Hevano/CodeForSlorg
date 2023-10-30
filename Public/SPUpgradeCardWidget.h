// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPUpgradeData.h"
#include "Blueprint/UserWidget.h"
#include "SPUpgradeCardWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpgradeSelectEvent, FSPUpgradeData, UpgradeData);

/**
 * 
 */
UCLASS()
class SPOOKYMONSTERS_API USPUpgradeCardWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FUpgradeSelectEvent OnUpgradeSelect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSPUpgradeData UpgradeData;

	UFUNCTION(BlueprintCallable)
	inline void CallOnUpgradeSelect() const { OnUpgradeSelect.Broadcast(UpgradeData); };
	
};
