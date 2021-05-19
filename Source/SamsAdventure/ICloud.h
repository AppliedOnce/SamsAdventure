// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ICloud.generated.h"

UCLASS()
class SAMSADVENTURE_API AICloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AICloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup");
	UStaticMeshComponent* OurVisibleComponent{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Setup");
	class USphereComponent* Collider{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Setup");
	float Speed = 100.f;

	float TimePresent = 0.f;

	UPROPERTY(EditAnywhere, Category = "Setup");
	float TimeToGetToTheOtherSide = 6.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AICloudSpawner* Spawner{ nullptr };
};
