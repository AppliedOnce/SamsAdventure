// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BirdAIController.generated.h"

/**
 * 
 */
UCLASS()
class SAMSADVENTURE_API ABirdAIController : public AAIController
{
	GENERATED_BODY()
<<<<<<< Updated upstream
public:
	virtual void BeginPlay() override;


=======
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

>>>>>>> Stashed changes
	virtual void Tick(float DeltaTime) override;

};
