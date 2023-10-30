// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PaperFlipbookComponent.h"
#include "SPMonster.h"
#include "SPAnimationComponent.generated.h"

UENUM(BlueprintType)
enum class EAnimationType : uint8 {
	RUN = 0,
	HIT = 1,
	ATTACK = 2,
	IDLE = 3,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPOOKYMONSTERS_API USPAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USPAnimationComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AnimationSpeed { 1.f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HitDistance { 100.f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EAnimationType CurrentAnimation = { EAnimationType::IDLE };

	UFUNCTION(BlueprintCallable)
	void PlayAnimation(EAnimationType Animation);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//Callbacks methods, because lambda's are too cool for Multicast delegates I guess
	UFUNCTION()
	void RunAnimationCallback();

	UFUNCTION()
	void IdleAnimationCallback();

	UFUNCTION()
	void HitAnimationCallback(float DamageAmount, AActor* Source);

	UFUNCTION()
	void AttackAnimationCallback(float DamageAmount, ASPMonster* DamageTarget);

private:
	float CycleTime { 0.f };
	float Direction { 1.f };
	float AnimationOffset { 0.f };

	UPaperFlipbookComponent* Sprite;

	void RunAnimation();
	void IdleAnimation();
	void HitAnimation();
	void AttackAnimation();

	
		
};
