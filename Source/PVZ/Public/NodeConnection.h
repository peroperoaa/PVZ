// NodeConnection.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "NodeConnection.generated.h"

UCLASS()
class PVZ_API ANodeConnection : public AActor
{
	GENERATED_BODY()
    
public:    
	ANodeConnection();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Connection")
	USplineComponent* SplineComponent;
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Connection")
	TArray<USplineMeshComponent*> SplineMeshes;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
	UStaticMesh* ConnectionMesh;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
	UMaterialInterface* ConnectionMaterial;
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Connection")
	UMaterialInterface* ActiveConnectionMaterial;

	UFUNCTION(BlueprintCallable, Category = "Connection")
	void SetupConnection(FVector StartPoint, FVector EndPoint);

	UFUNCTION(BlueprintCallable, Category = "Connection")
	void SetActive(bool bActive);
};