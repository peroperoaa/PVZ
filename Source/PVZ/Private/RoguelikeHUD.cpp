// RoguelikeHUD.cpp
#include "RoguelikeHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "RoguelikeGameInstance.h"
#include "RoguelikeStateManager.h"

ARoguelikeHUD::ARoguelikeHUD()
{
    // 设置默认值
    TextColor = FLinearColor::White;
}

void ARoguelikeHUD::BeginPlay()
{
    Super::BeginPlay();

    // 获取StateManager
    StateManager = GetStateManager();

    // 注册状态变化事件
    if (StateManager)
    {
        StateManager->OnStateValueChanged.AddDynamic(this, &ARoguelikeHUD::OnStateValueUpdated);
    }
}

void ARoguelikeHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!StateManager)
    {
        StateManager = GetStateManager();
        if (!StateManager) return;
    }

    // 绘制各种状态值
    float StartX = 50.0f;
    float StartY = 50.0f;
    float YOffset = 30.0f;

    DrawStateValue(TEXT("生命值:"), ERoguelikeStateEnum::Health, StartX, StartY);
    DrawStateValue(TEXT("等级:"), ERoguelikeStateEnum::Level, StartX, StartY + YOffset);
    DrawStateValue(TEXT("肥料:"), ERoguelikeStateEnum::Fertilizer, StartX, StartY + YOffset * 2);
    DrawStateValue(TEXT("金钱:"), ERoguelikeStateEnum::Money, StartX, StartY + YOffset * 3);
    DrawStateValue(TEXT("携带上限:"), ERoguelikeStateEnum::CarryingLimit, StartX, StartY + YOffset * 4);
}

void ARoguelikeHUD::DrawStateValue(FString Label, ERoguelikeStateEnum StateType, float X, float Y)
{
    if (!StateManager) return;

    float Value = StateManager->GetStateValue(StateType);;

    FString DisplayString;
    
    DisplayString = FString::Printf(TEXT("%s %.0f"), *Label, Value);
    

    // 绘制文本
    DrawText(DisplayString, TextColor, X, Y, HUDFont, 1.5f);
}

URoguelikeStateManager* ARoguelikeHUD::GetStateManager() const
{
    URoguelikeGameInstance* GameInstance = Cast<URoguelikeGameInstance>(GetWorld()->GetGameInstance());
    if (GameInstance && GameInstance->StateManager)
    {
        return GameInstance->StateManager;
    }
    return nullptr;
}

void ARoguelikeHUD::OnStateValueUpdated(ERoguelikeStateEnum StateType, float OldValue, float NewValue)
{
    // 状态值变化时不需要特殊处理，DrawHUD会自动使用最新值
}