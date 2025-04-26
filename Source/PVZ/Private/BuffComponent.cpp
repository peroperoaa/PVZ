// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "StateComponent.h"


// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ExtraMaxHealth = 0.f;
	ExtraAttack = 0.f;
	AttackRate = 0.f;
	ExtraDefense = 0.f;
	AttackSpeedRate = 1.f;
	DamageReductionRate = 0.f;
	ExtraCritRate = 0.f;
	ExtraCritDamage = 0.f;
	// ...
}


// Called when the game starts
void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuffComponent::CalculateBuffValue()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UBuffComponent::CalculateBuffValue : 计算Buff组件数值"));
}

float UBuffComponent::CalculateOutgoingDamage(float Damage, UStateComponent* SelfStateComponent)
{
	if (!SelfStateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBuffComponent::CalculateOutgoingDamage : SelfStateComponent is null"));
		return Damage;
	}
	float FinalAttack = (Damage + ExtraAttack) * (1 + AttackRate);
	float TotalCritRate = SelfStateComponent->BaseCritRate + ExtraCritRate;
	float FinalCritRate = FMath::Clamp(TotalCritRate, 0.f, 1.f);
	float FinalCritDamage = SelfStateComponent->BaseCritDamage + ExtraCritDamage;
	bool bIsCrit = FMath::FRand() < FinalCritRate;
	float FinalDamage = 0.f;
	if (bIsCrit)
		FinalDamage = FinalAttack * (1 + FinalCritDamage);
	else 
		FinalDamage = FinalAttack;
	return FinalAttack;
}

float UBuffComponent::CalculateReceiveDamage(float Damage, UStateComponent* SelfStateComponent)
{
	if (!SelfStateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBuffComponent::CalculateReceiveDamage : SelfStateComponent is null"));
		return Damage;
	}
	float FinalDefense = SelfStateComponent->BaseDefense + ExtraDefense;
	float AfterDefenseCalculatedDamage = Damage * (1 - FinalDefense / (FinalDefense + 600));
	float FinalDamage = AfterDefenseCalculatedDamage * (1 - FMath::Clamp(DamageReductionRate, 0.f, 1.f));
	return FinalDamage;
}

float UBuffComponent::GetCurrentMaxHealth(UStateComponent* SelfStateComponent)
{
	if (!SelfStateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBuffComponent::GetCurrentMaxHealth : SelfStateComponent is null"));
		return -1;
	}
	return SelfStateComponent->BaseMaxHealth + ExtraMaxHealth;
}

float UBuffComponent::GetCurrentAttackInterval(UStateComponent* SelfStateComponent)
{
	if (!SelfStateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBuffComponent::GetCurrentAttackInterval : SelfStateComponent is null"));
		return -1;
	}
	return SelfStateComponent->BaseAttackInterval / AttackSpeedRate;
}

void UBuffComponent::AddBuff()
{
	UE_LOG(LogTemp, Warning, TEXT("UBuffComponent::AddBuff : Buff组件添加Buff"));
}

