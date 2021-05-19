// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ICloudSpawner.generated.h"

UCLASS()
class SAMSADVENTURE_API AICloudSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AICloudSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup");
	float TimeBetweenSpawn = 60.f;

	float TimeAlive = 60.f;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Setup");
	FVector ICloudSpawnPoint{ 0.f, 200.f, 0.f };

	UPROPERTY(EditAnywhere, Category = "Setup");
	TSubclassOf<class AICloud> ICloudBlueprint;

};
