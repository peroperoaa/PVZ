// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "ZombieStateComponent.h"
#include "PlantHealthBaseComponent.h"
#include "ZombieBuffComponent.h"
#include "kismet/GameplayStatics.h"
#include "NodeGameMode.h"

AZombieBase::AZombieBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UPlantHealthBaseComponent>(TEXT("HealthComponent"));
	StateComponent = CreateDefaultSubobject<UZombieStateComponent>(TEXT("StateComponent"));
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	ANodeGameMode* NodeGameMode = Cast<ANodeGameMode>(GameMode);
	BuffComponent = NodeGameMode ? NodeGameMode->ZombieBuffComponent : nullptr;
	ZombieID = 0;
}

bool AZombieBase::Init()
{
	if (StateComponent)
	{
		if (StateComponent->Init(ZombieID))
		{
			if (BuffComponent) HealthComponent->Init(BuffComponent->GetCurrentMaxHealth(StateComponent->BaseMaxHealth));
			else HealthComponent->Init(StateComponent->BaseMaxHealth);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Init : StateComponent Init failed"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Init : StateComponent is null"));
		return false;
	}
}

void AZombieBase::BeAttacked(float Damage)
{
	float FinalDamage = Damage;
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CalculateReceiveDamage : BuffComponent or StateComponent is null"))
	}
	else
		FinalDamage = BuffComponent->CalculateReceiveDamage(Damage);
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::BeAttacked : HealthComponent is null"));
		return;
	}
	HealthComponent->BeAttacked(FinalDamage);
}

void AZombieBase::Dead()
{
}

float AZombieBase::CalculateOutgoingDamage(float Damage)
{
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CalculateOutgoingDamage : BuffComponent or StateComponent is null"));
		return Damage;
	}
	return BuffComponent->CalculateOutgoingDamage(Damage);
}

//void AZombieBase::AddHealth(float Value)
//{
//	if (!HealthComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealth : HealthComponent is null"));
//		return;
//	}
//	HealthComponent->AddHealth(Value);
//}
//
//void AZombieBase::AddHealthPercent(float Rate)
//{
//	if (!HealthComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealthPercent : HealthComponent is null"));
//		return;
//	}
//	HealthComponent->AddHealthPercent(Rate);
//}


