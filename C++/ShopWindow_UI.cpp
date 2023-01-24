// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWindow_UI.h"

#define LOCTEXT_NAMESPACE "InventoryPro"


UShopWindow_UI::UShopWindow_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//loads data table
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("DataTable'/Game/Inventory/Items/DataTable.DataTable'"));
	//checks if load is successful
	if (dataTable.Succeeded())
	{
		//store to variable
		itemDataTable = dataTable.Object;
	}

	//loads widget class
	static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("WidgetBlueprint'/Game/Inventory/PlayerItemSlot_UI.PlayerItemSlot_UI_C'"));
	//check if null
	if (widget.Class != nullptr)
	{
		//stores to variable
		WidgetType = widget.Class;
	}
}

void UShopWindow_UI::NativeConstruct()
{
	//cast player character to local variable
	m_playerCharacterS = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//Updates mode
	UpdateModeMethod();

	//Binds button exits clicked event to reset camera function
	if (!button_exit->OnClicked.IsBound())
	{
		button_exit->OnClicked.AddDynamic(this, &UShopWindow_UI::ResetCamera);
	}

	//Bind mode button to update mode method function
	if (!ModeButton->OnClicked.IsBound())
	{
		ModeButton->OnClicked.AddDynamic(this, &UShopWindow_UI::UpdateModeMethod);
	}

	//Loads shop and player widgets
	for (int i = 0; i < 7; i++)
	{
		createPlayWidget(i);
		createShopWidget(i);
	}

	//Update player wallet
	UpdatePlayerWalletMethod();
}

void UShopWindow_UI::FetchPlayerItemMethod(const int& Index, int& itemID, int& Quantity)
{
	TArray<int> tem;
	//stores and array of keys
	m_playerCharacterS->inventory->m_inventoryMap.GenerateKeyArray(tem);

	//checks if keys are valid
	if (tem.IsValidIndex(Index))
	{
		//Grabs items id and quantity
		itemID = tem[Index];
		Quantity = m_playerCharacterS->inventory->m_inventoryMap.FindRef(itemID);
	}
	else
	{
		itemID = -1;
		Quantity = 0;
	}
}

void UShopWindow_UI::UpdateDetailsMethod(FText Name, int ItemID, int Cost)
{
	//updates item details 
	NameT->SetText(FText::Format(LOCTEXT("ExampleFText", "Name: { }"), Name));
	BuyPriceT->SetText(FText::Format(LOCTEXT("ExampleFText", "Buy Cost: { }"), Cost));
	int t = FGenericPlatformMath::TruncToInt(Cost * 0.8);
	SellPriceT->SetText(FText::Format(LOCTEXT("ExampleFText", "Sell Cost: { }"), t));
}

void UShopWindow_UI::UpdatePlayerWalletMethod()
{
	//Updates players money text
	PlayerMoneyText->SetText(FText::Format(LOCTEXT("ExampleFText", "{ } Gold"), m_playerCharacterS->m_money));
}

void UShopWindow_UI::createShopWidget(const int& index)
{
	int itemID, quantity;
	//Fetchs shop item info
	m_NPCTraderS->FetchShopItemMethodS(index, itemID, quantity);
	//Create widget
	yo = CreateWidget<UShopItemSlots_UI>(this, m_NPCTraderS->WidgetTe);
	//sets item id
	yo->m_ItemID = itemID;
	//sts quanitity
	yo->m_Quantity = quantity;
	//passes reference to the shop keeper
	yo->m_NPCTrader = m_NPCTraderS;
	//Binds the delegates to this classes functions
	yo->isTheSpendMoney.AddDynamic(this, &UShopWindow_UI::BindToDelegate);
	yo->callUpdateDetail.AddDynamic(this, &UShopWindow_UI::UpdateDetailsMethod);
	//add items to grid
	ItemGrid->AddChildToUniformGrid(yo, index / 4, index % 4);
}

void UShopWindow_UI::createPlayWidget(const int& index)
{
	int itemID, quantity;
	//Fetchs player item info
	FetchPlayerItemMethod(index, itemID, quantity);
	//Create widget
	zo = CreateWidget<UPlayerItemSlots_UI>(this, WidgetType);
	//sets item id
	zo->m_ItemID = itemID;
	//sts quanitity
	zo->m_Quantity = quantity;
	//passes reference to the shop keeper
	zo->m_NPCTrader = m_NPCTraderS;
	//Binds the delegates to this classes functions
	zo->isTheRemovedItem.AddDynamic(this, &UShopWindow_UI::refreshPart);
	zo->callUpdateDetail.AddDynamic(this, &UShopWindow_UI::UpdateDetailsMethod);
	//add items to grid
	PlayerInventory->AddChildToUniformGrid(zo, index / 4, index % 4);
}

void UShopWindow_UI::UpdateModeMethod()
{
	//checks current mode and updates what item grid is displayed
	switch (m_CurrentMode)
	{
	case 0:
		Sell->SetText(FText::FromString("Buy"));
		m_CurrentMode = 1;
		break;
	case 1:
		Sell->SetText(FText::FromString("Sell"));
		m_CurrentMode = 0;
		break;
	}
	
	WidgetSwitcher_0->SetActiveWidgetIndex(m_CurrentMode);

	linkedFunction();
}


void UShopWindow_UI::refreshPart(int itemID)
{
	//loads item info from data table
	FName localRow = FName(FString::FromInt(itemID));
	static const FString ContextStr(TEXT("Context"));
	FdataNew* temp = itemDataTable->FindRow<FdataNew>(localRow, "");

	//checks if data table is found
	if (temp)
	{
		//calculates the price based on the quantity of said itaem
		int t = m_NPCTraderS->CalculateMethod(temp->cost, itemID);

		//adds 80% of the items value to player money
		m_playerCharacterS->m_money += FGenericPlatformMath::TruncToInt(t * 0.8);

		//Updates players wallet
		UpdatePlayerWalletMethod();
	}

	linkedFunction();
}

void UShopWindow_UI::ResetCamera()
{
	//Loads a local verison of the player character controller
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//Moves camera back to orgin
	controller->SetViewTargetWithBlend(m_playerCharacterS, 1);
	//Sets input mode to game only
	controller->SetInputMode(FInputModeGameOnly());
	//disable visable cursor
	controller->bShowMouseCursor = false;
	//Make character visable
	m_playerCharacterS->SetActorHiddenInGame(false);
	//Remove the ui from parent
	RemoveFromParent();
}

void UShopWindow_UI::BindToDelegate(int ID, int Quantity)
{
	//Updates players wallert
	UpdatePlayerWalletMethod();
	//add item to shop keepers inventrory
	m_playerCharacterS->inventory->AddToInventoryMethod(ID, Quantity);
	//CLears children of shop item grid
	ItemGrid->ClearChildren();

	//Re-generate item grid
	for (int i = 0; i < 7; i++)
	{
		createShopWidget(i);
	}
}

void UShopWindow_UI::linkedFunction()
{
	//clears grids and re-generates them
	PlayerInventory->ClearChildren();
	ItemGrid->ClearChildren();

	for (int i = 0; i < 7; i++ )
	{
		createPlayWidget(i);
		createShopWidget(i);
	}
}

#undef LOCTEXT_NAMESPACE