// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AmmoNut.h"
#include "BirdWarrior.generated.h"

UCLASS()
class SAMSADVENTURE_API ABirdWarrior : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABirdWarrior();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, Category = "AI")
		class USphereComponent* PlayerSensingSphere{ nullptr };


	UPROPERTY(EditAnywhere, Category = "Setup");
	TSubclassOf<AActor> PowerupBlueprint;

	UPROPERTY(EditAnywhere, Category = "Setup");
	TArray<TSubclassOf<AActor>> PowerupArray;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GotHit();
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	


private:
	int Health{ 0 };

	void SpawnPowerups();

};

