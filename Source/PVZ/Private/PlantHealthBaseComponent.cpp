// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantHealthBaseComponent.h"
#include "StateComponent.h"
#include "PlantBase.h"
#include "ZombieBase.h"
// Sets default values for this component's properties
UPlantHealthBaseComponent::UPlantHealthBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = 0.f;       
	CalculatedMaxHealth = 0.f;
	// ...
}


// Called when the game starts
void UPlantHealthBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlantHealthBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlantHealthBaseComponent::SetCurrentMaxHealth(float NewMaxHealth)
{
	if (NewMaxHealth < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlantHealthBaseComponent::SetCurrentMaxHealth : NewMaxHealth is less than 0"));
		return; 
	}
	CurrentHealth = FMath::Clamp(CurrentHealth / CalculatedMaxHealth, 0.f, 1.f) * NewMaxHealth;
	CalculatedMaxHealth = NewMaxHealth;
}

void UPlantHealthBaseComponent::BeAttacked(float FinalDamage)
{
	if (FinalDamage < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlantHealthBaseComponent::BeAttacked : FinalDamage is less than 0"));
		return;
	}
	CurrentHealth -= FinalDamage;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CurrentHealth: %f"), CurrentHealth));
	if (CurrentHealth <= 0)
	{
		AActor* Owner = GetOwner();
		if (!Owner)
		{
			UE_LOG(LogTemp, Warning, TEXT("UPlantHealthBaseComponent::BeAttacked : Owner is null"));
			return;
		}
		APlantBase* PlantBase = Cast<APlantBase>(Owner);
		if (!PlantBase)
		{
			AZombieBase* ZombieBase = Cast<AZombieBase>(Owner);
			if (!ZombieBase)
			{
				UE_LOG(LogTemp, Warning, TEXT("UPlantHealthBaseComponent::BeAttacked : Owner is not PlantBase or ZombieBase"));
				return;
			}
			else
			{
				ZombieBase->Dead();
				return;
			}
		}
		PlantBase->Dead();
	}
}

void UPlantHealthBaseComponent::Init(float MaxHealth)
{
	CurrentHealth = CalculatedMaxHealth = MaxHealth;
}


//void UPlantHealthBaseComponent::AddHealth(float Value)
//{
//	if(Value < 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UPlantHealthBaseComponent::AddHealth : Value is less than 0"));
//		return;
//	}
//	CurrentHealth = FMath::Min(CurrentHealth + Value, CalculatedMaxHealth);
//}
//
//void UPlantHealthBaseComponent::AddHealthPercent(float Rate)
//{
//	if (Rate < 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UPlantHealthBaseComponent::AddHealthPercent : Rate is less than 0"));
//		return;
//	}
//	CurrentHealth = FMath::Min(CurrentHealth + Rate * CalculatedMaxHealth, CalculatedMaxHealth);
//}



