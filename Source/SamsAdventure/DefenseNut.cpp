// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseNut.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "PlayerHealth.h"

// Sets default values
ADefenseNut::ADefenseNut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
	OurVisibleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ADefenseNut::BeginPlay()
{
	Super::BeginPlay();

	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ADefenseNut::OnOverlap);
}

// Called every frame
void ADefenseNut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefenseNut::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);

		if (!Player->GetHealthComponent()->CheckShielded())
		{
			Player->GetHealthComponent()->ShieldPlayer();
			Destroy();
		}
		
	}
}

