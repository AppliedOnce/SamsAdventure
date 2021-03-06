// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "BulletNut.h"
#include "TailAttack.h"
#include "BirdEnemy.h"
#include "PlayerHealth.h"
#include "EnemyBullet.h"
#include <dos.h>


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 800.f;
	CameraArm->SetRelativeRotation(FRotator(-60.0, 90.f, CameraArm->GetRelativeRotation().Roll));
	CameraArm->bInheritYaw = false;
	CameraArm->bDoCollisionTest = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	Paraglider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paraglider"));
	Paraglider->SetupAttachment(GetCapsuleComponent());
	Paraglider->ToggleVisibility(false);

	PlayerCollider = this->GetCapsuleComponent();

	MovementComp = GetCharacterMovement();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->RotationRate = FRotator(0.f, 540.f, 0.0f);

	HealthComp = CreateDefaultSubobject<UPlayerHealth>(TEXT("PlayerHealth"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCollider->OnComponentHit.AddDynamic(this, &AMainCharacter::OnHit);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSinceLastShot += DeltaTime;
	JumpAnim = MovementComp->IsFalling();
	if (!MovementComp->IsFalling() && Paraglider->IsVisible())
	{
		Paraglider->SetVisibility(false, true);
	}
	AttackAnim = false;
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Glide", IE_Pressed, this, &AMainCharacter::Glide);
	PlayerInputComponent->BindAction("Glide", IE_Released, this, &AMainCharacter::StopGliding);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::Shoot);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::StopRunning);
}



void AMainCharacter::MoveForward(float Value)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
		
	}
}

void AMainCharacter::Run()
{
	MovementComp->MaxWalkSpeed = 800.f;
}

void AMainCharacter::StopRunning()
{
	MovementComp->MaxWalkSpeed = 450.f;
}

void AMainCharacter::Shoot()
{
	UWorld* SamsWorld = GetWorld();

	if (SamsWorld)
	{
		if (CurrentAmmo > 0 && TimeSinceLastShot >= ShootCooldown)
		{
			SamsWorld->SpawnActor<ABulletNut>(BulletBlueprint, GetActorLocation() + (GetActorForwardVector() * 100), GetActorRotation());
			CurrentAmmo--;
			TimeSinceLastShot = 0.f;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't shoot, out of ammo!"));
		}
	}
}

void AMainCharacter::Attack() {
	UWorld* SamsWorld = GetWorld();

	if (SamsWorld)
	{
		SamsWorld->SpawnActor<ATailAttack>(AttackBlueprint, GetActorLocation()+ AttackSpawnPoint, GetActorRotation());
	}
	 AttackAnim = true;

}

void AMainCharacter::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABirdEnemy::StaticClass()))
	{
		Cast<ABirdEnemy>(OtherActor)->birbAttackAnim();
	
		HealthComp->LoseHp(1);
		UE_LOG(LogTemp, Warning, TEXT("Player just hit %s, taking damage.\nPlayer health: %i"), *OtherActor->GetName(), HealthComp->GetCurrentHp());
	
	}

}

void AMainCharacter::IncreaseAmmo(int Value)
{
	CurrentAmmo += Value;
	if (CurrentAmmo > MaxAmmo)
		CurrentAmmo = MaxAmmo;
}

bool AMainCharacter::IsAmmoFull() const
{
	return CurrentAmmo >= MaxAmmo;
}

UPlayerHealth* AMainCharacter::GetHealthComponent() const
{
	return HealthComp;
}

bool AMainCharacter::IsInvulnerable()
{
	return Invulnerable;
}

void AMainCharacter::Glide()
{
	if (MovementComp->IsFalling())
	{
		MovementComp->GravityScale = 0.2f;
		MovementComp->AirControl = 0.3f;
		Paraglider->SetVisibility(true, true);
	}
}

void AMainCharacter::StopGliding()
{
	MovementComp->GravityScale = 1.0f;
	MovementComp->AirControl = 1.0f;
	Paraglider->SetVisibility(false, true);
}
