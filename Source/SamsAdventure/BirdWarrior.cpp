// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdWarrior.h"
#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "AmmoNut.h"
#include "BirdAIController.h"

// Sets default values
ABirdWarrior::ABirdWarrior()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerSensingSphere = CreateDefaultSubobject<USphereComponent> (TEXT("VISION"));
	PlayerSensingSphere->SetupAttachment(GetRootComponent());
	PlayerSensingSphere->InitSphereRadius(650.f);

}

// Called when the game starts or when spawned
void ABirdWarrior::BeginPlay()
{
	Super::BeginPlay();
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABirdWarrior::OnOverlap);
	
}

// Called every frame
void ABirdWarrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdWarrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABirdWarrior::GotHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy got hit"))
	Health--;
	if (Health <= 0)
	{
		SpawnPowerups();
		Destroy();
	}
}

void ABirdWarrior::SpawnPowerups()
{
	UWorld* World = GetWorld();
	int RandomNumber = FMath::RandRange(0, 20 * (PowerupArray.Num() + 1));

	if (World)
	{
		for (int i = 0; i < PowerupArray.Num(); i++)
		{
			if (RandomNumber >= (20 * PowerupArray.Num() / PowerupArray.Num()) * (i + 1))
			{
				PowerupBlueprint = PowerupArray[i];
			}
		}

		if (PowerupBlueprint != NULL)
		{
			World->SpawnActor<AAmmoNut>(PowerupBlueprint, GetActorLocation(), GetActorRotation());
		}
	}
}

void ABirdWarrior::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Do not destroy the bullet if it collides with the player or other bullets

	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		/*InRange = true;*/
		/*Shooting();*/
		UE_LOG(LogTemp, Warning, TEXT("Attack"));

	}
}
