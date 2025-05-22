// RogueLikeStateManager.cpp

#include "RogueLikeStateManager.h"
#include "Kismet/GameplayStatics.h"

URogueLikeStateManager::URogueLikeStateManager()
{
    InitializeDefaultValues();
}

float URogueLikeStateManager::GetStateValue(ERogueLikeStateEnum StateType) const
{
    if (StateValues.Contains(StateType))
    {
        return StateValues[StateType];
    }
    return 0.0f;
}

void URogueLikeStateManager::SetStateValue(ERogueLikeStateEnum StateType, float NewValue)
{
    float OldValue = GetStateValue(StateType);
    
    // 应用最大值和最小值限制
    if (MaxValues.Contains(StateType))
    {
        NewValue = FMath::Min(NewValue, MaxValues[StateType]);
    }
    
    if (MinValues.Contains(StateType))
    {
        NewValue = FMath::Max(NewValue, MinValues[StateType]);
    }
    
    StateValues.Add(StateType, NewValue);
    
    // 如果值有变化，触发委托
    if (OldValue != NewValue)
    {
        OnStateValueChanged.Broadcast(StateType, OldValue, NewValue);
    }
}

void URogueLikeStateManager::ModifyStateValue(ERogueLikeStateEnum StateType, float Delta)
{
    float CurrentValue = GetStateValue(StateType);
    SetStateValue(StateType, CurrentValue + Delta);
}

void URogueLikeStateManager::InitializeDefaultValues()
{
    // 设置默认值
    StateValues.Add(ERogueLikeStateEnum::Health, 5.0f);
    StateValues.Add(ERogueLikeStateEnum::Level, 1.0f);
    StateValues.Add(ERogueLikeStateEnum::Fertilizer, 50.0f);
    StateValues.Add(ERogueLikeStateEnum::Money, 0.0f);
    StateValues.Add(ERogueLikeStateEnum::CarryingLimit, 5.0f);
    
    // 设置最大值限制
    MaxValues.Add(ERogueLikeStateEnum::Health, 100.0f);
    MaxValues.Add(ERogueLikeStateEnum::Level, 99.0f);
    MaxValues.Add(ERogueLikeStateEnum::Fertilizer, 999.0f);
    MaxValues.Add(ERogueLikeStateEnum::Money, 9999.0f);
    MaxValues.Add(ERogueLikeStateEnum::CarryingLimit, 100.0f);
    
    // 设置最小值限制
    MinValues.Add(ERogueLikeStateEnum::Health, 0.0f);
    MinValues.Add(ERogueLikeStateEnum::Level, 1.0f);
    MinValues.Add(ERogueLikeStateEnum::Fertilizer, 0.0f);
    MinValues.Add(ERogueLikeStateEnum::Money, 0.0f);
    MinValues.Add(ERogueLikeStateEnum::CarryingLimit, 3.0f);
}

void URogueLikeStateManager::SaveState()
{
    // 保存状态逻辑可以在这里实现
    // 例如使用UGameplayStatics::SaveGameToSlot
}

void URogueLikeStateManager::LoadState()
{
    // 加载状态逻辑可以在这里实现
    // 例如使用UGameplayStatics::LoadGameFromSlot
}