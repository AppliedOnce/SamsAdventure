// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdEnemy.h"
#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "AmmoNut.h"



// Sets default values
ABirdEnemy::ABirdEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABirdEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABirdEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABirdEnemy::GotHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("Enemy got hit"))
	Health--;
	if (Health <= 0)
	{
		SpawnPowerups();
		Destroy();
	}
}

void ABirdEnemy::SpawnPowerups()
{
	UWorld* World = GetWorld();
	const int RandomNumber = FMath::RandRange(0, 20 * (PowerupArray.Num() + 1));

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
			World->SpawnActor<AActor>(PowerupBlueprint, GetActorLocation(), GetActorRotation());
		}
	}
}


void ABirdEnemy::birbAttackAnim()
{
	BirbAttackAnim = true;

	if (BirbAttackAnim == true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Anim"));
	}

}