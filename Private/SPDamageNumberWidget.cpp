// Fill out your copyright notice in the Description page of Project Settings.


#include "SPDamageNumberWidget.h"
#include "GenericPlatform/GenericPlatformMath.h"

float USPDamageNumberWidget::GetScaleFromDamage(float Damage) const
{
	//Remap Damage to be between 0 and 2
	float RemappedDamage = Damage / 100.f;
	RemappedDamage = FMath::Max(-2, RemappedDamage);
	RemappedDamage = FMath::Min(2, RemappedDamage);
	RemappedDamage = FMath::Abs(RemappedDamage);
	
	// Function found through experimenting with Desmos. Sorry if it looks ugly ;)
	return -(RemappedDamage - 4) * (RemappedDamage) + 0.5f;
}
