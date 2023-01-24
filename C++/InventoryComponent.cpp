// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	GenerateInventoryMethod();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//fills the inventory map with random amount of items
void UInventoryComponent::GenerateInventoryMethod()
{
	if (!m_isPlayer)
	{
		m_inventoryMap.Empty();
		for (int i = 1; i < 4; i++)
		{
			m_inventoryMap.Add(i, FMath::RandRange(1, 30));
		}
	}
}

//Takes in item id and quantity and adds to current item map
void UInventoryComponent::AddToInventoryMethod(const int& ItemId, const int& Quantity)
{
	//Store item quantity
	int32 t = m_inventoryMap.FindRef(ItemId);
	//Checks if there is any current items with the same id  and adds either current amount or starts a new amount
	if (t > 0)
	{
		m_inventoryMap.Add(ItemId, t + Quantity);
	}
	else
	{
		m_inventoryMap.Add(ItemId, t + Quantity);
	}
}

//Removes 1 item from current map based on inputed Item Id
void UInventoryComponent::RemoveFromInventoryMethod(const int& ItemId)
{
	//stores current quantity of item id
	int32 t = m_inventoryMap.FindRef(ItemId);

	//Chhecks if any are in the map
	if (t > 0)
	{
		//if removing 1 means there is a negitive then remove item from map
		if ((t - 1) <= 0)
		{
			m_inventoryMap.Remove(ItemId);
		}
		else
		{
			//Update quantity with -1
			m_inventoryMap.Add(ItemId, t - 1);
		}
	}
}

