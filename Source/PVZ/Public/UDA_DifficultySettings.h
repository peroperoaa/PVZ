// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Algo/Compare.h"
#include "Engine/DataAsset.h"
#include "UDA_DifficultySettings.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API UUDA_DifficultySettings : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Difficulty Settings")
	float difficulty = 0.0f;
	
	UPROPERTY(EditAnywhere, Category = "Difficulty Settings")
	float maxDifficulty = 5.0f;
	
	UPROPERTY(EditAnywhere, Category = "Difficulty Settings")
	float enemyStrengthMultiplier = 1.1f;
	
	UPROPERTY(EditAnywhere, Category = "Difficulty Settings")
	float rewardMultiplier = 1.1f;
};
