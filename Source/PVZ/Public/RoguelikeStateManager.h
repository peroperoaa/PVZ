// RogueLikeStateManager.h

#pragma once

#include "CoreMinimal.h"
#include "RogueLikeStateEnum.h"
#include "GameFramework/SaveGame.h"
#include "RogueLikeStateManager.generated.h"

// 数值变化委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStateValueChanged, ERogueLikeStateEnum, StateType, float, OldValue, float, NewValue);

UCLASS(BlueprintType, Blueprintable)
class PVZ_API URogueLikeStateManager : public UObject
{
	GENERATED_BODY()

public:
	URogueLikeStateManager();

	// 获取状态值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	float GetStateValue(ERogueLikeStateEnum StateType) const;

	// 设置状态值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void SetStateValue(ERogueLikeStateEnum StateType, float NewValue);

	// 修改状态值
	UFUNCTION(BlueprintCallable, Category = "Rogue|State")
	void ModifyStateValue(ERogueLikeStateEnum StateType, float Delta);

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

private:
	// 存储各项状态值的映射
	UPROPERTY()
	TMap<ERogueLikeStateEnum, float> StateValues;

	// 最大值限制
	UPROPERTY()
	TMap<ERogueLikeStateEnum, float> MaxValues;

	// 最小值限制
	UPROPERTY()
	TMap<ERogueLikeStateEnum, float> MinValues;
};