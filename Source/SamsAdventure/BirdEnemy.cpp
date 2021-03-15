// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdEnemy.h"
#include "MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"



// Sets default values
ABirdEnemy::ABirdEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABirdEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Cast<UCapsuleComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABirdEnemy::OnOverlap);
	Cast<USphereComponent>(RootComponent)->OnComponentBeginOverlap.AddDynamic(this, &ABirdEnemy::OnOverlap);
}

// Called every frame
void ABirdEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABirdEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABirdEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) 
{
	UE_LOG(LogTemp, Warning, TEXT("You got hit by: %s"), *OtherActor->GetName());

	if (OtherActor->IsA(AMainCharacter::StaticClass()))
	{

	}
}
