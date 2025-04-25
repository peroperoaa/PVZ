// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PlantBase.generated.h"

class UStateComponent;
class UBuffComponent;
class UPlantHealthBaseComponent;
class UPlantAttackBaseComponent;
class UPaperSpriteComponent;

UCLASS(Abstract)
class PVZ_API APlantBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStateComponent* StateComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBuffComponent* BuffComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlantHealthBaseComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPlantAttackBaseComponent* AttackComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlantID;
};
