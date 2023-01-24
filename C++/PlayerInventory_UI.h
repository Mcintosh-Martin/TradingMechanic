// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWindow_UI.h"
#include "GameFramework/PlayerController.h"
#include "PlayerItemSlots_UI.h"
#include "Components/UniformGridPanel.h"
#include "PlayerInventory_UI.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPROJECT_API UPlayerInventory_UI : public UUserWidget
{
	//
	GENERATED_BODY()
	
public:
	UPlayerInventory_UI(const FObjectInitializer& ObjectInitializer);

	//Text block
	UPROPERTY(meta = (BindWidget)) UTextBlock* PlayerMoneyText;
	//Player Object
	UPROPERTY(EditAnywhere, Category = References) APlayerCharacter* m_playerCharacter;
	//Item Panel
	UPROPERTY(meta = (BindWidget)) UUniformGridPanel* ItemPanel;
	//Buttons
	UPROPERTY(meta = (BindWidget)) UButton* RefreshButto;
	UPROPERTY(meta = (BindWidget)) UButton* button_exit;
	//Subclass of userWidget
	UPROPERTY(EditDefaultsOnly) TSubclassOf<UUserWidget> WidgetTemplate;
	
	UPROPERTY(EditDefaultsOnly) class UPlayerItemSlots_UI* yo;

	//Fetchs item from player item grid
	UFUNCTION() void FetchItemMethod(const int& Index,  int& itemID,  int& Quantity);

	//Button click event
	UFUNCTION() void ExitOnClick();

	//Referesh event
	UFUNCTION() void RefreshOnClick();

protected:
	virtual void NativeConstruct();
private:
};
