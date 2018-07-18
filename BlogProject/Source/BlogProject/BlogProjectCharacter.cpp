// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BlogProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeroAnimInstance.h"
#include "WeaponActor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "BlogGameInstance.h"
#include "BlogSaveGame.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// ABlogProjectCharacter

ABlogProjectCharacter::ABlogProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	static ConstructorHelpers::FClassFinder<AWeaponActor> WeaponBP(TEXT("/Game/ThirdPersonCPP/Blueprints/WeaponActorBP"));
	if (WeaponBP.Succeeded())
	{
		WeaponM = WeaponBP.Class;
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABlogProjectCharacter::BeginPlay()
{
	Super::BeginPlay(); // 记得一定先调父类的函数
	//武器的添加
	//Weapon = GetWorld()->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass()); // 之前的创建方式
	Weapon = GetWorld()->SpawnActor<AWeaponActor>(WeaponM);
	//if (Weapon != nullptr)
	//{
	//	// 附加武器，保持位置
	//	Weapon->GetWeaponMesh()->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon"));
	//}

	UBlogGameInstance* GI = Cast<UBlogGameInstance>(GetWorld()->GetGameInstance());
	UE_LOG(LogTemp, Warning, TEXT("SaveGame: GameInstance: %s, %d"), *(GI->GetName()), 1);
	if (GI != nullptr && GI->bLoadGame) // 如果是读取游戏
	{
		SetActorLocation(GI->GetHeroLocation()); // 设置到上一次保存的位置
	}

	//UBlogSaveGame* SaveGameInstance = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
	//SaveGameInstance = Cast<UBlogSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HeroLocation"), 0));
	//if (SaveGameInstance != nullptr)
	//	SetActorLocation(SaveGameInstance->LastLocation);

	//bool bRet = UGameplayStatics::DoesSaveGameExist(TEXT("HeroLocation"), 0);
	//if (bRet) // 如果有存档，则读取记录
	//{
	//	//SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
	//	UBlogSaveGame* SaveGame = Cast<UBlogSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("HeroLocation"), 0));
	//	if (SaveGame)
	//	{
	//		FVector HeroLocation = SaveGame->LastLocation; // 读取最后一次保存的位置
	//		SetActorLocation(HeroLocation);
	//	}
	//}


}

void ABlogProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABlogProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlogProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABlogProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABlogProjectCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABlogProjectCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABlogProjectCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABlogProjectCharacter::OnResetVR);

	// 绑定攻击
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ABlogProjectCharacter::Attack);

	// 绑定保存游戏按钮
	PlayerInputComponent->BindAction("SaveGame", IE_Pressed, this, &ABlogProjectCharacter::SaveGame);

}


void ABlogProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABlogProjectCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ABlogProjectCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ABlogProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABlogProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABlogProjectCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABlogProjectCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABlogProjectCharacter::Attack()
{
	UHeroAnimInstance* AnimInstance = Cast<UHeroAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance != nullptr)
	{
		if (!AnimInstance->Montage_IsPlaying(AttackMontage)) // 如果该蒙太奇动画未在播放，则进行播放
		{
			Weapon->ActiveAttack();
			float fDt = AnimInstance->Montage_Play(AttackMontage);
			FTimerHandle ActiveWeapon;
			GetWorld()->GetTimerManager().SetTimer(ActiveWeapon, [=]() {
				Weapon->DeActiveAttack();
			}, fDt, false);
		}
	}
}

void ABlogProjectCharacter::Tick(float DeltaSeconds) // 需要在每一帧重新置位置，而不是attach。
{
	Super::Tick(DeltaSeconds);
	if (Weapon != nullptr)
	{
		FVector Location;
		FQuat Rotation;
		GetMesh()->GetSocketWorldLocationAndRotation(TEXT("weapon"), Location, Rotation);
		FVector New = Weapon->GetWeaponCollision()->GetScaledBoxExtent();
		//FVector NewLocation = FVector(Location.X + New.Size() / 2 + 20, Location.Y, Location.Z);
		//Weapon->GetWeaponCollision()->SetWorldLocationAndRotation(Location, Rotation);
		//Weapon->GetWeaponMesh()->SetWorldLocationAndRotation(Location, Rotation);
		Weapon->SetActorLocationAndRotation(Location, Rotation);
	}
}

void ABlogProjectCharacter::SaveGame()
{
	UBlogGameInstance* GI = Cast<UBlogGameInstance>(GetWorld()->GetGameInstance());
	UE_LOG(LogTemp, Warning, TEXT("SaveGame: ClassName: %s, %d"), *(GI->GetName()), 1);
	if (GI != nullptr) // save game必须要创建新的文件
	{
		UBlogSaveGame* SaveGameInstance = Cast<UBlogSaveGame>(UGameplayStatics::CreateSaveGameObject(UBlogSaveGame::StaticClass()));
		SaveGameInstance->LastLocation = GetActorLocation();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("HeroLocation"), 0); // 保存游戏
	}
}
