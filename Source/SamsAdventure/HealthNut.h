// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthNut.generated.h"

UCLASS()
class SAMSADVENTURE_API AHealthNut : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthNut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Setup");
	class UStaticMeshComponent* OurVisibleComponent{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Setup");
	class USphereComponent* OurCollider{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Setup");
	float HealthToGive { 1.0f };

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
