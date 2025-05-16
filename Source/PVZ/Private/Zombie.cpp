// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie.h"
#include "PlantBase.h"

AZombie::AZombie()
{
	PrimaryActorTick.bCanEverTick = true;
	ZombieID = 1;
	Init();
	bIsNeedAttack = false;
	bIsDead = false;
	AttackInterval = .5f;
	UCapsuleComponent* SelfCapsuleComponent = GetCapsuleComponent();
	if (SelfCapsuleComponent)
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AZombie::OnBeginOverlap);
		GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AZombie::OnEndOverlap);
	}
}

void AZombie::Dead()
{
	bIsDead = true;
}

void AZombie::BeginPlay()
{
	Super::BeginPlay();
	Move(true);
}

void AZombie::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlantBase* Plant = Cast<APlantBase>(OtherActor);
	if (Plant)
	{
		bIsNeedAttack = true;
		Move(false);
		GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &AZombie::OnTryAttack, AttackInterval, true);
	}
	//else
	//{
	//	bIsNeedAttack = false;
	//	Move(true);
	//	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	//}
}

void AZombie::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsNeedAttack = false;
	Move(true);
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}

