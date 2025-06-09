// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantBase.h"
#include "WallNut.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API AWallNut : public APlantBase
{
	GENERATED_BODY()

public:
	AWallNut();

	virtual void Dead();
};
