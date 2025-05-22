// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoguelikeMapManager.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "NodeDetailsWidget.h"
#include "NodeUIWidget.generated.h"

class AMapNode;

/**
 * 节点UI控件，用于显示节点信息并提供交互功能
 */
UCLASS()
class PVZ_API UNodeUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	// UI组件
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* NodeCanvas;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* ActionButton;
    
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NodeInfoText;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UNodeDetailsWidget> NodeDetailsWidgetClass;
	
	// 初始化控件
	virtual void NativeConstruct() override;

	// 设置关联的节点
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetNode(AMapNode* InNode);

	// 更新节点UI状态（根据节点是否禁用等）
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateNodeState();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnNodeDisabled();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnNodeVisited();
	
private:
	// 当前关联的节点
	UPROPERTY()
	AMapNode* CurrentNode = nullptr;

	// 按钮点击事件
	UFUNCTION()
	void OnActionButtonClicked();
	
};