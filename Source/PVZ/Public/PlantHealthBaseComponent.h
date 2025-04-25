// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlantHealthBaseComponent.generated.h"


UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UPlantHealthBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantHealthBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CalculatedMaxHealth;

	UFUNCTION(BlueprintCallable)
	virtual void BeAttacked(float FinalDamage) PURE_VIRTUAL(UPlantHealthBaseComponent::BeAttacked, );

	UFUNCTION(BlueprintCallable)
	virtual void AddHealth(float Value) PURE_VIRTUAL(UPlantHealthBaseComponent::AddHealth, );
};
