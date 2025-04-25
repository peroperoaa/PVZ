// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"

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
}

float UBuffComponent::CalculateAttackValue(float BaseAttack)
{
	return 0.0f;
}

