// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InventoryProject.h"
#include "GameFramework/PlayerController.h"
#include "Components/Button.h"
#include "PlayerCharacter.h"
#include "Engine/DataTable.h"
#include "NPC_TRADE.generated.h"

USTRUCT(BlueprintType)
struct FItemDetailsNew {
	GENERATED_BODY()

		//Name and item cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Cost;

	//set to default
	FItemDetailsNew() {
		Name.FromString("");
		Cost = 0;
	}
};

USTRUCT(BlueprintType)
struct FdataNew : public FTableRowBase
{
	GENERATED_BODY()
		//Name and item cost
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int cost;

	//set to default
	FdataNew() {
		name.FromString("");
		cost = 0;
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPROJECT_API ANPC_TRADE : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_TRADE(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UInventoryComponent* inventory;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> WidgetTe;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Grabs current item quanity based on index with id and quantity ouputed
	UFUNCTION(BlueprintCallable)
		void FetchShopItemMethodS(const int& Index, int& itemID, int& Quantity);

	//Calculate price
	UFUNCTION(BlueprintCallable)
		int CalculateMethod(const int& cost, const int& Index);
};
