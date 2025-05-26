#include "PlantProjectileBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "ZombieBase.h"
#include "PlantBase.h"
#include "ProjectileState.h"
#include "Engine/DataTable.h"
#include "kismet/gameplaystatics.h"
#include "NodeGameMode.h"
#include "BuffComponent.h"
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
	Damage = 0.f;
	ProjectileID = 0;
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
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	if (GameModeBase)
	{
		ANodeGameMode* GameMode = Cast<ANodeGameMode>(GameModeBase);
		if (GameMode)
		{
			UBuffComponent* BuffComponent = GameMode->PlantBuffComponent;
			if (BuffComponent)
				OutDamage = BuffComponent->CalculateOutgoingDamage(Damage);
		}
	}
	Zombie->BeAttacked(OutDamage);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteComponent->SetVisibility(false);
	Destroy();
}

bool APlantProjectileBase::Init()
{
	if (!ProjectileID) return false;
	UDataTable* DataTable = nullptr;
	static ConstructorHelpers::FObjectFinder<UDataTable> TableType(TEXT("/Script/Engine.DataTable'/Game/DataTables/Plant/DT_ProjectileState.DT_ProjectileState'"));
	if (TableType.Succeeded())
	{
		DataTable = TableType.Object;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APlantProjectileBase::Init: Failed to load DataTable for ProjectileState!"));
		return false;
	}
	FName RowName = FName(*FString::Printf(TEXT("Projectile_%d"), ProjectileID));
	static const FString ContextString(TEXT("AProjectileBase::Init"));
	if (DataTable)
	{
		FProjectileState* ProjectileData = DataTable->FindRow<FProjectileState>(RowName, ContextString);
		Damage = ProjectileData->BaseDamage;
		return true;
	}
	return false;
}
