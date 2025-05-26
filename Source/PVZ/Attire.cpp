// Fill out your copyright notice in the Description page of Project Settings.


#include "Attire.h"
#include "Engine/DataTable.h"
#include "Components/Button.h"

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

void UAttire::NativeConstruct()
{
        int32 TargetId = 1;
        const FAttireInfo& Info = GetAttireInfoByAttireId(TargetId);
        // 赋值给你的控件
        AttireInfo = Info;

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

}
