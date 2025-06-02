// Fill out your copyright notice in the Description page of Project Settings.


#include "Attire.h"
#include "Engine/DataTable.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "CollectionInterface.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h" // Include the correct header for GetAllWidgetsOfClass


const FAttireInfo& UAttire::GetAttireInfoByAttireId(int32 InAttireId) const
{
        if (!AttireInfoTable) {
                static FAttireInfo DefaultInfo;
                DefaultInfo.AttireName = TEXT("Default");
		DefaultInfo.AttireIntroduction = TEXT("No data available");
                return DefaultInfo;
        }
        // 遍历数据表所有行
        TArray<FAttireInfo*> AllRows;
        AttireInfoTable->GetAllRows<FAttireInfo>(TEXT("AttireInfoLookup"), AllRows);

        for (FAttireInfo* Row : AllRows)
        {
                if (Row && Row->AttireId == InAttireId)
                {
                        return *Row;
                }
        }
        static FAttireInfo DefaultInfo;
        DefaultInfo.AttireIntroduction = TEXT("No data available");
        DefaultInfo.AttireName = TEXT("Default");
        return DefaultInfo;
}

void UAttire::InitAttire(int32 InAttireId)
{
        AttireInfo.AttireId = InAttireId;
        const FAttireInfo& Info = GetAttireInfoByAttireId(AttireInfo.AttireId);
        // 赋值给你的控件
        AttireInfo = Info;
}

void UAttire::NativeConstruct()
{
}

bool UAttire::Initialize()
{
        if (!Super::Initialize()) {
                return false;
        }
        if (Button) {
                Button->OnClicked.AddDynamic(this, &UAttire::ButtonClicked);
        }
        return true;
}



void UAttire::ButtonClicked()
{
        // 查找所有UI_CollectionInterface类型的Widget
        /*if (GEngine)
        {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("AttireId: %d, Name: %s"), AttireInfo.AttireId, *AttireInfo.AttireName));
        }*/
        TArray<UUserWidget*> FoundWidgets;
        UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UCollectionInterface::StaticClass(), false);

        if (FoundWidgets.Num() > 0)
        {
                UCollectionInterface* CollectionWidget = Cast<UCollectionInterface>(FoundWidgets.Last());
                if (CollectionWidget)
                {
                        CollectionWidget->SetDisplayInfo(AttireInfo);
                }
        }
}
