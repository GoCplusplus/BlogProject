// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CloseEnoughBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API UCloseEnoughBTDecorator : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = LimitDis)
	float fDis;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory) const override;
	
	
};
