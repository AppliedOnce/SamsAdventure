// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TotemTrap.generated.h"

UCLASS()
class SAMSADVENTURE_API ATotemTrap : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATotemTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category = Setup);
	class UStaticMeshComponent* OurVisibleComponent{ nullptr };

	UPROPERTY(EditAnywhere, Category = Setup);
	class USphereComponent* OurCollider{ nullptr };

	bool InRange = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		class AAIController* AIController{ nullptr };

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			int32 OtherBodyIndex);

	void Shooting();

	float ShootingRythm{ 0.f };

	UPROPERTY(EditAnywhere, Category = "Projectile");
	TSubclassOf<class AEnemyBullet> AttackBlueprint;

	UPROPERTY(EditAnywhere, Category = "Projectile");
	FVector AttackSpawnPoint{ 100.f, 0.f, 0.f };
};
