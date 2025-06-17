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
	Squad_Default UMETA(DisplayName = "初始分队"),// 无效果
	
	Squad_Command UMETA(DisplayName = "指挥分队"),// 初始生命+3
	Squad_Colony UMETA(DisplayName = "集群分队"),// 初始携带位+2
	Squad_Logistics UMETA(DisplayName = "后勤分队"),// 初始金钱+10
};

class PVZ_API ERoguelikeSquadType
{
public:
	ERoguelikeSquadType();
	~ERoguelikeSquadType();
};
