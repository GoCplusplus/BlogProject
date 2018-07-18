// Fill out your copyright notice in the Description page of Project Settings.

#include "CloseEnoughBTDecorator.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIBlogCharacter.h"
#include "AIBlogController.h"
#include "BlogProjectCharacter.h"

bool UCloseEnoughBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory) const
{
	AAIBlogController* AIC = Cast<AAIBlogController>(OwnerComp.GetAIOwner());
	if (AIC != nullptr)
	{
		FVector AILocation = Cast<AAIBlogCharacter>(AIC->GetPawn())->GetActorLocation();
		ABlogProjectCharacter* Player = Cast<ABlogProjectCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()); // ������
		if (Player != nullptr)
		{
			FVector PlayerLocation = Player->GetActorLocation();
			// �������
			float Dis = (PlayerLocation - AILocation).Size();
			//UE_LOG(LogTemp, Warning, TEXT("Dis: %.2f, fDis: %.2f"), Dis, fDis);
			if (Dis < fDis)
			{
				return false; // �㹻�������ƶ���
			}
			else
			{
				return true; // �������������ƶ�
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


