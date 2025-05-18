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
	AttackingPlant = nullptr;
	UCapsuleComponent* SelfCapsuleComponent = GetCapsuleComponent();
	if (SelfCapsuleComponent)
	{
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AZombie::OnBeginOverlap);
	}
}

void AZombie::Dead()
{
	bIsDead = true;
	Destroy();
}

void AZombie::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	Move(true);
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
		AttackingPlant = Plant;
		// 添加植物销毁事件监听
		Plant->OnDestroyed.AddDynamic(this, &AZombie::OnAttackingPlantDestroyed);
	}
	//else
	//{
	//	bIsNeedAttack = false;
	//	Move(true);
	//	GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	//}
}

void AZombie::OnAttackingPlantDestroyed(AActor* DestroyedActor)
{
	if (AttackingPlant == DestroyedActor)
	{
		bIsNeedAttack = false;
		Move(true);
		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
		AttackingPlant = nullptr;
	}
}