// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamSelectInterface.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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
}

void UTeamSelectInterface::Team2ButtonClicked()
{
	Team = TEXT("Team2");
}

void UTeamSelectInterface::Team3ButtonClicked()
{
	Team = TEXT("Team3");
}

void UTeamSelectInterface::Team4ButtonClicked()
{
	Team = TEXT("Team4");
}

