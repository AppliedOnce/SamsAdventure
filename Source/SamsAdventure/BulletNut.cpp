// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletNut.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "BirdEnemy.h"
#include "BirdWarrior.h"
// Sets default values
ABulletNut::ABulletNut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
													//Dette lager en collider og en mesh som er satt fast sammen
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->SetGenerateOverlapEvents(true);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABulletNut::BeginPlay()
{
	Super::BeginPlay();
								//Denne gj�r at den kj�rer
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABulletNut::OnOverlap);
}

// Called every frame
void ABulletNut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);						//Det under gj�r at prosjektilen g�r framover
	
	TimeSurvived += DeltaTime;

	if (TimeSurvived > TimeBeforeDestruction)
	{
		this->Destroy();
	}
	else
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * Speed * DeltaTime;
		SetActorLocation(NewLocation, false);
	}
}
												//Dette gj�r s�nn at n�r prosjektilen treffer noe, s� skjer noe. den calles n�r den treffer noe
void ABulletNut::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Do not destroy the bullet if it collides with the player or other bullets
	if (!OtherActor->IsA(AMainCharacter::StaticClass()) && !OtherActor->IsA(ABulletNut::StaticClass()) && !OtherActor->IsA(AAmmoNut::StaticClass()))
	{
		if (OtherActor->IsA(ABirdEnemy::StaticClass()))
		{
			Cast<ABirdEnemy>(OtherActor)->GotHit();
			Destroy();
		}

		Destroy();
	}
}