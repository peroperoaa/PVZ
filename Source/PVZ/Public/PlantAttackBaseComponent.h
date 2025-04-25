// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlantAttackBaseComponent.generated.h"


UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PVZ_API UPlantAttackBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlantAttackBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FTimerHandle AttackTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CalculatedAttackInterval;

	UFUNCTION(BlueprintCallable)
	virtual void OnTryAttack() PURE_VIRTUAL(UPlantAttackBaseComponent::OnTryAttack,);

	UFUNCTION(BlueprintCallable)
	virtual void Attack() PURE_VIRTUAL(UPlantAttackBaseComponent::OnTryAttack,);
};
