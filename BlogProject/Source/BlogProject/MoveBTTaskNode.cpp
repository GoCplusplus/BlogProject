// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveBTTaskNode.h"
#include "AIBlogController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIBlogCharacter.h"

EBTNodeResult::Type UMoveBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIBlogController* AIC = Cast<AAIBlogController>(OwnerComp.GetAIOwner()); // �����Ϊ��������control
	if (AIC != nullptr)
	{
		//FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TargetLocation")); // ��úڰ��ϵ�����
		FVector TargetLocation;
		UBlackboardComponent* BlackCompo = OwnerComp.GetBlackboardComponent();
		if (BlackCompo != nullptr)
		{
			TargetLocation = BlackCompo->GetValueAsVector(TEXT("TargetLocation"));
		}

		AAIBlogCharacter* AI = Cast<AAIBlogCharacter>(AIC->GetPawn()); // ��ȡ�����Ƶ�AI
		if (AI != nullptr && AI->bSeen) // ��AI�ƶ���targetlocation
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
		return EBTNodeResult::Failed; // ʧ��
	}
}


