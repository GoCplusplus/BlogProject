// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBlogController.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIBlogCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

AAIBlogController::AAIBlogController()
{
	BehaviorTreeCompo = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackBoardCompo = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBorad"));

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/ThirdPersonCPP/AI/AIBlogBehaviorTree")); // 找到编辑器中的行为树
	if (BehaviorTreeAssert.Succeeded())
	{
		BehaviorTree = BehaviorTreeAssert.Object; // 分配给tree
	}
}

void AAIBlogController::Possess(APawn* InPawn)
{
	AAIBlogCharacter* AIC = Cast<AAIBlogCharacter>(InPawn);
	if (AIC == nullptr)
	{
		return;
	}

	Super::Possess(InPawn);
	
	if (BehaviorTreeCompo != nullptr)
	{
		if (BehaviorTree != nullptr)
		{
			if (BlackBoardCompo != nullptr)
			{
				BlackBoardCompo->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
			}
			BehaviorTreeCompo->StartTree(*BehaviorTree); // 运行行为树
			//AIC->HeroData = BehaviorTree->BlackboardAsset; // 设置黑板资源，方便以后更新黑板资源成员数据
			if (AIC->HeroData != nullptr)
			{
				AIC->HeroData->InitializeBlackboard(*BehaviorTree->BlackboardAsset); // 初始化
			}
		}
	}
}

void AAIBlogController::UnPossess()
{
	Super::UnPossess();
	if (BehaviorTreeCompo != nullptr)
	{
		BehaviorTreeCompo->StopTree(EBTStopMode::Safe); // 停止运行行为树
	}
}


