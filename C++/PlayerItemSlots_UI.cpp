// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerItemSlots_UI.h"

UPlayerItemSlots_UI::UPlayerItemSlots_UI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Loads datatable at loading time
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable(TEXT("DataTable'/Game/Inventory/Items/DataTable.DataTable'"));
	//if successful then bind to variable
	if (dataTable.Succeeded())
	{
		itemDataTablePlayer = dataTable.Object;
	}
}

void UPlayerItemSlots_UI::NativeConstruct()
{
	if (m_ItemID >= 0)
	{
		//checks if item is found in data table
		FName localRow = FName(FString::FromInt(m_ItemID));
		static const FString ContextStr(TEXT("Context"));
		FdataNew* temp = itemDataTablePlayer->FindRow<FdataNew>(localRow, "");

		//checks if datable is found
		if (temp)
		{
			//if player has npc reference
			if (m_NPCTrader)
			{
				//set name and run calculation method
				m_ItemDetails.Name = temp->name;
				m_ItemDetails.Cost = m_NPCTrader->CalculateMethod(temp->cost, m_ItemID);
			}
			//If no reference then use default value
			else
			{
				m_ItemDetails.Name = temp->name;
				m_ItemDetails.Cost = temp->cost;
			}

		}
		//sets text with name and quantity
		ItemName->SetText(m_ItemDetails.Name);
		QuantityText->SetText(FText::AsNumber(m_Quantity));
	}
	else
	{
		//Clears text and hides from UIU
		FText blank;
		ItemName->SetText(blank);
		QuantityText->SetText(blank);

		Button_55->SetVisibility(ESlateVisibility::Hidden);
	}

	//Binds hover event to itemOnHovered
	if (!Button_55->OnHovered.IsBound())
	{
		Button_55->OnHovered.AddDynamic(this, &UPlayerItemSlots_UI::ItemOnHovered);
	}
	//binds addRemove to button click event
	if (!Button_55->OnClicked.IsBound())
	{
		Button_55->OnClicked.AddDynamic(this, &UPlayerItemSlots_UI::AddRemove);
	}
}

void UPlayerItemSlots_UI::AddRemove()
{
	//checks if player has access to npc shop keeper
	if (m_NPCTrader)
	{
		//cast player character to local variable
		APlayerCharacter* m_playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		//Removes item from players inventory
		m_playerCharacter->inventory->RemoveFromInventoryMethod(m_ItemID);

		//Adds item to npcs inventory
		m_NPCTrader->inventory->AddToInventoryMethod(m_ItemID, 1);
		//brodacast to shopWindow
		isTheRemovedItem.Broadcast(m_ItemID);
	}
}

void UPlayerItemSlots_UI::ItemOnHovered()
{
	//Broadcast to the shop window UI
	callUpdateDetail.Broadcast(m_ItemDetails.Name, m_ItemID, m_ItemDetails.Cost);
}



