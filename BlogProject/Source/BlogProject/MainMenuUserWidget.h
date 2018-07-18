// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* SettingBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameBtn;

	virtual bool Initialize() override;

public:

	UFUNCTION()
	void OnClickedStartGame();

	UFUNCTION()
	void OnClickedSetting();

	UFUNCTION()
	void OnClickedQuitGame();
	
};
