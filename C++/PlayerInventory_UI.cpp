// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory_UI.h"
#define LOCTEXT_NAMESPACE "InventoryPro"

UPlayerInventory_UI::UPlayerInventory_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Loads data table at point of loading
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("WidgetBlueprint'/Game/Inventory/PlayerItemSlot_UI.PlayerItemSlot_UI_C'"));

	//Checks its not null
	if (widget.Class != nullptr)
	{
		//Stores to a variable
		WidgetTemplate = widget.Class;
	}
}

void UPlayerInventory_UI::NativeConstruct()
{
	//casts player character to a local variable
	m_playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Checks for item with player inventory and adds them to the UI grid
	for (int i = 0; i < 7; i++)
	{
		int itemID, quantity;
		FetchItemMethod(i, itemID, quantity);
		yo = CreateWidget<UPlayerItemSlots_UI>(this, WidgetTemplate);
		yo->m_ItemID = itemID;
		yo->m_Quantity = quantity;
		ItemPanel->AddChildToUniformGrid(yo, i / 4, i % 4);
	}

	//Sets gold text
	PlayerMoneyText->SetText(FText::Format(LOCTEXT("ExampleFText", "{ } Gold"), m_playerCharacter->m_money));

	//Binds refresh click to refresh button
	if (!RefreshButto->OnClicked.IsBound())
	{
		RefreshButto->OnClicked.AddDynamic(this, &UPlayerInventory_UI::RefreshOnClick);
	}
	//Binds exit on click to exit button click event
	if (!button_exit->OnClicked.IsBound())
	{
		button_exit->OnClicked.AddDynamic(this, &UPlayerInventory_UI::ExitOnClick);
	}
}

void UPlayerInventory_UI::FetchItemMethod(const int& Index, int& itemID,  int& Quantity)
{
	TArray<int> tem;
	m_playerCharacter->inventory->m_inventoryMap.GenerateKeyArray(tem);

	if (tem.IsValidIndex(Index))
	{
		itemID = tem[Index];
		Quantity = m_playerCharacter->inventory->m_inventoryMap.FindRef(itemID);
	}
	else
	{
		itemID = -1;
		Quantity = 0;
	}
}

void UPlayerInventory_UI::ExitOnClick()
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	controller->SetInputMode(FInputModeGameOnly());
	controller->bShowMouseCursor = false;
	m_playerCharacter->SetActorHiddenInGame(false);
	RemoveFromParent();
}

void UPlayerInventory_UI::RefreshOnClick()
{
	m_playerCharacter->m_isRefresh = true;
}

#undef LOCTEXT_NAMESPACE