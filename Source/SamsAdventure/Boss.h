// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BirdEnemy.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class SAMSADVENTURE_API ABoss : public ABirdEnemy
{
	GENERATED_BODY()
public:
	int GetPhase();
private:
	int Phase{ 0 };
	float Health{ 10 };
	void Attack();
};
