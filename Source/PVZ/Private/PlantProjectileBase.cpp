#include "PlantProjectileBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "ZombieBase.h"
#include "PlantBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.



// Sets default values
APlantProjectileBase::APlantProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	RootComponent = BoxComponent;
	SpriteComponent->SetupAttachment(BoxComponent);
	Damage = 20.f;//测试用
}

// Called when the game starts or when spawned
void APlantProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlantProjectileBase::BeginOverlap);
}

// Called every frame
void APlantProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlantProjectileBase::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombieBase* Zombie = Cast<AZombieBase>(OtherActor);
	if (!Zombie)
		return;
	float OutDamage = Damage;
	AActor* Parent = GetOwner();
	if (Parent)
	{
		APlantBase* Plant = Cast<APlantBase>(Parent);
		if (Plant)
			OutDamage = Plant->CalculateOutgoingDamage(Damage);
	}
	Zombie->BeAttacked(OutDamage);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteComponent->SetVisibility(false);
	Destroy();
}
//待优化
void APlantProjectileBase::Init(float InDamage, AActor* InOwner)
{
	Damage = InDamage;
	SetOwner(InOwner);
}