// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AWorkshopCharacter.h"

// Sets default values
AAWorkshopCharacter::AAWorkshopCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAWorkshopCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add the mapping context
			Subsystem->AddMappingContext(FirstPersonContext, 0);
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("We are using Workshop Character."));
}

// Called every frame
void AAWorkshopCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAWorkshopCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Setup action bindings
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAWorkshopCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAWorkshopCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAWorkshopCharacter::Interact);
	}

}

void AAWorkshopCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add movement 
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementVector.X);

		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementVector.Y);

		// Add debug message to the screen
		if (GEngine)
		{
			FString DebugMessage = FString::Printf(TEXT("Movement Input: X=%f, Y=%f"), MovementVector.X, MovementVector.Y);
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, DebugMessage);
		}
	}
}

void AAWorkshopCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
		// Add debug message to the screen
		if (GEngine)
		{
			FString DebugMessage = FString::Printf(TEXT("Look Input: X=%f, Y=%f"), LookAxisVector.X, LookAxisVector.Y);
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Blue, DebugMessage);
		}
	}
}

void AAWorkshopCharacter::Interact(const FInputActionValue& Value)
{
	// Handle interaction input here
	// For example, you can call a function to interact with objects in the game world
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Interact action triggered."));
	}
}

