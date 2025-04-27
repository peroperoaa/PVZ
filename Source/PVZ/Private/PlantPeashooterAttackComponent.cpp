// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantPeashooterAttackComponent.h"
#include "PlantBase.h"

// Sets default values for this component's properties
UPlantPeashooterAttackComponent::UPlantPeashooterAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	AttackInterval = -1.f;
	// ...
}


// Called when the game starts
void UPlantPeashooterAttackComponent::BeginPlay()
{
	Super::BeginPlay(); 
	if (!AttackProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlantPeashooterAttackComponent::BeginPlay : AttackProjectileClass is null"));
		return;
	}
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlantPeashooterAttackComponent::BeginPlay : Owner is null"));
		return;
	}
	APlantBase* Plant = Cast<APlantBase>(Owner);
	if (!Plant)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlantPeashooterAttackComponent::BeginPlay : Plant is null"));
		return;
	}
	if (AttackInterval < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlantPeashooterAttackComponent::BeginPlay : AttackInterval is error"));
		return;
	}
	//GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, Owner, &APlantBase::OnTryAttack, AttackInterval, true);
	// ...
	
}

void UPlantPeashooterAttackComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}


// Called every frame
void UPlantPeashooterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlantPeashooterAttackComponent::OnTryAttack()
{
}
