// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BlogProjectGameMode.h"
#include "BlogProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABlogProjectGameMode::ABlogProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/NewBlogProjectCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
