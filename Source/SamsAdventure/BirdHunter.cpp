// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdHunter.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "EnemyBullet.h"
#include "AIController.h"



ABirdHunter::ABirdHunter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PlayerSensingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("VISION"));
	PlayerSensingSphere->SetupAttachment(GetRootComponent());
	PlayerSensingSphere->InitSphereRadius(650.f);
}

void ABirdHunter::BeginPlay()
{
	Super::BeginPlay();

	PlayerSensingSphere->OnComponentBeginOverlap.AddDynamic(this, &ABirdHunter::OnOverlap);
	PlayerSensingSphere->OnComponentEndOverlap.AddDynamic(this, &ABirdHunter::OnOverlapEnd);
}

void ABirdHunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ShootingRythm += DeltaTime;
	Shooting();

}

void ABirdHunter::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Do not destroy the bullet if it collides with the player or other bullets

	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		InRange = true;


	}
}

void ABirdHunter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		InRange = false;


	}

}

void ABirdHunter::Shooting() {
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

USphereComponent* ABirdHunter::GetVisionCollider()
{
	return PlayerSensingSphere;
}
