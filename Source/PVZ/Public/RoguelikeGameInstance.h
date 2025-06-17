// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RogueLikeStateManager.h"
#include "CombatNode.h"
#include "GameOverWidget.h"
#include "RoguelikeGameInstance.generated.h"
/**
 * 
 */
UCLASS()
class PVZ_API URoguelikeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	
	
	UPROPERTY()
	URoguelikeStateManager* StateManager;

	UPROPERTY(BlueprintReadWrite)
	ACombatNode* CurrentCombatNode;
	
};
