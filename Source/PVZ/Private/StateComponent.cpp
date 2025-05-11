// Fill out your copyright notice in the Description page of Project Settings.


#include "StateComponent.h"
#include "Engine.h"
#include "PlantState.h"

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
	static ConstructorHelpers::FObjectFinder<UDataTable> TableType(TEXT("/Script/Engine.DataTable'/Game/DataTables/Plant/DT_PlantState.DT_PlantState'"));
	if (TableType.Succeeded())
	{
		DataTable = TableType.Object;
	}
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
	if (!DataTable)
		return false;
	FName RowName = FName(*FString::Printf(TEXT("Plant_%d"), SelfPlantID));
	static const FString ContextString(TEXT("UStateComponent::Init"));
	FPlantState* PlantData = DataTable->FindRow<FPlantState>(RowName, ContextString);
	if (PlantData)
	{
		BaseMaxHealth = PlantData->BaseMaxHealth;
		BaseAttack = PlantData->BaseAttack;
		BaseDefense = PlantData->BaseDefense;
		BaseAttackInterval = PlantData->BaseAttackInterval;
		BaseCritRate = PlantData->BaseCritRate;
		BaseCritDamage = PlantData->BaseCritDamage;
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to find row in DataTable"));
		return false;
	}
}

