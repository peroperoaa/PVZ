// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeGameMode.h"
#include "BuffComponent.h"
#include "ZombieBuffComponent.h"

void ANodeGameMode::SetSunlight(int32 NewAmount)
{
	OnSunlightChangedDelegate.Broadcast(NewAmount);
}

ANodeGameMode::ANodeGameMode()
{
	PlantBuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("PlantBuffComponent"));//TEMP
	ZombieBuffComponent = CreateDefaultSubobject<UZombieBuffComponent>(TEXT("ZombieBuffComponent"));//TEMP
	CurrentSunlight = 0.f;
}

void ANodeGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ANodeGameMode::Init(UBuffComponent* PlantComponent, UZombieBuffComponent* ZombieComponent)
{
	PlantBuffComponent = PlantComponent;
	ZombieBuffComponent = ZombieComponent;
}

int32 ANodeGameMode::GetCurrentSunlight() const
{
	return  CurrentSunlight;
}

void ANodeGameMode::AddSunlight(int32 Amount)
{
	CurrentSunlight += Amount;
	SetSunlight(CurrentSunlight);
}

bool ANodeGameMode::ConsumeSunlight(int32 AmountToConsume)
{
	if(CurrentSunlight >= AmountToConsume)
	{
		CurrentSunlight -= AmountToConsume;
		SetSunlight(CurrentSunlight);
		return true;
	}
	else
	{
		return false;
	}
}

//float ANodeGameMode::CalculatePlantDamageOutput(float InDamage)
//{
//	if (!PlantBuffComponent)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ANodeGameMode::CalculatePlantDamageOutput: PlantBuffComponent is null!"));
//		return InDamage;
//	}
//	//PlantBuffComponent->CalculateOutgoingDamage(InDamage,)
//	return InDamage;
//}
//
//float ANodeGameMode::CalculatePlantDamageTaken(float InDamage)
//{
//	return 0.0f;
//}
//
//float ANodeGameMode::CalculateZombieDamageOutput(float InDamage)
//{
//	return 0.0f;
//}
//
//float ANodeGameMode::CalculateZombieDamageTaken(float InDamage)
//{
//	return 0.0f;
//}

