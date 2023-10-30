// Fill out your copyright notice in the Description page of Project Settings.


#include "SPHealthComponent.h"

// Sets default values for this component's properties
USPHealthComponent::USPHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USPHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USPHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float USPHealthComponent::TakeDamage(float Amount, AActor* Source)
{
	if(bIsDead) return 0.f; //Cannot take damage if dead
	
	OnPreTakeDamage.Broadcast(Amount, Source);
	HealthCurrent -= Amount;
	OnTakeDamage.Broadcast(Amount, Source);
	
	if(HealthCurrent <= 0)
	{
		HealthCurrent = 0;
		bIsDead = true;
		OnDeath.Broadcast(Source);
	}

	return Amount;
}

float USPHealthComponent::HealDamage(float Amount, AActor* Source)
{
	if(bIsDead && !bIsRevivable) return 0.f; //Cannot be healed if dead
	
	OnPreTakeDamage.Broadcast(Amount, Source);
	const float HealthNew = HealthCurrent + Amount;

	//Revival Check
	if(bIsDead && bIsRevivable)
	{
		bIsDead = false;
		OnRevive.Broadcast(Source);
	}

	//Cap healing to max health
	if(HealthNew > HealthMax)
	{
		HealthCurrent = HealthMax;
		Amount = HealthNew - HealthMax;
	} else
	{
		HealthCurrent = HealthNew;
	}
	
	OnHealDamage.Broadcast(Amount, Source);

	return Amount;
}
