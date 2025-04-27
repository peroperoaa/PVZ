// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBase.h"
#include "BuffComponent.h"
#include "StateComponent.h"
#include "PaperFlipbookComponent.h"
#include "PlantHealthBaseComponent.h"

// Sets default values
APlantBase::APlantBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperSpriteComponent"));
	HealthComponent = CreateDefaultSubobject<UPlantHealthBaseComponent>(TEXT("HealthComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	RootComponent = SpriteComponent;
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

void APlantBase::BeAttacked(float Damage)
{
	float FinalDamage = Damage;
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::CalculateReceiveDamage : BuffComponent or StateComponent is null"))
	}
	else
		FinalDamage = BuffComponent->CalculateReceiveDamage(Damage, StateComponent);
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::BeAttacked : HealthComponent is null"));
		return;
	}
	HealthComponent->BeAttacked(FinalDamage);
}

void APlantBase::AddBuff()
{
	if (!BuffComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddBuff : BuffComponent is null"));
		return;
	}
	BuffComponent->AddBuff();
	if (!StateComponent || !HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddBuff : StateComponent or HealthComponent is null"));
		return;
	}
	HealthComponent->SetCurrentMaxHealth(BuffComponent->GetCurrentMaxHealth(StateComponent));
}

void APlantBase::BuffUpdateOtherComponents()
{

}

void APlantBase::AddHealth(float Value)
{
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealth : HealthComponent is null"));
		return;
	}
	HealthComponent->AddHealth(Value);
}

void APlantBase::AddHealthPercent(float Rate)
{
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealthPercent : HealthComponent is null"));
		return;
	}
	HealthComponent->AddHealthPercent(Rate);
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