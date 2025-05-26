// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBuffComponent.h"
#include "ZombieStateComponent.h"

// Sets default values for this component's properties
UZombieBuffComponent::UZombieBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ExtraMaxHealth = 0.f;
	ExtraAttack = 0.f;
	ExtraDefense = 0.f;
	DamageReductionRate = 0.f;
	ExtraCritRate = 0.f;
	ExtraCritDamage = 0.f;
	ExtraMoveSpeed = 0.f;
	AttackRate = 1.f;
	// ...
}


// Called when the game starts
void UZombieBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UZombieBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UZombieBuffComponent::CalculateOutgoingDamage(float Damage)
{
	float FinalAttack = (Damage + ExtraAttack) * (1 + AttackRate);
	float TotalCritRate = ExtraCritRate;
	float FinalCritRate = FMath::Clamp(TotalCritRate, 0.f, 1.f);
	float FinalCritDamage = ExtraCritDamage;
	bool bIsCrit = FMath::FRand() < FinalCritRate;
	float FinalDamage = 0.f;
	if (bIsCrit)
		FinalDamage = FinalAttack * (1 + FinalCritDamage);
	else
		FinalDamage = FinalAttack;
	return FinalDamage;
}

float UZombieBuffComponent::CalculateReceiveDamage(float Damage)
{
	float FinalDefense = ExtraDefense;
	float AfterDefenseCalculatedDamage = Damage * (1 - FinalDefense / (FinalDefense + 600));
	float FinalDamage = AfterDefenseCalculatedDamage * (1 - FMath::Clamp(DamageReductionRate, 0.f, 1.f));
	return FinalDamage;
}

float UZombieBuffComponent::GetCurrentMaxHealth(float InBaseMaxHealth)
{
	return InBaseMaxHealth + ExtraMaxHealth;
}

float UZombieBuffComponent::GetCurrentAttackInterval(float BaseAttackInterval)
{
	return BaseAttackInterval / AttackRate;
}
