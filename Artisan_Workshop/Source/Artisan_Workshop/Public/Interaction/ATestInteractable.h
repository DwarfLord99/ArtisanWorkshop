// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/Interactable.h"
#include "ATestInteractable.generated.h"

UCLASS()
class ARTISAN_WORKSHOP_API AATestInteractable : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATestInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Implement the Interact function from the IInteractable interface
	virtual void Interact() override;
};
