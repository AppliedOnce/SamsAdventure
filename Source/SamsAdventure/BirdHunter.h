// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BirdEnemy.h"
#include "BirdHunter.generated.h"

/**
 * 
 */
UCLASS()
class SAMSADVENTURE_API ABirdHunter : public ABirdEnemy
{
	GENERATED_BODY()

public:
	ABirdHunter();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup");
	class USphereComponent* Collider = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup");
	class UStaticMeshComponent* OK = nullptr;

	UPROPERTY(EditAnywhere, Category = "Projectile");
	FVector AttackSpawnPoint{ 0.f, 0.f, 0.f };

	UPROPERTY(EditAnywhere, Category = "Projectile");
	TSubclassOf<class AEnemyBullet> AttackBlueprint;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
