// Fill out your copyright notice in the Description page of Project Settings.


#include "SPMonsterAbility.h"

#include "SPAttackActionComponent.h"
#include "SPHealthComponent.h"
#include "SPMonster.h"

// Sets default values for this component's properties
USPMonsterAbility::USPMonsterAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USPMonsterAbility::AddDamageReflection(EDamageType DamageType)
{
	auto MonsterOwner = Cast<ASPMonster>(GetOwner());
	MonsterOwner->HealthComponent->OnPreTakeDamage.AddDynamic(this, &USPMonsterAbility::ReflectDamage);
}

void USPMonsterAbility::ReflectDamage(float& Amount, AActor* EventSource)
{
	auto EnemyMonster = Cast<ASPMonster>(EventSource);
	auto MonsterOwner = Cast<ASPMonster>(GetOwner());
	if(!EnemyMonster) return;

	if(EnemyMonster->GetComponentByClass<USPAttackActionComponent>()->DamageType != DamageTypeToReflect) return;

	MonsterOwner->DamageTargetMonster(Amount, EnemyMonster);
	Amount = 0;
}

// Called when the game starts
void USPMonsterAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USPMonsterAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

