// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BulletNut.h"
#include "Components/SphereComponent.h"
#include "TailAttack.h"
#include "Components/CapsuleComponent.h"
#include "BirdEnemy.h"
#include "PlayerHealth.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 800.f;
	//CameraArm->bEnableCameraLag = true;
	CameraArm->SetRelativeRotation(FRotator(-60.0, 90.f, 0.f));
	CameraArm->bInheritYaw = false;
	CameraArm->bDoCollisionTest = false;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	PlayerCollider = this->GetCapsuleComponent();
	movementComp = GetCharacterMovement();

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

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMainCharacter::Shoot);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainCharacter::Attack);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMainCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMainCharacter::StopRunning);
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::Run()
{
	movementComp->MaxWalkSpeed = 800.f;
}

void AMainCharacter::StopRunning()
{
	movementComp->MaxWalkSpeed = 600.f;
}

void AMainCharacter::Shoot()
{
	UWorld* SamsWorld = GetWorld();

	if (SamsWorld)
	{
		if (CurrentAmmo > 0)
		{
			SamsWorld->SpawnActor<ABulletNut>(BulletBlueprint, GetActorLocation() + BulletSpawnPoint, GetActorRotation());
			CurrentAmmo--;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't shoot, out of ammo!"));
		}
	}
}

void AMainCharacter::Attack() {
	UWorld* SamsWorld = GetWorld();

	UE_LOG(LogTemp, Warning, TEXT("Attack"));
	if (SamsWorld)
	{
		SamsWorld->SpawnActor<ATailAttack>(AttackBlueprint, GetActorLocation()+ AttackSpawnPoint, GetActorRotation());
	}

}

void AMainCharacter::OnHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABirdEnemy::StaticClass()))
	{
		HealthComp->LoseHp(1);
		UE_LOG(LogTemp, Warning, TEXT("Player just hit %s, taking damage.\nPlayer health: %i"), *OtherActor->GetName(), HealthComp->GetCurrentHp());
	}
}

void AMainCharacter::IncreaseAmmo(int value)
{
	CurrentAmmo += value;
	if (CurrentAmmo > MaxAmmo)
		CurrentAmmo = MaxAmmo;
}

bool AMainCharacter::IsAmmoFull()
{
	return CurrentAmmo >= MaxAmmo;
}
