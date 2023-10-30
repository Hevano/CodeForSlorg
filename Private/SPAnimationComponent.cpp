// Fill out your copyright notice in the Description page of Project Settings.


#include "SPAnimationComponent.h"

#include "PaperFlipbookComponent.h"
#include "SPHealthComponent.h"
#include "SPMonster.h"

// Sets default values for this component's properties
USPAnimationComponent::USPAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	AnimationOffset = FMath::FRand();
}


// Called when the game starts
void USPAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Sprite = GetOwner()->GetComponentByClass<UPaperFlipbookComponent>();
	auto MonsterOwner = Cast<ASPMonster>(GetOwner());
	MonsterOwner->OnDealDamage.AddDynamic(this, &USPAnimationComponent::AttackAnimationCallback);
	MonsterOwner->HealthComponent->OnTakeDamage.AddDynamic(this, &USPAnimationComponent::HitAnimationCallback);
}


// Called every frame
void USPAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CycleTime += DeltaTime * AnimationSpeed;

	switch(CurrentAnimation)
	{
		case EAnimationType::RUN:
			RunAnimation();
			break;
		case EAnimationType::HIT:
			HitAnimation();
			break;
		case EAnimationType::ATTACK:
			AttackAnimation();
			break;
		case EAnimationType::IDLE:
			IdleAnimation();
			break;
		default:
			break;
	}
}

void USPAnimationComponent::PlayAnimation(EAnimationType Animation)
{
	CycleTime = 0.f;
	CurrentAnimation = Animation;
}

void USPAnimationComponent::RunAnimation()
{
	//Pitch is left and right, yaw is back and forward, roll is along the z axis
	Sprite->SetRelativeRotation(FRotator(FMath::Sin(CycleTime*PI + AnimationOffset)*15.f,90,0));
	Sprite->SetRelativeLocation(FVector(0.f,0.f, FMath::Sin(CycleTime*PI + AnimationOffset)*15.f) - 90.f);
}

void USPAnimationComponent::IdleAnimation()
{
	//Pitch is left and right, yaw is back and forward, roll is along the z axis
	Sprite->SetRelativeRotation(FRotator(FMath::Sin(CycleTime*PI + AnimationOffset)*2.f,90,0));
	Sprite->SetRelativeLocation(FVector(0.f,0.f, FMath::Sin(CycleTime*PI + AnimationOffset)*15.f) - 90.f);
}

void USPAnimationComponent::HitAnimation()
{
	Direction = Cast<ASPMonster>(GetOwner())->Team == ETeam::PLAYER ? -1.f : 1.f;
	if(CycleTime > 1.f)
	{
		PlayAnimation(EAnimationType::IDLE);
	} else if(CycleTime > 0.5f)
	{
		float DisplacementCurve = -180.f * FMath::Pow(CycleTime - 0.65f, 2) + 10.f;
		//Pitch is left and right, yaw is back and forward, roll is along the z axis
		Sprite->SetRelativeRotation(FRotator(FMath::Sin(CycleTime*PI*5.f)*20.f,90,0));
		Sprite->SetRelativeLocation(FVector(0.f, DisplacementCurve * 10.f * -Direction, FMath::Sin(CycleTime*PI)*15.f) - 90.f);
	}
}

void USPAnimationComponent::AttackAnimation()
{
	Direction = Cast<ASPMonster>(GetOwner())->Team == ETeam::PLAYER ? -1.f : 1.f;
	float DisplacementCurve = -40.f * FMath::Pow(CycleTime - 0.5f, 2) + 10.f;
	//Pitch is left and right, yaw is back and forward, roll is along the z axis
	Sprite->SetRelativeRotation(FRotator(FMath::Sin(CycleTime*PI)*15.f,90,0));
	Sprite->SetRelativeLocation(FVector(0.f, DisplacementCurve * HitDistance * Direction, FMath::Sin(CycleTime*PI)*15.f) - 90.f);

	if(CycleTime > 1.f)
	{
		PlayAnimation(EAnimationType::IDLE);
	}
}

void USPAnimationComponent::RunAnimationCallback()
{
	PlayAnimation(EAnimationType::RUN);
}

void USPAnimationComponent::IdleAnimationCallback()
{
	PlayAnimation(EAnimationType::IDLE);
}

void USPAnimationComponent::HitAnimationCallback(float DamageAmount, AActor* Source)
{
	PlayAnimation(EAnimationType::HIT);
}

void USPAnimationComponent::AttackAnimationCallback(float DamageAmount, ASPMonster* DamageTarget)
{
	HitDistance = (GetOwner()->GetActorLocation() - DamageTarget->GetActorLocation()).Size() / 10.f;
	PlayAnimation(EAnimationType::ATTACK);
}
