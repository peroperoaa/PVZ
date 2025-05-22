// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeUIWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStatics.h"

void UNodeUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
    
	// 绑定按钮事件
	if (ActionButton)
	{
		ActionButton->OnClicked.AddDynamic(this, &UNodeUIWidget::OnActionButtonClicked);
	}
}

void UNodeUIWidget::SetNode(AMapNode* InNode)
{
	CurrentNode = InNode;
    
	if (CurrentNode && NodeInfoText)
	{
		// 方法1：使用UEnum反射获取枚举名称
		UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERoguelikeNodeTypes"), true);
		if (EnumPtr)
		{
			FString NodeTypeString = EnumPtr->GetNameStringByValue((int64)CurrentNode->NodeType);
			// 移除枚举类型前缀
			NodeTypeString.RemoveFromStart(TEXT("ERoguelikeNodeTypes::"));
            
			// 设置文本
			NodeInfoText->SetText(FText::FromString(NodeTypeString));
		}
	}
}

void UNodeUIWidget::OnActionButtonClicked()
{
	if (CurrentNode && NodeDetailsWidgetClass)
	{
		UNodeDetailsWidget* DetailsWidget = CreateWidget<UNodeDetailsWidget>(GetWorld(), NodeDetailsWidgetClass);
		if (DetailsWidget)
		{
			DetailsWidget->SetNode(CurrentNode);
			DetailsWidget->AddToViewport();
		}
	}
}

void UNodeUIWidget::UpdateNodeState()
{
	if (!CurrentNode)
		return;
    
	// 根据节点状态更新UI
	if (CurrentNode->bIsDisabled)
	{
		// 例如：禁用按钮，改变节点外观等
		// 这部分可以在蓝图中实现，这里添加BlueprintImplementableEvent
		OnNodeDisabled();
	}
	else if (CurrentNode->bIsVisited)
	{
		// 显示已访问状态
		OnNodeVisited();
	}
    
	// 刷新UI
	InvalidateLayoutAndVolatility();
}