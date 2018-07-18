// Fill out your copyright notice in the Description page of Project Settings.

#include "RobotHealthUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void URobotHealthUserWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (this->CurrentHealth != nullptr)
	{
		FText text = FText::AsNumber(CurrentHealth);
		this->CurrentHealth->SetText(text);
	}

	if (this->MaxHealth != nullptr)
	{
		FText text = FText::AsNumber(MaxHealth);
		this->MaxHealth->SetText(text);
	}

	if (this->HealthPro != nullptr)
	{
		this->HealthPro->SetPercent(CurrentHealth / MaxHealth);
	}

}




