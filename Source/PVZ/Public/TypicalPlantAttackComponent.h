// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlantAttackBaseComponent.h"
#include "TypicalPlantAttackComponent.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UTypicalPlantAttackComponent : public UPlantAttackBaseComponent
{
	GENERATED_BODY()

public:
	UTypicalPlantAttackComponent();

	virtual void OnTryAttack() override;

	virtual void Attack() override;

};
