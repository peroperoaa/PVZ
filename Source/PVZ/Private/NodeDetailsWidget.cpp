// Fill out your copyright notice in the Description page of Project Settings.

#include "NodeDetailsWidget.h"
#include "Kismet/GameplayStatics.h"

void UNodeDetailsWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    // 绑定确认按钮事件
    if (ConfirmButton)
    {
        ConfirmButton->OnClicked.AddDynamic(this, &UNodeDetailsWidget::OnConfirmButtonClicked);
    }
}

void UNodeDetailsWidget::SetNode(AMapNode* InNode)
{
    CurrentNode = InNode;
    
    if (CurrentNode)
    {
        // 获取枚举名称
        UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERoguelikeNodeTypes"), true);
        FString NodeTypeString;
        
        if (EnumPtr)
        {
            NodeTypeString = EnumPtr->GetNameStringByValue((int64)CurrentNode->NodeType);
            NodeTypeString.RemoveFromStart(TEXT("ERoguelikeNodeTypes::"));
        }
        
        // 设置标题
        if (NodeTitleText)
        {
            NodeTitleText->SetText(FText::FromString(NodeTypeString));
        }
        
        // 设置描述内容（根据节点类型设置不同的描述）
        if (NodeDescriptionText)
        {
            FString Description;
            switch (CurrentNode->NodeType)
            {
            case ERoguelikeNodeTypes::Combat:
                Description = FString::Printf(TEXT("战斗\n可能遭遇敌人并获得奖励"));
                break;
            case ERoguelikeNodeTypes::Encounter:
                Description = TEXT("不期而遇\n触发随机事件，可能获得奖励或惩罚");
                break;
            case ERoguelikeNodeTypes::Shop:
                Description = TEXT("商店\n购买道具和升级");
                break;
            case ERoguelikeNodeTypes::Wish:
                Description = TEXT("得偿所愿\n获得收藏品或植物");
                break;
            default:
                Description = TEXT("未知节点类型");
                break;
            }
            NodeDescriptionText->SetText(FText::FromString(Description));
        }
        
        // 设置图标（需在蓝图中实现）
        // 可以根据节点类型设置不同的图标
    }
}

void UNodeDetailsWidget::OnConfirmButtonClicked()
{
    if (CurrentNode)
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            // 进入节点
            CurrentNode->EnterNode(PC);
            
            // 关闭详细信息UI
            RemoveFromParent();
        }
    }
}