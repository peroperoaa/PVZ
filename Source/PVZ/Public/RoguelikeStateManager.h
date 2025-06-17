// RoguelikeStateManager.h

#pragma once

#include "CoreMinimal.h"
#include "RoguelikeStateEnum.h"
#include "RoguelikeGameSave.h"
#include "GameOverWidget.h"
#include "GameFramework/SaveGame.h"
#include "RoguelikeStateManager.generated.h"

// 数值变化委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStateValueChanged, ERoguelikeStateEnum, StateType, float, OldValue, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class PVZ_API URoguelikeStateManager : public UObject
{
	GENERATED_BODY()

public:
	URoguelikeStateManager();

	URoguelikeStateManager(const FObjectInitializer& ObjectInitializer);

	// 将默认值声明为可编辑属性
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Roguelike|DefaultValues")
	TMap<ERoguelikeStateEnum, float> DefaultValues;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Roguelike|DefaultValues")
	TMap<ERoguelikeStateEnum, float> DefaultMaxValues;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Roguelike|DefaultValues")
	TMap<ERoguelikeStateEnum, float> DefaultMinValues;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	// 获取状态值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	float GetStateValue(ERoguelikeStateEnum StateType) const;

	// 设置状态值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void SetStateValue(ERoguelikeStateEnum StateType, float NewValue);

	// 修改状态值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void ModifyStateValue(ERoguelikeStateEnum StateType, float Delta);

	// 状态变化委托
	UPROPERTY(BlueprintAssignable, Category = "Rogue|State")
	FOnStateValueChanged OnStateValueChanged;

	// 初始化默认值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void InitializeDefaultValues();

	// 保存状态
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void SaveState();

	// 加载状态
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void LoadState();
	
	// 重置所有状态到默认值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void ResetAllStatesToDefault();
    
	// 获取状态的最大值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	float GetStateMaxValue(ERoguelikeStateEnum StateType) const;
    
	// 获取状态的百分比(当前值/最大值)
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	float GetStateValueAsPercentage(ERoguelikeStateEnum StateType) const;

	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void UpdateDefaultConfiguration();

	// 应用战斗胜利奖励
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void ApplyBattleVictoryRewards();

	// 应用战斗失败惩罚
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void ApplyBattleDefeatPenalties();

	// 处理等级提升时的奖励
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void HandleLevelUpRewards(int32 NewLevel);


private:
	// 存储各项状态值的映射
	UPROPERTY()
	TMap<ERoguelikeStateEnum, float> StateValues;

	// 最大值限制
	UPROPERTY()
	TMap<ERoguelikeStateEnum, float> MaxValues;

	// 最小值限制
	UPROPERTY()
	TMap<ERoguelikeStateEnum, float> MinValues;
};