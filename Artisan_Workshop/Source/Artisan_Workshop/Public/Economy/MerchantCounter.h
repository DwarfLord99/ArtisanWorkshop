// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryComponent.h"
#include "MerchantCounter.generated.h"

UCLASS()
class ARTISAN_WORKSHOP_API AMerchantCounter : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMerchantCounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MerchantCounter")
	TObjectPtr<UStaticMeshComponent> MerchantCounterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MerchantCounter")
	TObjectPtr<UInventoryComponent> InventoryComponent;

public:
	void Interact(AActor* Interactor) override;

	void SellItem(FInventorySlot& ItemSlot);

};
