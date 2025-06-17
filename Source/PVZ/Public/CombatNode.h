// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapNode.h"
#include "RogueLikeStateManager.h"
#include "Kismet/GameplayStatics.h"
#include "CombatNode.generated.h"

/**
 * 
 */
UCLASS()
class PVZ_API ACombatNode : public AMapNode
{
	GENERATED_BODY()

public:
	ACombatNode();
	
	virtual void EnterNode_Implementation(APlayerController* PlayerController) override;
	
	// 战斗完成后调用此方法
	UFUNCTION(BlueprintCallable, Category = "Rogue|Combat")
	void OnCombatCompleted(bool bVictory);
    
	// 获取RoguelikeStateManager的引用
	UFUNCTION(BlueprintCallable, Category = "Rogue|Combat")
	URoguelikeStateManager* GetStateManager() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Rogue|Combat")
	void OnLevelUnloaded(const FName& LevelName);

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Rogue|Combat")
	FName CombatLevelName;
};
