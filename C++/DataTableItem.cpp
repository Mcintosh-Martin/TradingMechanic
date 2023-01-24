// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableItem.h"

void UDataTableItem::setAr()
{

	for (int i = 0; i < 3; i++)
	{
		name.Emplace(new FItemData);
	}
	name[0]->Cost = 5;

	temp->StaticStruct();
	temp->ID = 1;
	temp->Name.FromString("Apple");
	temp->Cost = 30;
	name.Emplace(temp);

	temp->ID = 2;
	temp->Name.FromString("Banana");
	temp->Cost = 25;
	name.Emplace(temp);

	temp->ID = 3;
	temp->Name.FromString("Pear");
	temp->Cost = 35;
	name.Emplace(temp);
}

void UDataTableItem::findArr()
{
	setAr();

	for (auto& Data : name)
	{
		if (Data->ID == 1)
		{
			Data->Cost = 4;
		}
	}
}
