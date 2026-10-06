// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryComponent.h"
#include "StorageCrate.generated.h"

UCLASS()
class ARTISAN_WORKSHOP_API AStorageCrate : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorageCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Storage")
	UStaticMeshComponent* CrateMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Storage")
	TObjectPtr<UInventoryComponent> StorageInventoryComponent;

public:	
	virtual void Interact(AActor* Interactor) override;

	FText GetInteractionPrompt_Implementation() const override;
};
