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

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAssert(TEXT("/Game/ThirdPersonCPP/AI/AIBlogBehaviorTree")); // �ҵ��༭���е���Ϊ��
	if (BehaviorTreeAssert.Succeeded())
	{
		BehaviorTree = BehaviorTreeAssert.Object; // �����tree
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
			BehaviorTreeCompo->StartTree(*BehaviorTree); // ������Ϊ��
			//AIC->HeroData = BehaviorTree->BlackboardAsset; // ���úڰ���Դ�������Ժ���ºڰ���Դ��Ա����
			if (AIC->HeroData != nullptr)
			{
				AIC->HeroData->InitializeBlackboard(*BehaviorTree->BlackboardAsset); // ��ʼ��
			}
		}
	}
}

void AAIBlogController::UnPossess()
{
	Super::UnPossess();
	if (BehaviorTreeCompo != nullptr)
	{
		BehaviorTreeCompo->StopTree(EBTStopMode::Safe); // ֹͣ������Ϊ��
	}
}


