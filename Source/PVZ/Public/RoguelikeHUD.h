// RoguelikeHUD.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RoguelikeStateManager.h"
#include "RoguelikeHUD.generated.h"

UCLASS()
class PVZ_API ARoguelikeHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARoguelikeHUD();

	virtual void DrawHUD() override;
    
	// 获取StateManager
	UFUNCTION(BlueprintCallable, Category = "Rogue|HUD")
	URoguelikeStateManager* GetStateManager() const;
    
	// 更新数据事件处理
	UFUNCTION()
	void OnStateValueUpdated(ERoguelikeStateEnum StateType, float OldValue, float NewValue);
    
protected:
	virtual void BeginPlay() override;
    
	// 绘制状态值
	void DrawStateValue(FString Label, ERoguelikeStateEnum StateType, float X, float Y);
    
private:
	// 状态管理器引用
	UPROPERTY()
	URoguelikeStateManager* StateManager;
    
	// 绘制设置
	UPROPERTY(EditDefaultsOnly, Category = "Rogue|HUD")
	UFont* HUDFont;
    
	UPROPERTY(EditDefaultsOnly, Category = "Rogue|HUD")
	FLinearColor TextColor;
};