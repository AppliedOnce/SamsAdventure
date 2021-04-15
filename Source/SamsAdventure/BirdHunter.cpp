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
	
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABirdHunter::OnOverlap);
}

void ABirdHunter::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Do not destroy the bullet if it collides with the player or other bullets
	UWorld* SamsWorld = GetWorld();

		if (OtherActor->IsA(AMainCharacter::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Attack"));
			if (SamsWorld)
			{
				SamsWorld->SpawnActor<AEnemyBullet>(AttackBlueprint, GetActorLocation(), GetActorRotation());
			}
		}

}


