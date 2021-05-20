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
	FVector BulletSpawnPoint{ 100.f, 0.f, 0.f };

	UPROPERTY(EditAnywhere, Category = "Setup");
	UStaticMeshComponent* Paraglider;

	//An additional collision for the attack.
	class USphereComponent* AttackCollider = nullptr;

	UCapsuleComponent* PlayerCollider;

	UCharacterMovementComponent* MovementComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPlayerHealth* HealthComp;
	
	UPROPERTY(EditAnywhere, Category = "Melee");
	TSubclassOf<class ATailAttack> AttackBlueprint;

	UPROPERTY(EditAnywhere, Category = "Projectile");
	TSubclassOf<class ABulletNut> BulletBlueprint;

	UPROPERTY(EditAnywhere, Category = "Melee");
	FVector AttackSpawnPoint{ 0.f, 0.f, 0.f };
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile");
	int CurrentAmmo{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile");
	int MaxAmmo{ 20 };

	UPROPERTY(EditAnywhere, Category = "Projectile");
	float ShootCooldown{ 0.1f };

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void IncreaseAmmo(int Value);
	bool IsAmmoFull() const;
	class UPlayerHealth* GetHealthComponent() const;
	bool IsInvulnerable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation");
	bool AttackAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation");
	bool JumpAnim = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation");
	bool WalkAnim = false;


private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Shoot();
	void Run();
	void StopRunning();
	void Attack();
	void Glide();
	void StopGliding();
	void AnimateJump();
	int JumpState{ 0 };

	bool Invulnerable{ false };
	float TimeSinceLastShot{ ShootCooldown };
};
