// Fill out your copyright notice in the Description page of Project Settings.


#include "MainInterface.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "CollectionInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WrapBox.h"
#include "UMG.h"

int32 PreviousIndex = 0;



void UMainInterface::UpdateAttire(UAttire* AddingAttire)
{
	if (UI_CollectionInterface) {
		UWrapBox* TargetWraBox = Cast<UWrapBox>(UI_CollectionInterface->GetWidgetFromName(TEXT("AttireContainer")));
		if (TargetWraBox && AddingAttire) {
			TargetWraBox->AddChild(AddingAttire);
			AddingAttire->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
	}
}

bool UMainInterface::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	if (NextStepButton) {
		NextStepButton->OnClicked.AddDynamic(this, &UMainInterface::NextStepButtonClicked);
	}
	if (PreviousStepButton) {
		PreviousStepButton->OnClicked.AddDynamic(this, &UMainInterface::PreviousStepButtonClicked);
	}
	if (CollectionInterfaceButton) {
		CollectionInterfaceButton->OnClicked.AddDynamic(this, &UMainInterface::CollectionInterfaceButtonClicked);
	}
        return true;
}

void UMainInterface::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainInterface::NextStepButtonClicked()
{
	if (WidgetSwitcher)
	{
		int32 CurrentIndex = WidgetSwitcher->GetActiveWidgetIndex();
		if (CurrentIndex < 2)// 2为允许使用下一步按钮的界面个数
		{
			WidgetSwitcher->SetActiveWidgetIndex(CurrentIndex + 1);
			
		}
	}
}

void UMainInterface::PreviousStepButtonClicked()
{
	if (WidgetSwitcher)
	{
		int32 CurrentIndex = WidgetSwitcher->GetActiveWidgetIndex();
		if (CurrentIndex == SwitcherChlidNum - 1) {
			WidgetSwitcher->SetActiveWidgetIndex(PreviousIndex);
			CollectionInterfaceButton->SetIsEnabled(true);
			NextStepButton->SetIsEnabled(true);
			return;
		}
		WidgetSwitcher->SetActiveWidgetIndex(CurrentIndex - 1);
		
	}
}

void UMainInterface::CollectionInterfaceButtonClicked()
{
	if (WidgetSwitcher) {
		PreviousIndex = WidgetSwitcher->GetActiveWidgetIndex();
		WidgetSwitcher->SetActiveWidgetIndex(SwitcherChlidNum - 1);
		CollectionInterfaceButton->SetIsEnabled(false);
		NextStepButton->SetIsEnabled(false);
		
	}
}
