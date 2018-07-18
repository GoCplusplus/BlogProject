// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "MainMenuUserWidget.h"

AMainMenuHUD::AMainMenuHUD(const FObjectInitializer& Initailizer)
	: Super(Initailizer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetBP(TEXT("/Game/ThirdPersonCPP/UI/MainMenu")); // �ҵ���ͼ��
	if (MainMenuWidgetBP.Succeeded())
	{
		MainMenuWidgetClass = MainMenuWidgetBP.Class; // �õ�class
	}
}

void AMainMenuHUD::BeginPlay()
{
	if (MainMenuWidgetClass != nullptr)
	{
		UMainMenuUserWidget* Widget = CreateWidget<UMainMenuUserWidget>(GetWorld()->GetGameInstance(), MainMenuWidgetClass);
		if (Widget != nullptr)
		{
			Widget->AddToViewport();
		}
	}
}




