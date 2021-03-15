// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BulletNut.h"
#include "Components/SphereComponent.h"
#include "TailAttack.h"

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
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
	SetActorLocation(NewLocation);

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
}

void AMainCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMainCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AMainCharacter::Shoot()
{
	UWorld* SamsWorld = GetWorld();

	if (SamsWorld)
	{
		SamsWorld->SpawnActor<ABulletNut>(BulletBlueprint, GetActorLocation() + BulletSpawnPoint, GetActorRotation());
	}
}


void AMainCharacter::Attack() {
	UWorld* SamsWorld = GetWorld();

	UE_LOG(LogTemp, Warning, TEXT("Attack"))

	if (SamsWorld)
	{
		SamsWorld->SpawnActor<ATailAttack>(AttackBlueprint, GetActorLocation()+ AttackSpawnPoint, GetActorRotation());
	}

}

