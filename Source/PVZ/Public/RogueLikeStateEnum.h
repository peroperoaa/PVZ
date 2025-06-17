// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "RoguelikeStateEnum.generated.h"
/**
 * 
 */
UENUM(BlueprintType, meta = (ScriptName = "RoguelikeStateEnum"))
enum class ERoguelikeStateEnum : uint8
{
	//生命值
	Health UMETA(DisplayName = "Health"),
	//等级
	Level UMETA(DisplayName = "Level"),
	//肥料
	Fertilizer UMETA(DisplayName = "Fertilizer"),
	//金钱
	Money UMETA(DisplayName = "Money"),
	//携带上限
	CarryingLimit UMETA(DisplayName = "CarryingLimit"),
};
class PVZ_API RoguelikeStateEnum
{
public:
	RoguelikeStateEnum();
	~RoguelikeStateEnum();
};
