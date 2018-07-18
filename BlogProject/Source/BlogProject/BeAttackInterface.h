// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBeAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLOGPROJECT_API IBeAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void BeAttacked(float fDamage) = 0;
	
};
