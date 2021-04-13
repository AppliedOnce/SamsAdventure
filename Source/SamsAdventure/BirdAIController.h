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
public:
	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;

};
