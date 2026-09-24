// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/ATestInteractable.h"

// Sets default values
AATestInteractable::AATestInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AATestInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Implement the Interact function from the IInteractable interface
void AATestInteractable::Interact(AActor* Interactor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacted with ATestInteractable!"));
	}
}
