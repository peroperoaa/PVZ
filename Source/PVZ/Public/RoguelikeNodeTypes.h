// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "RoguelikeNodeTypes.generated.h"

UENUM(BlueprintType, meta = (ScriptName = "RoguelikeNodeTypes"))
enum class ERoguelikeNodeTypes : uint8
{
	None UMETA(DisplayName = "None"),
	Combat UMETA(DisplayName = "Combat"),
	Encounter UMETA(DisplayName = "Encounter"),
	Shop UMETA(DisplayName = "Shop"),
	Wish UMETA(DisplayName = "Wish"),
	Boss UMETA(DisplayName = "Boss"),
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
