// Fill out your copyright notice in the Description page of Project Settings.


#include "ICloud.h"
#include "ICloudSpawner.h"
#include "Components/SphereComponent.h"

// Sets default values
AICloud::AICloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	Collider->SetGenerateOverlapEvents(true);

	RootComponent = Collider;
	
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AICloud::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AICloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimePresent += DeltaTime;


	if (TimePresent > TimeToGetToTheOtherSide)
	{
		//Spawner->ICloudThrough();
		this->Destroy();
	}

}

