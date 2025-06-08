// Fill out your copyright notice in the Description page of Project Settings.


#include "DifficultySelectInterface.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/Widget.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MainInterface.h"


bool UDifficultySelectInterface::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	if (AddDifficultyButton) {
		AddDifficultyButton->OnClicked.AddDynamic(this, &UDifficultySelectInterface::AddDifficultyButtonClicked);
	}
        if (MinusDifficultyButton) {
                MinusDifficultyButton->OnClicked.AddDynamic(this, &UDifficultySelectInterface::MinusDifficultyButtonClicked);
        }
	return true;
}

void UDifficultySelectInterface::NativeConstruct()
{
        Super::NativeConstruct();
}


void UDifficultySelectInterface::ScrollToDifficulty()
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

                if (DisplayName == FString::FromInt(Difficulty))
                {
                        // 滚动到目标子控件
                        DifficultySelectScrollBox->ScrollWidgetIntoView(Child, true, EDescendantScrollDestination::Center, 0.0f);
                        return;
                }
        }
}

void UDifficultySelectInterface::SetDifficultyButtonForbid()
{
        if (Difficulty == 1) {
                MinusDifficultyButton->SetIsEnabled(false);
        }
        else if (Difficulty == 9) {
                AddDifficultyButton->SetIsEnabled(false);
        }
        else {
                MinusDifficultyButton->SetIsEnabled(true);
                AddDifficultyButton->SetIsEnabled(true);
        }
        
}

void UDifficultySelectInterface::AddDifficultyButtonClicked()
{
        if (Difficulty >= 9) return;
	Difficulty++;
        UpdateDifficulty();
        //ScrollToDifficulty();
}

void UDifficultySelectInterface::MinusDifficultyButtonClicked()
{
        if (Difficulty <= 1) return;
        Difficulty--;
        UpdateDifficulty();
        //ScrollToDifficulty();
}

void UDifficultySelectInterface::UpdateDifficulty()
{
        TArray<UUserWidget*> FoundWidgets;
        UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UMainInterface::StaticClass(), false);

        if (FoundWidgets.Num() > 0)
        {
                UMainInterface* MainWidget = Cast<UMainInterface>(FoundWidgets.Last());
                if (MainWidget)
                {
                        MainWidget->SelectedDifficulty = Difficulty;
                }
        }
}


