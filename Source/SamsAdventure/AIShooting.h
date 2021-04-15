// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIShooting.generated.h"

/**
 * 
 */
UCLASS()
class SAMSADVENTURE_API AAIShooting : public AAIController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Bullet");
	TSubclassOf<class AEnemyBullet> AttackBlueprint;


	virtual void Tick(float DeltaTime) override;

};
