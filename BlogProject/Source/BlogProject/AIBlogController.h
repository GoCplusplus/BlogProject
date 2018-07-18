// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBlogController.generated.h"

/**
 * 
 */
UCLASS()
class BLOGPROJECT_API AAIBlogController : public AAIController
{
	GENERATED_BODY()

	class UBehaviorTreeComponent* BehaviorTreeCompo;
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackBoardCompo;
	
public:
	AAIBlogController();

protected:
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeCompo() { return BehaviorTreeCompo; }
	FORCEINLINE UBlackboardComponent* GetBlackBoardCompo() { return BlackBoardCompo; }
};
