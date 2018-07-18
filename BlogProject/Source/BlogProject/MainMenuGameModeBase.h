// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMainMenuGameModeBase();

	virtual void BeginPlay() override;

private:
	class USoundCue* Sound;
	
};
