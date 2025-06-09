// Fill out your copyright notice in the Description page of Project Settings.


#include "Sunflower.h"

ASunflower::ASunflower()
{
	PlantID = 3;
	Init();
	ProductInterval = 0.f;
}

void ASunflower::BeginPlay()
{
	Super::BeginPlay();
	ProductInterval = GetCurrentAttackInterval();
	if (ProductInterval > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(CreateSunlightTimerHandle, this, &ASunflower::OnCreateSunlight, ProductInterval, true, ProductInterval);
	}
}

void ASunflower::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(CreateSunlightTimerHandle);
}

void ASunflower::Dead()
{
	Destroy();
}