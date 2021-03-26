// Fill out your copyright notice in the Description page of Project Settings.


#include "TailAttack.h"
#include "Components/SphereComponent.h"
#include "BulletNut.h"
#include "MainCharacter.h"
#include "BirdEnemy.h"

// Sets default values
ATailAttack::ATailAttack()
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
void ATailAttack::BeginPlay()
{
	Super::BeginPlay();

	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ATailAttack::OnOverlap);
}

// Called every frame
void ATailAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeSurvived += DeltaTime;

	if (TimeSurvived > TimeBeforeDestruction)
	{
		this->Destroy();
	}
}

void ATailAttack::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	// Do not destroy the bullet if it collides with the player or other bullets
	if (!OtherActor->IsA(AMainCharacter::StaticClass()) && !OtherActor->IsA(ATailAttack::StaticClass()))
	{
		if (OtherActor->IsA(ABirdEnemy::StaticClass()))
		{
			Cast<ABirdEnemy>(OtherActor)->GotHit();
			Destroy();
		}

		Destroy();
	}
}

