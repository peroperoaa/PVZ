// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBase.h"
#include "BuffComponent.h"
#include "StateComponent.h"
#include "PlantHealthBaseComponent.h"

// Sets default values
APlantBase::APlantBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	HealthComponent = CreateDefaultSubobject<UPlantHealthBaseComponent>(TEXT("HealthComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	PlantID = 0;
}

// Called when the game starts or when spawned
void APlantBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlantBase::Init()
{
	if (StateComponent)
	{
		if(StateComponent->Init(PlantID))
			return HealthComponent->Init(StateComponent);
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

float APlantBase::CalculateOutgoingDamage(float Damage)
{
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::CalculateOutgoingDamage : BuffComponent or StateComponent is null"));
		return Damage;
	}
	return BuffComponent->CalculateOutgoingDamage(Damage, StateComponent);
}

float APlantBase::CalculateReceiveDamage(float Damage)
{
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::CalculateReceiveDamage : BuffComponent or StateComponent is null"));
		return Damage;
	}
	return BuffComponent->CalculateReceiveDamage(Damage, StateComponent);
}

float APlantBase::GetCurrentMaxHealth()
{
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::GetCurrentMaxHealth : BuffComponent or StateComponent is null"));
		return -1;
	}
	return BuffComponent->GetCurrentMaxHealth(StateComponent);
}

float APlantBase::GetCurrentAttackInterval()
{
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::GetCurrentAttackInterval : BuffComponent or StateComponent is null"));
		return -1;
	}
	return BuffComponent->GetCurrentAttackInterval(StateComponent);
}

