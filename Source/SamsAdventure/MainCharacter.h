// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class SAMSADVENTURE_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera");
	class USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera");
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, Category = "Projectile");
	TSubclassOf<class ABulletNut> BulletBlueprint;


	UPROPERTY(EditAnywhere, Category = "Projectile");
	FVector BulletSpawnPoint{ 100.f, 0.f, 0.f };

	UPROPERTY(EditAnywhere, Category = "Melee");
	TSubclassOf<class ATailAttack> AttackBlueprint;

	UPROPERTY(EditAnywhere, Category = "Melee");
	FVector AttackSpawnPoint{ 0.f, 0.f, 0.f };

	//An additional collision for the attack.
	UPROPERTY(EditAnywhere, Category = "Setup");
	class USphereComponent* Collider = nullptr;

	

	

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Shoot();
	void Attack();


};
