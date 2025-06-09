// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlantState.generated.h"


USTRUCT(BlueprintType)
struct PVZ_API FPlantState : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName PlantName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseAttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseCritRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseCritDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SunCost;
};