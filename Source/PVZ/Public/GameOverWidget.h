// GameOverWidget.h
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

UENUM(BlueprintType)
enum class EGameEndState : uint8
{
	GameOver,    // 游戏失败
	GameVictory  // 游戏胜利
};

UCLASS()
class PVZ_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
	// 显示游戏结束界面
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowGameEnd(EGameEndState EndState);
    
	// 退出游戏
	UFUNCTION(BlueprintCallable, Category = "UI")
	void QuitGame();
    
	// 返回主界面（预留）
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ReturnToMainMenu();
    
	// 获取标题文本组件（在蓝图中绑定）
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TitleText;
};