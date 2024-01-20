// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptReiderGameMode.h"
#include "CryptReiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptReiderGameMode::ACryptReiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
