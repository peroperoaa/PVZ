// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProjectileState.generated.h"

USTRUCT(BlueprintType)
struct PVZ_API FProjectileState : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ProjectileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;
};