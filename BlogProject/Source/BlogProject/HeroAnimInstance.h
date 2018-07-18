// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadOnly)
	float Speed; // �ƶ��ٶ�

	UPROPERTY(BlueprintReadOnly)
	float Direction; // ����(-180~180)

	UPROPERTY(BlueprintReadOnly)
	bool bInAir; // �Ƿ��ڿ���
	
	UFUNCTION(BlueprintCallable)
	void UpdateAnimInfo(float dt);

};
