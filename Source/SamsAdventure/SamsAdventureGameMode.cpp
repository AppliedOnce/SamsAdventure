// Fill out your copyright notice in the Description page of Project Settings.


#include "SamsAdventureGameMode.h"
#include "MainCharacter.h"
#include "PlayerHealth.h"

ASamsAdventureGameMode::ASamsAdventureGameMode()
{

}

void ASamsAdventureGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	PlayerHealthComp = PlayerCharacter->GetHealthComponent();
}

void ASamsAdventureGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter)
	{
		if (PlayerHealthComp->GetCurrentHp() <= 0)
		{
			PlayerHealthComp->IncreaseHp(PlayerHealthComp->GetMaxHp());
			PlayerCharacter->SetActorLocation(Checkpoint);
		}
	}
}

void ASamsAdventureGameMode::TeleportPlayerToStart()
{
	UE_LOG(LogTemp, Warning, TEXT("Teleport to: %s"), *Checkpoint.ToString())
	PlayerCharacter->SetActorLocation(Checkpoint);
}

void ASamsAdventureGameMode::SetCheckpoint(FVector NewCheckpoint)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting checkpoint to: %s"), *NewCheckpoint.ToString())
	Checkpoint = NewCheckpoint;
}