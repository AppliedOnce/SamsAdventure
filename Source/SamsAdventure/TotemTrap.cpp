// Fill out your copyright notice in the Description page of Project Settings.


#include "TotemTrap.h"
#include "AIController.h"
#include "MainCharacter.h"
#include "Components/SphereComponent.h"
#include "EnemyBullet.h"


ATotemTrap::ATotemTrap()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollider"));
	RootComponent = OurCollider;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATotemTrap::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AAIController>(GetController());


	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ATotemTrap::OnOverlap);
	Cast<USphereComponent>(RootComponent)->OnComponentEndOverlap.AddDynamic(this, &ATotemTrap::OnOverlapEnd);

}

// Called every frame
void ATotemTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShootingRythm += DeltaTime;
	Shooting();
}

// Called to bind functionality to input
void ATotemTrap::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATotemTrap::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("I see you"))
			AIController->SetFocus(Player);

	}

	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		InRange = true;


	}

}

void ATotemTrap::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		InRange = false;


	}

}

void ATotemTrap::Shooting() {
	UWorld* SamsWorld = GetWorld();

	if (InRange != false) {
		if (ShootingRythm >= 1) {
			UE_LOG(LogTemp, Warning, TEXT("Attack"));
			if (SamsWorld)
			{
				SamsWorld->SpawnActor<AEnemyBullet>(AttackBlueprint, GetActorLocation() + AttackSpawnPoint, GetActorRotation());
			}
			ShootingRythm = 0;
		}
	}

}