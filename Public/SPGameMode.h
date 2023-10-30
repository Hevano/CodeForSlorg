// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPMonster.h"
#include "GameFramework/GameModeBase.h"
#include "SPGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurnEvent, ASPMonster*, TurnMonster);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEncounterOverEvent, bool, bDidPlayerLose);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundEvent);

/**
 * 
 */
UCLASS()
class SPOOKYMONSTERS_API ASPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//All enemy monsters in the current encounter
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ASPMonster*> EnemyMonsters;

	//All monsters in the players current party
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ASPMonster*> PlayerMonsters;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimePerTurn { 1.f };

	UPROPERTY(BlueprintReadOnly)
	int RoundNumber { 0 };
	
	UPROPERTY(BlueprintReadWrite)
	int EncounterNumber { 0 };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Difficulty { 1.1f };

	//Todo: Replace this with a data table to spawn monsters based on difficulty
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ASPMonster>> MonsterCatalogue;

	UPROPERTY(BlueprintAssignable)
	FRoundEvent OnRoundStart;

	UPROPERTY(BlueprintAssignable)
	FRoundEvent OnRoundEnd;

	UPROPERTY(BlueprintAssignable)
	FTurnEvent OnTurnStart;

	UPROPERTY(BlueprintAssignable)
	FTurnEvent OnTurnEnd;
	
	UPROPERTY(BlueprintAssignable)
	FEncounterOverEvent OnEncounterEnd;

	//Starts a round
	UFUNCTION(BlueprintCallable)
	void StartRound();

	UFUNCTION()
	void ProgressRound();

	UFUNCTION()
	void EndRound();

	//Gets all monsters in the current encounter
	/*UFUNCTION(BlueprintCallable)
	TArray<TWeakObjectPtr<ASPMonster>> GetAllMonsters();*/

	UFUNCTION(BlueprintCallable)
	void PopulateEnemyEncounter(float DifficultyBudget);
	
	UFUNCTION(BlueprintCallable)
	void AddMonsterToParty(TSubclassOf<ASPMonster> MonsterToAdd);

	~ASPGameMode();


private:
	TArray<ASPMonster*> AllMonsters;

	//Tracks which monster's turn it is, index into AllMonsters array
	int CurrentRoundProgress { 0 };

	FTimerHandle TurnTimerHandle;

	ASPMonster* TurnMonster { nullptr };
	
};
