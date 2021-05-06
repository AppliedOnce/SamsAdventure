// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthNut.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "PlayerHealth.h"

// Sets default values
AHealthNut::AHealthNut()
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
void AHealthNut::BeginPlay()
{
	Super::BeginPlay();

	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &AHealthNut::OnOverlap);
	
}

// Called every frame
void AHealthNut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthNut::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		UPlayerHealth* PlayerHealthComp = Cast<AMainCharacter>(OtherActor)->GetHealthComponent();
		if (PlayerHealthComp->GetCurrentHp() < PlayerHealthComp->GetMaxHp())
		{
			PlayerHealthComp->IncreaseHp(HealthToGive);
			Destroy();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Health is allready full, did not pick up."));
		}
	}
}

