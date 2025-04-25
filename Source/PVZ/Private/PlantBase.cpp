// Fill out your copyright notice in the Description page of Project Settings.


#include "PlantBase.h"

// Sets default values
APlantBase::APlantBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StateComponent = nullptr;
	BuffComponent = nullptr;
	HealthComponent = nullptr;
	AttackComponent = nullptr;
	SpriteComponent = nullptr;
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

