// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdEnemy.h"
#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

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
		Destroy();
	}
}
