// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "MainCharacter.h"
#include "PlayerHealth.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->SetGenerateOverlapEvents(true);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnOverlap);
	
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timeSurvived += DeltaTime;

	if (timeSurvived > timeBeforeDestruction)
	{
		this->Destroy();
	}
	else
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(NewLocation, false);
	}

}

void AEnemyBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Do not destroy the bullet if it collides with the player or other bullets
	
		if (OtherActor->IsA(AMainCharacter::StaticClass()))
		{
			Cast<AMainCharacter>(OtherActor)->GetHealthComponent()->LoseHp(1);
			Destroy();
		}

	
	
}