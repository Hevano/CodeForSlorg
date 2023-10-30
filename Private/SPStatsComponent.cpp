// Fill out your copyright notice in the Description page of Project Settings.


#include "SPStatsComponent.h"

// Sets default values for this component's properties
USPStatsComponent::USPStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USPStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void USPStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float USPStatsComponent::ModifyDamage(float Amount, EDamageType Type)
{
	switch (Type) {
	case EDamageType::BLOOD:
		if (bIsImmuneToBlood) {
			Amount = 0;
		}
		else {
			Amount = Amount - (Amount * BloodDefense);
		}
	case EDamageType::BONE:
		if (bIsImmuneToBone) {
			Amount = 0;
		}
		else {
			Amount = Amount - (Amount * BoneDefense);
		}
	case EDamageType::BILE:
		if (bIsImmuneToBile) {
			Amount = 0;
		}
		else {
			Amount = Amount - (Amount * BileDefense);
		}
	case EDamageType::PSYCHEDELIC:
		if (bIsImmuneToPsychedelic) {
			Amount = 0;
		}
		else {
			Amount = Amount - (Amount * PsychedelicDefense);
		}
	}
	return Amount;
}