// Fill out your copyright notice in the Description page of Project Settings.


#include "MainInterface.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

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
        return true;
}

void UMainInterface::NextStepButtonClicked()
{
	if (WidgetSwitcher)
	{
		int32 CurrentIndex = WidgetSwitcher->GetActiveWidgetIndex();
		int32 NumWidgets = WidgetSwitcher->GetNumWidgets();
		if (CurrentIndex < NumWidgets - 1)
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
		if (CurrentIndex > 0)
		{
			WidgetSwitcher->SetActiveWidgetIndex(CurrentIndex - 1);
		}
	}
}
