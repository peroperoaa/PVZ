// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "PaperFlipbookComponent.h"
#include "ZombieStateComponent.h"
#include "PlantHealthBaseComponent.h"
#include "ZombieBuffComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AZombieBase::AZombieBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperSpriteComponent"));
	BuffComponent = CreateDefaultSubobject<UZombieBuffComponent>(TEXT("BuffComponent"));
	HealthComponent = CreateDefaultSubobject<UPlantHealthBaseComponent>(TEXT("HealthComponent"));
	StateComponent = CreateDefaultSubobject<UZombieStateComponent>(TEXT("StateComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AZombieBase::Init()
{
	if (StateComponent)
	{
		if (StateComponent->Init(ZombieID))
		{
			HealthComponent->Init(StateComponent->BaseMaxHealth);
			return true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Init : StateComponent Init failed"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::Init : StateComponent is null"));
		return false;
	}
}

void AZombieBase::BeAttacked(float Damage)
{
	float FinalDamage = Damage;
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::CalculateReceiveDamage : BuffComponent or StateComponent is null"))
	}
	else
		FinalDamage = BuffComponent->CalculateReceiveDamage(Damage, StateComponent);
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombieBase::BeAttacked : HealthComponent is null"));
		return;
	}
	HealthComponent->BeAttacked(FinalDamage);
}

float AZombieBase::CalculateOutgoingDamage(float Damage)
{
	if (!BuffComponent || !StateComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZomebieBase::CalculateOutgoingDamage : BuffComponent or StateComponent is null"));
		return Damage;
	}
	return BuffComponent->CalculateOutgoingDamage(Damage, StateComponent);
}

void AZombieBase::AddHealth(float Value)
{
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealth : HealthComponent is null"));
		return;
	}
	HealthComponent->AddHealth(Value);
}

void AZombieBase::AddHealthPercent(float Rate)
{
	if (!HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantBase::AddHealthPercent : HealthComponent is null"));
		return;
	}
	HealthComponent->AddHealthPercent(Rate);
}


