// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionInterface.h"
#include "Attire.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MainInterface.h"

TArray<int32> UCollectionInterface::AttireIds;

bool UCollectionInterface::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	Display_Image.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
	return true;
}

void UCollectionInterface::NativeConstruct()
{
	AttireIds.Empty();
}

void UCollectionInterface::SetDisplayInfo(const FAttireInfo& AttireInfo)
{
	Display_Image = AttireInfo.AttireImage;
	Display_Name = FText::FromString(AttireInfo.AttireName);
	Display_Introduction = FText::FromString(AttireInfo.AttireIntroduction);
}

void UCollectionInterface::UpdateAttire(int32 TargetId, UAttire* AddingAttire)
{
	if (TargetId < 1 || TargetId >3) {
		return;
	}
	if (!UCollectionInterface::AttireIds.Contains(TargetId)) {
		UCollectionInterface::AttireIds.Add(TargetId);
		/*UAttire* AddingAttire = CreateWidget<UAttire>(GetWorld(), UAttire::StaticClass());
		AddingAttire->InitAttire(TargetId);*/
	

		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UMainInterface::StaticClass(), false);

		if (FoundWidgets.Num() > 0)
		{
			UMainInterface* MainWidget = Cast<UMainInterface>(FoundWidgets.Last());
			if (MainWidget)
			{
				MainWidget->UpdateAttire(AddingAttire); 
			}
		}
	}
}
