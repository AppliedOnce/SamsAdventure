// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletNut.generated.h"

UCLASS()
class SAMSADVENTURE_API ABulletNut : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletNut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup");	// Gjør dette for å kunne endre den i Unreal
	float speed = 800.f;							//legg til .f fordi det er en float

	UPROPERTY(EditAnywhere, Category = "Setup");
	float timeBeforeDestruction = 3.f;

	float timeSurvived = 0.f;

	UPROPERTY(EditAnywhere, Category = "Setup");
	class USphereComponent* Collider = nullptr;


	UPROPERTY(EditAnywhere, Category = "Setup");
	class UStaticMeshComponent* Mesh = nullptr;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
