// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SamsAdventureGameMode.generated.h"

UCLASS()
class SAMSADVENTURE_API ASamsAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	ASamsAdventureGameMode();

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn points")
	FVector Checkpoint = FVector(0.f, 0.f, 0.f);

	class AMainCharacter* PlayerCharacter;
	class UPlayerHealth* PlayerHealthComp;

	virtual void Tick(float DeltaTime) override;
};
