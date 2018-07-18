// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveBTTaskNode.h"
#include "AIBlogController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIBlogCharacter.h"

EBTNodeResult::Type UMoveBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIBlogController* AIC = Cast<AAIBlogController>(OwnerComp.GetAIOwner()); // 获得行为树的所属control
	if (AIC != nullptr)
	{
		//FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TargetLocation")); // 获得黑板上的数据
		FVector TargetLocation;
		UBlackboardComponent* BlackCompo = OwnerComp.GetBlackboardComponent();
		if (BlackCompo != nullptr)
		{
			TargetLocation = BlackCompo->GetValueAsVector(TEXT("TargetLocation"));
		}

		AAIBlogCharacter* AI = Cast<AAIBlogCharacter>(AIC->GetPawn()); // 获取所控制的AI
		if (AI != nullptr && AI->bSeen) // 让AI移动到targetlocation
		{
			AIC->MoveToLocation(TargetLocation);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed; // 失败
	}
}


