// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "Components/UniformGridPanel.h"
#include "PlayerItemSlots_UI.h"
#include "ShopItemSlots_UI.h"
#include "ShopWindow_UI.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPROJECT_API UShopWindow_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	UShopWindow_UI(const FObjectInitializer& ObjectInitializer);

	//Grid switcher
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UWidgetSwitcher* WidgetSwitcher_0;
	//Text blocks
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* NameT;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* SellPriceT;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* BuyPriceT;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* PlayerMoneyText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UTextBlock* Sell;
	//Current buy/sell mode
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) int m_CurrentMode = 1;
	//Reference to npc shopkeeper
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true)) ANPC_TRADE* m_NPCTraderS;
	//Player and shopkeeper inventory grid
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUniformGridPanel* ItemGrid;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UUniformGridPanel* PlayerInventory;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly) class UDataTable* itemDataTable;
	//Buttons
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* button_exit;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* ModeButton;
	
	//Reference to player and shop item slots UI
	UPROPERTY(BlueprintReadWrite) UShopItemSlots_UI* ShopItemSlotsRef;
	UPROPERTY(BlueprintReadWrite) UPlayerItemSlots_UI* playerItemSlotRef;

	//Player character class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = References) APlayerCharacter* m_playerCharacterS;

	UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> WidgetType;

	UPROPERTY(EditDefaultsOnly) class UPlayerItemSlots_UI* zo;

	UPROPERTY(EditDefaultsOnly) class UShopItemSlots_UI* yo;

	//Fetches item from players inventory
	UFUNCTION(BlueprintCallable) void FetchPlayerItemMethod(const int& Index, int& itemID, int& Quantity);
	
	//set text blocks info
	UFUNCTION(BlueprintCallable) void UpdateDetailsMethod(FText Name, int Cost, int ItemID);

	//Updates player wallet after a purchese
	UFUNCTION(BlueprintCallable) void UpdatePlayerWalletMethod();

	//Creates Shop item grid
	UFUNCTION(BlueprintCallable) void createShopWidget(const int& index);

	//Creates player item grid
	UFUNCTION(BlueprintCallable) void createPlayWidget(const int& index);

	//Updates buy/sell mode
	UFUNCTION(BlueprintCallable) void UpdateModeMethod();

	//Refreshes currently displyed info
	UFUNCTION(BlueprintCallable) void refreshPart(int itemID);

	//Resets camera when shop is exited
	UFUNCTION(BlueprintCallable) void ResetCamera();

	//adds item to players inventory
	UFUNCTION(BlueprintCallable) void BindToDelegate(int ID, int Quantity);

	//Clears screen and reloads item grids
	UFUNCTION(BlueprintCallable) void linkedFunction();

protected:
	virtual void NativeConstruct();
private:
};
