// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopItemSlots_UI.h"
#define LOCTEXT_NAMESPACE "InventoryPro"

UShopItemSlots_UI::UShopItemSlots_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Loads datatable at point of load
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("DataTable'/Game/Inventory/Items/DataTable.DataTable'"));
	//Checks if datatable was found
	if (dataTable.Succeeded())
	{
		//Store data table
		itemDataTableOURS = dataTable.Object;
	}

	//Sets values to default
	m_ItemID = 0;
	m_NPCTrader = NULL;
	m_Quantity = 0;
}

void UShopItemSlots_UI::NativeConstruct()
{
	if (m_ItemID >= 0)
	{
		//search datatable for the item based on the index
		FName localRow = FName(FString::FromInt(m_ItemID));
		static const FString ContextStr(TEXT("Context"));
		//If found the store local variable
		FdataNew* temp = itemDataTableOURS->FindRow<FdataNew>(localRow, "");

		if (temp)
		{
			//Stores name and calculates price
			m_ItemDetails.Name = temp->name;
			m_ItemDetails.Cost = m_NPCTrader->CalculateMethod(temp->cost, m_ItemID);

			//Sets text for both name, cost and quantity
			ItemName->SetText(m_ItemDetails.Name);
			ItemCost->SetText(FText::Format(LOCTEXT("ExampleFText", "{ } Gold"), m_ItemDetails.Cost));
			QuantityText->SetText(FText::AsNumber(m_Quantity));
		}
	}
	else
	{
		//Clears text and hides from view
		FText blank;
		ItemName->SetText(blank);
		ItemCost->SetText(blank);
		QuantityText->SetText(blank);

		Button_55->SetVisibility(ESlateVisibility::Hidden);
	}

	//Binds buttonIsHovered to the buttons hover event
	if (!Button_55->OnHovered.IsBound())
	{
		Button_55->OnHovered.AddDynamic(this, &UShopItemSlots_UI::ButtonIsHovered);
	}
	//Binds onClickedFirst to the buttons click event
	if (!Button_55->OnClicked.IsBound())
	{
		Button_55->OnClicked.AddDynamic(this, &UShopItemSlots_UI::OnClickedFirst);
	}
}

void UShopItemSlots_UI::OnClickedFirst()
{
	//Retrieves player character and casts it to APlayerCharacter object
	m_playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	//Checks if the cost of the items is less than the player gold
	if (m_playerCharacter->m_money >= m_ItemDetails.Cost)
	{
		//Passes value of item to the character
		m_playerCharacter->SpendMoneyMethod(m_ItemDetails.Cost);
	}
	//Removes item from shops inventory
	m_NPCTrader->inventory->RemoveFromInventoryMethod(m_ItemID);
	//Broadcast to shopwindow
	isTheSpendMoney.Broadcast(m_ItemID, 1);
}

void UShopItemSlots_UI::ButtonIsHovered()
{
	//Broadcasts delegate which the shopwindow will listen to
	callUpdateDetail.Broadcast(m_ItemDetails.Name, m_ItemID, m_ItemDetails.Cost);
}

#undef LOCTEXT_NAMESPACEw