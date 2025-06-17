// RoguelikeStateManager.cpp

#include "RoguelikeStateManager.h"
#include "Kismet/GameplayStatics.h"

URoguelikeStateManager::URoguelikeStateManager()
{
    InitializeDefaultValues();
}

URoguelikeStateManager::URoguelikeStateManager(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // 初始化默认值
    InitializeDefaultValues();
}

float URoguelikeStateManager::GetStateValue(ERoguelikeStateEnum StateType) const
{
    if (StateValues.Contains(StateType))
    {
        return StateValues[StateType];
    }
    return 0.0f;
}

void URoguelikeStateManager::SetStateValue(ERoguelikeStateEnum StateType, float NewValue)
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

    // 如果是等级变化且是整数变化，检查是否需要给予奖励
    if (StateType == ERoguelikeStateEnum::Level && FMath::FloorToInt(NewValue) > FMath::FloorToInt(OldValue))
    {
        HandleLevelUpRewards(FMath::FloorToInt(NewValue));
    }
    if(StateType == ERoguelikeStateEnum::Health && NewValue <= 0.0f)
    {
        // 创建并显示游戏结束界面
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController && GameOverWidgetClass)
        {
            UGameOverWidget* GameOverWidget = CreateWidget<UGameOverWidget>(PlayerController, GameOverWidgetClass);
            if (GameOverWidget)
            {
                GameOverWidget->ShowGameEnd(EGameEndState::GameOver);
                UE_LOG(LogTemp, Warning, TEXT("显示游戏结束界面"));
            }
        }
    }
    // 如果值有变化，触发委托
    if (OldValue != NewValue)
    {
        OnStateValueChanged.Broadcast(StateType, OldValue, NewValue);
    }
}

void URoguelikeStateManager::ModifyStateValue(ERoguelikeStateEnum StateType, float Delta)
{
    float CurrentValue = GetStateValue(StateType);
    SetStateValue(StateType, CurrentValue + Delta);
}

void URoguelikeStateManager::InitializeDefaultValues()
{
    // 如果没有在蓝图中设置默认值，则使用硬编码的默认值
    if (DefaultValues.Num() == 0)
    {
        // 设置默认初始值
        DefaultValues.Add(ERoguelikeStateEnum::Health, 5.0f);
        DefaultValues.Add(ERoguelikeStateEnum::Level, 1.0f);
        DefaultValues.Add(ERoguelikeStateEnum::Fertilizer, 50.0f);
        DefaultValues.Add(ERoguelikeStateEnum::Money, 0.0f);
        DefaultValues.Add(ERoguelikeStateEnum::CarryingLimit, 5.0f);
    }

    if (DefaultMaxValues.Num() == 0)
    {
        // 设置默认最大值
        DefaultMaxValues.Add(ERoguelikeStateEnum::Health, 100.0f);
        DefaultMaxValues.Add(ERoguelikeStateEnum::Level, 99.0f);
        DefaultMaxValues.Add(ERoguelikeStateEnum::Fertilizer, 999.0f);
        DefaultMaxValues.Add(ERoguelikeStateEnum::Money, 9999.0f);
        DefaultMaxValues.Add(ERoguelikeStateEnum::CarryingLimit, 100.0f);
    }

    if (DefaultMinValues.Num() == 0)
    {
        // 设置默认最小值
        DefaultMinValues.Add(ERoguelikeStateEnum::Health, 0.0f);
        DefaultMinValues.Add(ERoguelikeStateEnum::Level, 1.0f);
        DefaultMinValues.Add(ERoguelikeStateEnum::Fertilizer, 0.0f);
        DefaultMinValues.Add(ERoguelikeStateEnum::Money, 0.0f);
        DefaultMinValues.Add(ERoguelikeStateEnum::CarryingLimit, 3.0f);
    }

    // 应用默认值
    StateValues = DefaultValues;
    MaxValues = DefaultMaxValues;
    MinValues = DefaultMinValues;
}

void URoguelikeStateManager::SaveState()
{
    // 创建SaveGame对象
    URoguelikeGameSave* SaveGameInstance = Cast<URoguelikeGameSave>(UGameplayStatics::CreateSaveGameObject(URoguelikeGameSave::StaticClass()));
    
    if (SaveGameInstance)
    {
        // 复制当前状态到存档
        SaveGameInstance->SavedStateValues = StateValues;
        
        // 保存到默认槽位
        if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("RoguelikeSaveSlot"), 0))
        {
            UE_LOG(LogTemp, Log, TEXT("游戏状态保存成功"));
        }
    }
}

void URoguelikeStateManager::LoadState()
{
    // 尝试加载存档
    URoguelikeGameSave* LoadedGame = Cast<URoguelikeGameSave>(UGameplayStatics::LoadGameFromSlot(TEXT("RoguelikeSaveSlot"), 0));
    
    if (LoadedGame)
    {
        // 临时存储旧值以触发委托
        TMap<ERoguelikeStateEnum, float> OldValues = StateValues;
        
        // 更新状态值
        StateValues = LoadedGame->SavedStateValues;
        
        // 触发每个变化状态的委托
        for (auto& Pair : StateValues)
        {
            ERoguelikeStateEnum StateType = Pair.Key;
            float NewValue = Pair.Value;
            float OldValue = 0.0f;
            
            if (OldValues.Contains(StateType))
            {
                OldValue = OldValues[StateType];
            }
            
            if (OldValue != NewValue)
            {
                OnStateValueChanged.Broadcast(StateType, OldValue, NewValue);
            }
        }
        
        UE_LOG(LogTemp, Log, TEXT("游戏状态加载成功"));
    }
    else
    {
        // 如果没有存档，则初始化默认值
        InitializeDefaultValues();
        UE_LOG(LogTemp, Log, TEXT("未找到存档，已初始化默认值"));
    }
}

void URoguelikeStateManager::ResetAllStatesToDefault()
{
    InitializeDefaultValues();
    
    // 触发所有状态变化的委托
    for (auto& Pair : StateValues)
    {
        OnStateValueChanged.Broadcast(Pair.Key, Pair.Value, Pair.Value);
    }
}

float URoguelikeStateManager::GetStateMaxValue(ERoguelikeStateEnum StateType) const
{
    if (MaxValues.Contains(StateType))
    {
        return MaxValues[StateType];
    }
    return 0.0f;
}

float URoguelikeStateManager::GetStateValueAsPercentage(ERoguelikeStateEnum StateType) const
{
    float CurrentValue = GetStateValue(StateType);
    float MaxValue = GetStateMaxValue(StateType);
    
    if (MaxValue > 0)
    {
        return CurrentValue / MaxValue;
    }
    return 0.0f;
}

void URoguelikeStateManager::UpdateDefaultConfiguration()
{
    // 使用当前设置的默认值重新初始化
    InitializeDefaultValues();
    
    // 通知所有值已更改
    for (auto& Pair : StateValues)
    {
        OnStateValueChanged.Broadcast(Pair.Key, Pair.Value, Pair.Value);
    }
}

void URoguelikeStateManager::ApplyBattleVictoryRewards()
{
    // 增加等级
    ModifyStateValue(ERoguelikeStateEnum::Level, 1.0f);
    
    // 增加金钱
    ModifyStateValue(ERoguelikeStateEnum::Money, 5.0f);
    
    // 增加肥料
    ModifyStateValue(ERoguelikeStateEnum::Fertilizer, 3.0f);
    
    // 可选：保存状态
    SaveState();
    
    UE_LOG(LogTemp, Log, TEXT("已应用战斗胜利奖励"));
}

void URoguelikeStateManager::ApplyBattleDefeatPenalties()
{
    // 减少生命值
    ModifyStateValue(ERoguelikeStateEnum::Health, -1.0f);
    
    // 可选：保存状态
    SaveState();
    
    UE_LOG(LogTemp, Log, TEXT("已应用战斗失败惩罚"));
}

void URoguelikeStateManager::HandleLevelUpRewards(int32 NewLevel)
{
    // 检查是否达到特定等级
    if (NewLevel == 3 || NewLevel == 6 || NewLevel == 10)
    {
        // 生命值+1
        ModifyStateValue(ERoguelikeStateEnum::Health, 1.0f);
        
        // 携带上限+1
        ModifyStateValue(ERoguelikeStateEnum::CarryingLimit, 1.0f);
        
        // 肥料+5
        ModifyStateValue(ERoguelikeStateEnum::Fertilizer, 5.0f);
        
        // 可以在这里添加UI提示或特效
        // ...
    }
}