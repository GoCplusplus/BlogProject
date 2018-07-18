// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroAnimInstance.h"
#include "GameFrameWork/Pawn.h"
#include "GameFrameWork/PawnMovementComponent.h"
#include "GameFrameWork/Character.h"

UHeroAnimInstance::UHeroAnimInstance(const FObjectInitializer& Initailizer) : Super(Initailizer)
{

}

void UHeroAnimInstance::UpdateAnimInfo(float dt)
{
	APawn* Owner = TryGetPawnOwner(); // �õ�������pawn
	ACharacter* Player = Cast<ACharacter>(Owner);
	if (Owner != nullptr)
	{
		Speed = Owner->GetVelocity().Size(); // ����ƶ��ٶ�
		Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetBaseAimRotation()); // ͨ���ٶȺ���ת���㷽�� (-180~180)
		bInAir = Player->GetMovementComponent()->IsFalling();
	}
}

