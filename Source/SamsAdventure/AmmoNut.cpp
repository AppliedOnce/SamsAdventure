// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoNut.h"
#include "Components/SphereComponent.h"
// Sets default values
AAmmoNut::AAmmoNut()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurCollider = CreateDefaultSubobject<USphereComponent>(TEXT("MyCollider"));
	RootComponent = OurCollider;
	
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAmmoNut::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoNut::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

