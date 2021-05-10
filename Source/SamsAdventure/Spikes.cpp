// Fill out your copyright notice in the Description page of Project Settings.


#include "Spikes.h"
#include "Components/BoxComponent.h"


// Sets default values
ASpikes::ASpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCollider"));
	RootComponent = OurCollider;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

