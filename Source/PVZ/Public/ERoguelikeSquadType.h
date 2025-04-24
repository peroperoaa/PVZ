// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ERoguelikeSquadType.generated.h"
/**
 * 
 */
UENUM(BlueprintType, meta=(ScriptName="RoguelikeSquadType"))
enum class EERoguelikeSquadType : uint8
{
	//基础分队类型
	Squad_Default UMETA(DisplayName = "默认分队"),
	//等待构思
	Squad_A UMETA(DisplayName = "A分队"),
	Squad_B UMETA(DisplayName = "B分队"),
	Squad_C UMETA(DisplayName = "C分队"),
};

class PVZ_API ERoguelikeSquadType
{
public:
	ERoguelikeSquadType();
	~ERoguelikeSquadType();
};
