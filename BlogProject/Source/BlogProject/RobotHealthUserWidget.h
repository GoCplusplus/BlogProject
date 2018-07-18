// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RobotHealthUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API URobotHealthUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealth;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealth;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthPro;
	
public:
	void UpdateHealth(float CurrentHealth, float MaxHealth);
	
};
