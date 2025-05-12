// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieStateComponent.h"
#include  "ZombieState.h"

// Sets default values for this component's properties
UZombieStateComponent::UZombieStateComponent()
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
	MoveSpeed = 0.f;
	static ConstructorHelpers::FObjectFinder<UDataTable> TableType(TEXT("/Script/Engine.DataTable'/Game/DataTables/Zombie/DT_ZombieState.DT_ZombieState'"));
	if (TableType.Succeeded())
	{
		DataTable = TableType.Object;
	}
	// ...
}


// Called when the game starts
void UZombieStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UZombieStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UZombieStateComponent::Init(int32 SelfZombieID)
{
	if (!DataTable)
		return false;
	FName RowName = FName(*FString::Printf(TEXT("Zombie_%d"), SelfZombieID));
	static const FString ContextString(TEXT("UZombieStateComponent::Init"));
	FZombieState* ZombieData = DataTable->FindRow<FZombieState>(RowName, ContextString);
	if (ZombieData)
	{
		BaseMaxHealth = ZombieData->BaseMaxHealth;
		BaseAttack = ZombieData->BaseAttack;
		BaseDefense = ZombieData->BaseDefense;
		BaseAttackInterval = ZombieData->BaseAttackInterval;
		BaseCritRate = ZombieData->BaseCritRate;
		BaseCritDamage = ZombieData->BaseCritDamage;
		MoveSpeed = ZombieData->MoveSpeed;
		return true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("UZombieStateCoponent::Init:Failed to find row in DataTable"));
	return false;
}

