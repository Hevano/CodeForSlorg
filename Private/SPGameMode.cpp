// Fill out your copyright notice in the Description page of Project Settings.


#include "SPGameMode.h"

#include "SPHealthComponent.h"
#include "SPMonsterSpawnSlotList.h"
#include "Kismet/GameplayStatics.h"

void ASPGameMode::StartRound()
{
	AllMonsters.Empty();
	AllMonsters.Append(PlayerMonsters);
	AllMonsters.Append(EnemyMonsters);
	CurrentRoundProgress = 0;
	TurnMonster = nullptr;
	RoundNumber++;
	UE_LOG(LogTemp, Error, TEXT("Starting Round #:%i"), RoundNumber);
	UE_LOG(LogTemp, Error, TEXT("Number of player monsters #:%i"), PlayerMonsters.Num());
	OnRoundStart.Broadcast();
	GetWorldTimerManager().SetTimer(TurnTimerHandle, this, &ASPGameMode::ProgressRound, TimePerTurn);
}

void ASPGameMode::ProgressRound()
{
	if(TurnMonster) OnTurnEnd.Broadcast(TurnMonster);
	TurnMonster = AllMonsters[CurrentRoundProgress];
	UE_LOG(LogTemp, Error, TEXT("Starting Turn #:%i, %s"), CurrentRoundProgress, *TurnMonster->GetName());
	

	OnTurnStart.Broadcast(TurnMonster);
	TurnMonster->TakeAction();

	CurrentRoundProgress++;
	if(CurrentRoundProgress >= AllMonsters.Num())
	{
		EndRound();	
	} else
	{
		GetWorldTimerManager().SetTimer(TurnTimerHandle, this, &ASPGameMode::ProgressRound, TimePerTurn);
	}
}

void ASPGameMode::EndRound()
{
	OnRoundEnd.Broadcast();
	//True if all player monsters are dead
	bool isPlayerDead = true;
	for(auto PlayerMonster : PlayerMonsters)
	{
		isPlayerDead = isPlayerDead && PlayerMonster->HealthComponent->GetIsDead();
	}
	if(isPlayerDead)
	{
		OnEncounterEnd.Broadcast(true);
		RoundNumber = 0;
		return;
	}

	//True if all enemy monsters are dead
	bool isEnemyDead = true;
	for(auto EnemyMonster : EnemyMonsters)
	{
		isEnemyDead = isEnemyDead && EnemyMonster->HealthComponent->GetIsDead();
	}
	if(isEnemyDead)
	{
		for(auto EnemyMonster : EnemyMonsters)
		{
			EnemyMonster->SetLifeSpan(0.1f);
		}
		OnEncounterEnd.Broadcast(false);
		RoundNumber = 0;
		EncounterNumber++;
		return;
	}
	
	GetWorldTimerManager().SetTimer(TurnTimerHandle, this, &ASPGameMode::StartRound, TimePerTurn);
}

void ASPGameMode::PopulateEnemyEncounter(float DifficultyBudget)
{
	EnemyMonsters.Empty();
	TArray<AActor*> SlotArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("EnemyMonsterSlots"), SlotArray);
	ASPMonsterSpawnSlotList* MonsterSpawnSlotList = Cast<ASPMonsterSpawnSlotList>(SlotArray[0]);
	int SpawnIndex = 0;
	while(DifficultyBudget > 1.f && SpawnIndex < MonsterSpawnSlotList->SpawnSlots.Num())
	{
		int RandomChoice = FMath::RandRange(0, MonsterCatalogue.Num() - 1);
		auto SpawnedActor = GetWorld()->SpawnActor(MonsterCatalogue[RandomChoice].Get());
		SpawnedActor->SetActorLocation(MonsterSpawnSlotList->GetSlotLocation(SpawnIndex));
		SpawnIndex++;
		auto SpawnedMonster = Cast<ASPMonster>(SpawnedActor);
		SpawnedMonster->Team = ETeam::ENEMY;
		EnemyMonsters.Add(SpawnedMonster);
		DifficultyBudget -= 1.f;
	}

	//TODO: Apply buffs to enemy monsters for a budget cost
	
	Difficulty += 0.5f;
}

void ASPGameMode::AddMonsterToParty(TSubclassOf<ASPMonster> MonsterToAdd)
{
	TArray<AActor*> SlotArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("PlayerMonsterSlots"), SlotArray);
	ASPMonsterSpawnSlotList* MonsterSpawnSlotList = Cast<ASPMonsterSpawnSlotList>(SlotArray[0]);
	auto SpawnedActor = GetWorld()->SpawnActor(MonsterToAdd);
	SpawnedActor->SetActorLocation(MonsterSpawnSlotList->GetSlotLocation(PlayerMonsters.Num()));
	auto SpawnedMonster = Cast<ASPMonster>(SpawnedActor);
	PlayerMonsters.Add(SpawnedMonster);
	auto Gm = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Gm->PopulateEnemyEncounter(Gm->Difficulty);
	Gm->StartRound();
}

ASPGameMode::~ASPGameMode()
{
	UE_LOG(LogTemp, Display, TEXT("gamemode being destroyed!"));
}
