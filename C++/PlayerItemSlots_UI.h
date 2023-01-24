// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPC_TRADE.h"
#include "PlayerItemSlots_UI.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPROJECT_API UPlayerItemSlots_UI : public UUserWidget
{
	//Delegates for checking if item is removed and to pass details of item to shopwindow
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FisTheItemRemoved, int, itemID);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FUpdateDetails, FText, Name, int, Cost, int, ItemID);
	GENERATED_BODY()
public:
	UPlayerItemSlots_UI(const FObjectInitializer& ObjectInitializer);

	//Text blocks
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* ItemName;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* QuantityText;
	//Buttons
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* Button_55;
	//Item details
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) int m_Quantity;
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) int m_ItemID;
	//Reference to the npc shop keeper
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) ANPC_TRADE* m_NPCTrader;
	//Store item data table
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) class UDataTable* itemDataTablePlayer;
	//Item details structure
	UPROPERTY(BlueprintReadWrite) FItemDetailsNew m_ItemDetails;
	//Delegates objects
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable) FisTheItemRemoved isTheRemovedItem;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable) FUpdateDetails callUpdateDetail;
	
	//Add and remove function for items
	UFUNCTION(BlueprintCallable) void AddRemove();

	//for Broadcasting item details to shop window
	UFUNCTION(BlueprintCallable) void ItemOnHovered();
protected:
	virtual void NativeConstruct();
private:
};
