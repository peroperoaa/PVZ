// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeGameMode.h"
#include "BuffComponent.h"
#include "ZombieBuffComponent.h"

ANodeGameMode::ANodeGameMode()
{
	PlantBuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("PlantBuffComponent"));//TEMP
	ZombieBuffComponent = CreateDefaultSubobject<UZombieBuffComponent>(TEXT("ZombieBuffComponent"));//TEMP
}

void ANodeGameMode::Init(UBuffComponent* PlantComponent, UZombieBuffComponent* ZombieComponent)
{
	PlantBuffComponent = PlantComponent;
	ZombieBuffComponent = ZombieComponent;
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

