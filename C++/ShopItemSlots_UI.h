// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InventoryProject.h"
#include "GameFramework/PlayerController.h"
#include "Components/Button.h"
#include "PlayerCharacter.h"
#include "NPC_TRADE.h"
#include "ShopItemSlots_UI.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPROJECT_API UShopItemSlots_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	//Delegate money Spent which is called in Shop window
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMoneySpentt, int, ID, int, Quantity);
	//Delegate UpdateDetails which is called in shop Window
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateDetails, FText, Name, int, Cost, int, ItemID);

	UShopItemSlots_UI(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = References)
		APlayerCharacter* m_playerCharacter;

	//Text Blocks
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* ItemName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* ItemCost;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* QuantityText;
	//Buttons
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* Button_55;
	//Item Detail Struct
	UPROPERTY(BlueprintReadWrite) FItemDetailsNew m_ItemDetails;
	//Data table of items
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) class UDataTable* itemDataTableOURS;
	//Item id and Quantity
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) int m_ItemID;
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) int m_Quantity;
	//Trader Object
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) ANPC_TRADE* m_NPCTrader;
	//Delegate Objects
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable) FMoneySpentt isTheSpendMoney;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable) FUpdateDetails callUpdateDetail;

	//Handles button clicked event
	UFUNCTION(BlueprintCallable) void OnClickedFirst();
	//Handles button hovered event
	UFUNCTION(BlueprintCallable) void ButtonIsHovered();

protected:
	virtual void NativeConstruct();
private:
};
