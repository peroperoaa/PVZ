// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MapNode.h"
#include "NodeDetailsWidget.generated.h"

/**
 * 节点详细信息UI，在屏幕左侧显示节点的具体信息
 */
UCLASS()
class PVZ_API UNodeDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// UI组件
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* DetailsCanvas;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NodeTitleText;
    
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NodeDescriptionText;
    
	UPROPERTY(meta = (BindWidget))
	class UButton* ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConfirmButtonText;

	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;
    
	// 初始化控件
	virtual void NativeConstruct() override;
	
	// 设置关联的节点
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetNode(AMapNode* InNode);
    
private:
	// 当前关联的节点
	UPROPERTY()
	AMapNode* CurrentNode = nullptr;
    
	// 确认按钮点击事件
	UFUNCTION()
	void OnConfirmButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();
};