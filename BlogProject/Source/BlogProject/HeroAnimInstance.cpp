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
	APawn* Owner = TryGetPawnOwner(); // 得到所属的pawn
	ACharacter* Player = Cast<ACharacter>(Owner);
	if (Owner != nullptr)
	{
		Speed = Owner->GetVelocity().Size(); // 获得移动速度
		Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetBaseAimRotation()); // 通过速度和旋转计算方向 (-180~180)
		bInAir = Player->GetMovementComponent()->IsFalling();
	}
}

