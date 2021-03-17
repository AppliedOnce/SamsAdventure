// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoNut.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"

// Sets default values
AAmmoNut::AAmmoNut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollider"));
	RootComponent = OurCollider;
	
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
	OurVisibleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void AAmmoNut::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AAmmoNut::OnOverlap);
}

// Called every frame
void AAmmoNut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoNut::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		AMainCharacter* player = Cast<AMainCharacter>(OtherActor);
		if (!player->IsAmmoFull())
		{
			UE_LOG(LogTemp, Warning, TEXT("Picking up %i ammo"), AmmoToGive);
			player->IncreaseAmmo(AmmoToGive);
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Ammo is allready full, did not pick up."));
		}
	}
}
