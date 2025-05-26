// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBase.h"
#include "BuffComponent.h"
#include "StateComponent.h"
#include "PlantHealthBaseComponent.h"
#include "NodeGameMode.h"
#include "Kismet/GameplayStatics.h"

APlantBase::APlantBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UPlantHealthBaseComponent>(TEXT("HealthComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	PlantID = 0;
}

bool APlantBase::Init()
{
	if (StateComponent)
	{
		if (StateComponent->Init(PlantID))
		{
			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
			ANodeGameMode* NodeGameMode = Cast<ANodeGameMode>(GameMode);
			UBuffComponent* BuffComponent = NodeGameMode ? NodeGameMode->PlantBuffComponent : nullptr;
			if (BuffComponent) HealthComponent->Init(BuffComponent->GetCurrentMaxHealth(StateComponent->BaseMaxHealth));
			else HealthComponent->Init(StateComponent->BaseMaxHealth);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APlantBase::Init : StateComponent Init failed"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::Init : StateComponent is null"));
		return false;
	}
}

//float APlantBase::CalculateOutgoingDamage(float Damage)
//{
//	if (!BuffComponent || !StateComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::CalculateOutgoingDamage : BuffComponent or StateComponent is null"));
//		return Damage;
//	}
//	return BuffComponent->CalculateOutgoingDamage(Damage);
//}

void APlantBase::BeAttacked(float Damage)
{
	float FinalDamage = Damage;
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	ANodeGameMode* NodeGameMode = Cast<ANodeGameMode>(GameMode);
	UBuffComponent* BuffComponent = NodeGameMode ? NodeGameMode->PlantBuffComponent : nullptr;
	if(BuffComponent)
		FinalDamage = BuffComponent->CalculateReceiveDamage(Damage);
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::BeAttacked : HealthComponent is null"));
		return;
	}
	HealthComponent->BeAttacked(FinalDamage);
}

float APlantBase::GetCurrentAttackInterval()
{
	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	ANodeGameMode* NodeGameMode = Cast<ANodeGameMode>(GameMode);
	UBuffComponent* BuffComponent = NodeGameMode ? NodeGameMode->PlantBuffComponent : nullptr;
	if (!BuffComponent || !StateComponent)
	{
		if (!BuffComponent)
			UE_LOG(LogTemp, Warning, TEXT("APlantBase::GetCurrentAttackInterval : BuffComponent is null"))
		else
			UE_LOG(LogTemp, Warning, TEXT("APlantBase::GetCurrentAttackInterval : StateComponent is null"))
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::GetCurrentAttackInterval : BuffComponent or StateComponent is null"));
		return -1;
	}
	return BuffComponent->GetCurrentAttackInterval(StateComponent->BaseAttackInterval);
}

void APlantBase::Dead()
{
}

//void APlantBase::AddBuff()
//{
//	if (!BuffComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddBuff : BuffComponent is null"));
//		return;
//	}
//	BuffComponent->AddBuff();
//	if (!StateComponent || !HealthComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddBuff : StateComponent or HealthComponent is null"));
//		return;
//	}
//	HealthComponent->SetCurrentMaxHealth(BuffComponent->GetCurrentMaxHealth(StateComponent));
//}

//void APlantBase::BuffUpdateOtherComponents()
//{
//
//}

//void APlantBase::AddHealth(float Value)
//{
//	if (!HealthComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealth : HealthComponent is null"));
//		return;
//	}
//	HealthComponent->AddHealth(Value);
//}
//
//void APlantBase::AddHealthPercent(float Rate)
//{
//	if (!HealthComponent)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealthPercent : HealthComponent is null"));
//		return;
//	}
//	HealthComponent->AddHealthPercent(Rate);
//}