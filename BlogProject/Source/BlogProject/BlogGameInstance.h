// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlogGameInstance.generated.h"

UENUM()
namespace NowLevel
{
	enum type
	{
		INITIAL, // ��ʼ������
		LEVELONE, // ��һ���ؿ�
	};
}

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API UBlogGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	FVector HeroLocation;

	TSubclassOf<class UUserWidget> LoadingWidget;

public:
	class UBlogSaveGame* SaveGame;

public:
	bool bLoadGame; // �Ƿ��Ƕ�ȡ�ļ�����

	NowLevel::type CurrentLevel;

public:

	UBlogGameInstance();

	virtual void Init() override;

	const FVector& GetHeroLocation() const { return HeroLocation; }

	void SetHeroLocation(const FVector& Location) { HeroLocation = Location; }

	FORCEINLINE class UBlogSaveGame* GetSaveGame() { return SaveGame; }

private:

	UFUNCTION()
	void BeginLoadingScreen(const FString& MapName);

	UFUNCTION()
	void EndLoadingScreen(UWorld* InLoadedWorld);

};
