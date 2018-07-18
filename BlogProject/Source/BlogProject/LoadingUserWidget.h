// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API ULoadingUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Level;
	
public:

	void SetLevel(int nIndex); // 0初始化 1第一关

};
