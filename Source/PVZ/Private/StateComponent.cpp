// Fill out your copyright notice in the Description page of Project Settings.


#include "StateComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	BaseMaxHealth = 0.f;
	BaseAttack = 0.f;
	BaseDefense = 0.f;
	BaseAttackInterval = 0.f;
	BaseCritRate = 0.f;
	BaseCritDamage = 0.f;
	// ...
}


// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UStateComponent::Init(int32 SelfPlantID)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("UStateComponent::Init : 通过%d读取基础属性"), SelfPlantID));
	return true;
}

