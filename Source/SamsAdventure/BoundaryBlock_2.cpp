// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundaryBlock_2.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "SamsAdventureGameMode.h"


// Sets default values
ABoundaryBlock_2::ABoundaryBlock_2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundaryBox_2"));
	RootComponent = Collider;

}

// Called when the game starts or when spawned
void ABoundaryBlock_2::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABoundaryBlock_2::OnOverlap);

}

// Called every frame
void ABoundaryBlock_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoundaryBlock_2::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		ASamsAdventureGameMode* GM = GetWorld()->GetAuthGameMode<ASamsAdventureGameMode>();

		GM->TeleportPlayerToStart();
	}
}
