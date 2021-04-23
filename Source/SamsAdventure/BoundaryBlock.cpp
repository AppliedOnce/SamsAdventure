// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundaryBlock.h"
#include "MainCharacter.h"
#include "Components/BoxComponent.h"
#include "SamsAdventureGameMode.h"

// Sets default values
ABoundaryBlock::ABoundaryBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoundaryBox"));
	RootComponent = Collider;
}

// Called when the game starts or when spawned
void ABoundaryBlock::BeginPlay()
{
	Super::BeginPlay();
	
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABoundaryBlock::OnOverlap);
}

// Called every frame
void ABoundaryBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoundaryBlock::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{
		GetWorld()->GetAuthGameMode<ASamsAdventureGameMode>()->TeleportPlayerToStart();
	}
}

