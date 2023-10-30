// Fill out your copyright notice in the Description page of Project Settings.


#include "SPPlayerController.h"

#include "SPGameMode.h"
#include "Kismet/GameplayStatics.h"

void ASPPlayerController::GetSelectionForUpgrade(FSPUpgradeData UpgradeData)
{
	UE_LOG(LogTemp, Warning, TEXT("Asking For Selection"));
	auto Gm = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UE_LOG(LogTemp, Warning, TEXT("Num of Player Characters: %i"), Gm->PlayerMonsters.Num());
	//Save upgrade for later, when selection is made
	PendingUpgradeData = MakeUnique<FSPUpgradeData>(UpgradeData);
	if(Gm && Gm->PlayerMonsters.Num() == 1)
	{
		//Apply Upgrade to Gm->PlayerMonsters[0]
		UpgradeSelectCallback(nullptr, Gm->PlayerMonsters[0]);
	} else
	{
		OnMonsterSelect.AddDynamic(this, &ASPPlayerController::UpgradeSelectCallback);
	}
}

void ASPPlayerController::SelectMonster(ASPMonster* MonsterToSelect)
{
	OnMonsterSelect.Broadcast(SelectedMonster.Get(), MonsterToSelect);
	SelectedMonster = MonsterToSelect;
}

void ASPPlayerController::UpgradeSelectCallback(ASPMonster* OldMonster, ASPMonster* NewMonster)
{
	//Apply upgrade to new monster here
	PendingUpgradeData->ApplyUpgradeToMonster(NewMonster);
	UE_LOG(LogTemp, Display, TEXT("Applying upgrade %s to monster %s"), *PendingUpgradeData->Title.ToString(), *NewMonster->GetName());
	OnMonsterSelect.RemoveDynamic(this, &ASPPlayerController::UpgradeSelectCallback);
	PendingUpgradeData.Reset();
	auto Gm = Cast<ASPGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	UE_LOG(LogTemp, Display, TEXT("Num of Player Characters: %i"), Gm->PlayerMonsters.Num());
	Gm->PopulateEnemyEncounter(Gm->Difficulty);
	Gm->StartRound();
}
