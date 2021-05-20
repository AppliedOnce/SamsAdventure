// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoNut.h"
#include "BirdEnemy.generated.h"

UCLASS()
class SAMSADVENTURE_API ABirdEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABirdEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GotHit();




	UPROPERTY(EditAnywhere, Category = "Setup");
	TSubclassOf<AActor> PowerupBlueprint;

	UPROPERTY(EditAnywhere, Category = "Setup");
	TArray<TSubclassOf<AActor>> PowerupArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation");
	bool BirbAttackAnim = false;

	void birbAttackAnim();


private:
	int Health{ 0 };

	void SpawnPowerups();

};
