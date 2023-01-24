// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_TRADE.h"

// Sets default values
ANPC_TRADE::ANPC_TRADE(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates object
	inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	////static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("WidgetBlueprint'/Game/Inventory/ShopItemSlot_UI.ShopItemSlot_UI_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> wid(TEXT("/Game/Inventory/ShopItemSlot_UI"));
	if (wid.Succeeded())
	{
		WidgetTe = wid.Class;
	}
}

// Called when the game starts or when spawned
void ANPC_TRADE::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_TRADE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC_TRADE::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC_TRADE::FetchShopItemMethodS(const int& Index, int& itemID, int& Quantity)
{
	//Creates local variable
	TArray<int> tem;
	//Generate array of keys
	inventory->m_inventoryMap.GenerateKeyArray(tem);
	//checks if index is viable if so return data
	if (tem.IsValidIndex(Index))
	{
		itemID = tem[Index];
		Quantity = inventory->m_inventoryMap.FindRef(itemID);
	}
	else //Return data which states nothing was found
	{
		itemID = -1;
		Quantity = 0;
	}
}

int ANPC_TRADE::CalculateMethod(const int& cost, const int& Index)
{
	//Creates local varables
	int ItemID, Quantity;
	//Finds item id and quantity
	FetchShopItemMethodS((Index - 1), ItemID, Quantity);

	//Calculate prices
	int output = cost + ((10 - Quantity) * FGenericPlatformMath::TruncToInt(cost * 0.1));

	//checks to make sure number is not 0 or negitive 
	if (ItemID > 0)
	{
		//If negitive then set as 1
		if (output < 0)
		{
			return 1;
		}
		else
		{
			//if zero then return 1
			if (output == 0)
			{
				return 1;
			}
			//otherwise retutn calculated value
			else
			{
				return output;
			}
		}
	}
	else
	{
		return cost;
	}
}
