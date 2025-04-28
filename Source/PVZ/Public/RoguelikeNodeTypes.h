// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "RoguelikeNodeTypes.generated.h"

UENUM(BlueprintType, meta = (ScriptName = "RoguelikeNodeTypes"))
enum class ERoguelikeNodeTypes : uint8
{
	None UMETA(DisplayName = "None"),
	Battle UMETA(DisplayName = "Battle"),
	Occurrence UMETA(DisplayName = "Occurrence"),
	Shop UMETA(DisplayName = "Shop"),
	Treasure UMETA(DisplayName = "Treasure"),
	Boss UMETA(DisplayName = "Boss"),
	End UMETA(DisplayName = "End"),
};
/**
 * 
 */
class PVZ_API RoguelikeNodeTypes
{
public:
	RoguelikeNodeTypes();
	~RoguelikeNodeTypes();
};
