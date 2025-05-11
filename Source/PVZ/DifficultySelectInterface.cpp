// Fill out your copyright notice in the Description page of Project Settings.


#include "DifficultySelectInterface.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/Widget.h"
#include "Components/PanelWidget.h"

bool UDifficultySelectInterface::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	if (AddDifficultyButton) {
		AddDifficultyButton->OnClicked.AddDynamic(this, &UDifficultySelectInterface::AddDifficultyButtonClicked);
	}
	return true;
}
void UDifficultySelectInterface::NativeConstruct()
{
        Super::NativeConstruct();

        ScrollToDIfficulty();
}

void UDifficultySelectInterface::ScrollToDIfficulty()
{
	if (!DifficultySelectScrollBox || Difficulty < 1) {
		return;
	}
        // 获取 ScrollBox 的所有子控件
        const TArray<UWidget*> Children = DifficultySelectScrollBox->GetAllChildren();

        for (UWidget* Child : Children)
        {
                if (!Child)
                {
                        continue;
                }

                // 获取子控件的显示名称
                const FString DisplayName = Child->GetName();

                // 检查显示名称是否与 Difficulty 匹配
                if (DisplayName == FString::FromInt(Difficulty))
                {
                        // 将匹配的控件滚动到视图中
                        DifficultySelectScrollBox->ScrollWidgetIntoView(Child, true, EDescendantScrollDestination::Center, 0.0f);
                        break;
                }
        }
}

void UDifficultySelectInterface::AddDifficultyButtonClicked()
{
	Difficulty++;
        ScrollToDIfficulty();
}


