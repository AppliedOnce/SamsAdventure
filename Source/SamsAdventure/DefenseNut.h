// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseNut.generated.h"

UCLASS()
class SAMSADVENTURE_API ADefenseNut : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefenseNut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup");
	class UStaticMeshComponent* Collider{ nullptr };

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
