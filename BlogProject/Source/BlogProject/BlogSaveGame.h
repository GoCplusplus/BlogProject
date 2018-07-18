// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BlogSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API UBlogSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere) // 记住 这里必须是UPROPERTY
	FVector LastLocation;
	
	
	
};
