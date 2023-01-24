// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataTableItem.generated.h"

USTRUCT(BlueprintType)
struct FItemData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int ID;

	FItemData() {
		ID = 0;
		Name.FromString("");
		Cost = 0;
	}
};

UCLASS()
class INVENTORYPROJECT_API UDataTableItem : public UObject
{
	GENERATED_BODY()
	
public:
		UFUNCTION(BlueprintCallable)
		void setAr();

		UFUNCTION(BlueprintCallable)
			void findArr();


private:

	TArray<FItemData*> name;
	FItemData* temp;
};
