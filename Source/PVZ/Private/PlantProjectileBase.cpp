#include "PlantProjectileBase.h"
// Fill out your copyright notice in the Description page of Project Settings.



// Sets default values
APlantProjectileBase::APlantProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	RootComponent = SpriteComponent;
	BoxComponent->SetupAttachment(SpriteComponent);
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
	//ZombieBase* Zombie = Cast<ZombieBase>(OtherActor);
	//if (!Zombie)
	//	return;
	UE_LOG(LogTemp, Warning, TEXT("APlantProjectileBase::BeginOverlap: 造成伤害逻辑"));
}

void APlantProjectileBase::Init(float InDamage, AActor* InOwner)
{
	Damage = InDamage;
	SetOwner(InOwner);
}