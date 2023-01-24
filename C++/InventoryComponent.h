// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORYPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool m_isPlayer = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<int, int> m_inventoryMap;

	UFUNCTION(BlueprintCallable)
		void GenerateInventoryMethod();

	UFUNCTION(BlueprintCallable)
		void AddToInventoryMethod(const int& ItemId, const int& Quantity);

	UFUNCTION(BlueprintCallable)
		void RemoveFromInventoryMethod(const int& ItemId);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
