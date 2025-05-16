// Fill out your copyright notice in the Description page of Project Settings.


#include "Peashooter.h"

APeashooter::APeashooter()
{
	PrimaryActorTick.bCanEverTick = true;
	PlantID = 1;
	AttackInterval = 0.f;
	Init();
}
void APeashooter::Dead()
{
	Destroy();
}
void APeashooter::BeginPlay()
{
	Super::BeginPlay();
	AttackInterval = GetCurrentAttackInterval();
	if (AttackInterval < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("APeashooter::BeginPlay : AttackInterval is error"));
		return;
	}
	if (AttackInterval > 0)
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &APeashooter::OnTryAttack, AttackInterval, true);
	else
		OnTryAttack();
}

void APeashooter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}
