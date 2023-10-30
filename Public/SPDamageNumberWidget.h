// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPDamageNumberWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPOOKYMONSTERS_API USPDamageNumberWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
	
	//Calculates the scale of the damage number based on the damage
	UFUNCTION(BlueprintCallable)
	float GetScaleFromDamage(float Damage) const;
};
