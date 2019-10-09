// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "O5_TestingGroundsGameMode.h"
#include "O5_TestingGroundsHUD.h"
#include "O5_TestingGroundsCharacter.h"
#include "UObject/ConstructorHelpers.h"

AO5_TestingGroundsGameMode::AO5_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AO5_TestingGroundsHUD::StaticClass();
}
