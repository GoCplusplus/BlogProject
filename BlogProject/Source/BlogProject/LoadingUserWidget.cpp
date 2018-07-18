// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingUserWidget.h"
#include "Components/TextBlock.h"

void ULoadingUserWidget::SetLevel(int nIndex)
{
	switch (nIndex)
	{
	case 0: // 初始化界面
		if (Level != nullptr)
		{
			FString textStr(TEXT("Initialize"));
			FText text = FText::FromString(textStr);
			Level->SetText(text);
		}
		break;
	case 1:
		if (Level != nullptr)
		{
			FString textStr(TEXT("Level1"));
			FText text = FText::FromString(textStr);
			Level->SetText(text);
		}
		break;
	}
}

