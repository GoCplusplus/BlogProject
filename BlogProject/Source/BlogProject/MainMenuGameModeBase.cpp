// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameModeBase.h"
#include "MainMenuHUD.h"
#include "MainMenuPlayerController.h"
#include "Sound/SoundCue.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	HUDClass = AMainMenuHUD::StaticClass();
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();

	static ConstructorHelpers::FObjectFinder<USoundCue> SoundCueAssert(TEXT("/Game/ThirdPersonCPP/Sound/mainmenu_Cue"));
	if (SoundCueAssert.Succeeded())
	{
		Sound = SoundCueAssert.Object;
	}

}

void AMainMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	if (Sound != nullptr) // ≤•∑≈“Ù¿÷
	{
		UGameplayStatics::PlaySound2D(this, Sound);
	}
}

