// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdHunter.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "EnemyBullet.h"


ABirdHunter::ABirdHunter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->SetGenerateOverlapEvents(true);

	OK = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	OK->SetupAttachment(RootComponent);
}

void ABirdHunter::BeginPlay()
{
	Super::BeginPlay();
	//Denne gjør at den kjører
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABirdHunter::OnOverlap);
}

void ABirdHunter::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UWorld* SamsWorld = GetWorld();

	// Do not destroy the bullet if it collides with the player or other bullets
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		

	
		if (SamsWorld)
		{
			SamsWorld->SpawnActor<AEnemyBullet>(AttackBlueprint, GetActorLocation() + AttackSpawnPoint, GetActorRotation());
		}
	}
}