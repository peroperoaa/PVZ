// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectionCard.h"
#include "Components/Button.h"
#include "Attire.h"
#include "CollectionInterface.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

bool UCollectionCard::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (Button) {
		Button->OnClicked.AddDynamic(this, &UCollectionCard::ButtonClicked);
	}
	return true;
}

void UCollectionCard::NativeConstruct()
{
	UI_Attire->InitAttire(FMath::RandRange(1, 3));
}

void UCollectionCard::ButtonClicked()
{
	UCollectionInterface* CollectionInterface = CreateWidget<UCollectionInterface>(GetWorld(), UCollectionInterface::StaticClass());
	CollectionInterface->UpdateAttire(UI_Attire->AttireInfo.AttireId, UI_Attire);
	RemoveFromParent();
}
