// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuUserWidget.h"
#include "Components/Button.h"
#include "BlogGameInstance.h"

bool UMainMenuUserWidget::Initialize()
{
	Super::Initialize();
	if (StartGameBtn != nullptr)
	{
		StartGameBtn->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickedStartGame);
	}
	if (SettingBtn != nullptr)
	{
		SettingBtn->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickedSetting);
	}
	if (QuitGameBtn != nullptr)
	{
		QuitGameBtn->OnClicked.AddDynamic(this, &UMainMenuUserWidget::OnClickedQuitGame);
	}

	return true;
}

void UMainMenuUserWidget::OnClickedStartGame()
{
	FString NewMap = FString::Printf(TEXT("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
	UBlogGameInstance* BG = Cast<UBlogGameInstance>(GetWorld()->GetGameInstance());
	if (BG != nullptr)
	{
		BG->CurrentLevel = NowLevel::LEVELONE;
	}
	GetWorld()->ServerTravel(NewMap);
}

void UMainMenuUserWidget::OnClickedSetting()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClicked Setting"));
}

void UMainMenuUserWidget::OnClickedQuitGame()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC != nullptr)
	{
		PC->ConsoleCommand(TEXT("quit"));
	}
}