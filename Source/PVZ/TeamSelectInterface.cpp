// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSelectInterface.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MainInterface.h"

bool UTeamSelectInterface::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	if (Team1) Team1->OnClicked.AddDynamic(this, &UTeamSelectInterface::Team1ButtonClicked);
	if (Team2) Team2->OnClicked.AddDynamic(this, &UTeamSelectInterface::Team2ButtonClicked);
	if (Team3) Team3->OnClicked.AddDynamic(this, &UTeamSelectInterface::Team3ButtonClicked);
	if (Team4) Team4->OnClicked.AddDynamic(this, &UTeamSelectInterface::Team4ButtonClicked);
	return true;
}

void UTeamSelectInterface::Team1ButtonClicked()
{
	Team = TEXT("Team1");
	UpdateSelectedTeam();
}

void UTeamSelectInterface::Team2ButtonClicked()
{
	Team = TEXT("Team2");
	UpdateSelectedTeam();
}

void UTeamSelectInterface::Team3ButtonClicked()
{
	Team = TEXT("Team3");
	UpdateSelectedTeam();
}

void UTeamSelectInterface::Team4ButtonClicked()
{
	Team = TEXT("Team4");
	UpdateSelectedTeam();
}

void UTeamSelectInterface::UpdateSelectedTeam()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UMainInterface::StaticClass(), false);

	if (FoundWidgets.Num() > 0)
	{
		UMainInterface* MainWidget = Cast<UMainInterface>(FoundWidgets.Last());
		if (MainWidget)
		{
			MainWidget->SelectedTeam = Team;
			MainWidget->SetNextStepButtonEnable();
		}
	}
}



