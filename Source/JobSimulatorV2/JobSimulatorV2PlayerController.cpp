// Copyright Epic Games, Inc. All Rights Reserved.


#include "JobSimulatorV2PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "JobSimulatorV2CameraManager.h"

AJobSimulatorV2PlayerController::AJobSimulatorV2PlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AJobSimulatorV2CameraManager::StaticClass();
}

void AJobSimulatorV2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
