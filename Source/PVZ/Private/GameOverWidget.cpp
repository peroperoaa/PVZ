// GameOverWidget.cpp
#include "GameOverWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/TextBlock.h"

void UGameOverWidget::ShowGameEnd(EGameEndState EndState)
{
	// 设置标题文本
	if (TitleText)
	{
		if (EndState == EGameEndState::GameOver)
		{
			TitleText->SetText(FText::FromString(TEXT("游戏结束")));
		}
		else
		{
			TitleText->SetText(FText::FromString(TEXT("游戏胜利")));
		}
	}
    
	// 添加到视口并设置为可见
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
    
	// 获取玩家控制器
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		// 显示鼠标光标
		PlayerController->SetShowMouseCursor(true);
        
		// 设置输入模式为UI模式
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}
}

void UGameOverWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

void UGameOverWidget::ReturnToMainMenu()
{
	// 预留功能，等待主界面完成后实现
	RemoveFromParent();
}