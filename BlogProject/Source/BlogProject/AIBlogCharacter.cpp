// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBlogCharacter.h"
#include "AIBlogController.h"
#include "Perception/PawnSensingComponent.h"
#include "BlogProjectCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "UObject/ConstructorHelpers.h"
#include "RobotHealthUserWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAIBlogCharacter::AAIBlogCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAIBlogController::StaticClass();

	Sight = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sight"));
	HeroData = CreateDefaultSubobject<UBlackboardComponent>(TEXT("HeroData"));
	bSeen = false;

	HealthUICompo = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthUICompo"));
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthUIBP(TEXT("/Game/ThirdPersonCPP/AI/RobotHealth"));
	if (HealthUIBP.Succeeded())
	{
		HealthUIWidget = HealthUIBP.Class;
	}

	if (HealthUICompo != nullptr)
	{
		HealthUICompo->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform); // ע��Ҫattach����Ȼ������ʾ
	}

	CurrentHealth = 100.0f;
	MaxHealth = 100.0f;

}

// Called when the game starts or when spawned
void AAIBlogCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (Sight != nullptr)
	{
		Sight->OnSeePawn.AddDynamic(this, &AAIBlogCharacter::HaveSeePawn);
	}

	if (HealthUIWidget != nullptr)
	{
		URobotHealthUserWidget* Widget = CreateWidget<URobotHealthUserWidget>(GetWorld()->GetGameInstance(), HealthUIWidget);
		if (Widget != nullptr)
		{
			if (HealthUICompo != nullptr)
			{
				HealthUICompo->SetWidget(Widget);
			}
		}
	}

}

// Called every frame
void AAIBlogCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HealthUICompo != nullptr)
	{
		URobotHealthUserWidget* Widget = Cast<URobotHealthUserWidget>(HealthUICompo->GetUserWidgetObject());
		if (Widget != nullptr)
		{
			Widget->UpdateHealth(CurrentHealth, MaxHealth);
		}
	}

	//��תѪ��
	if (HealthUICompo != nullptr)
	{
		//���ȵõ����ǵ�������ӽ�
		FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		//�ٵõ����ǵ�component����������
		FVector CompoLocation = HealthUICompo->GetComponentLocation();
		//ʹ��һ����ѧ������
		FRotator Turn = UKismetMathLibrary::FindLookAtRotation(CompoLocation, PlayerLocation);
		FRotator NewRotation(0, 0, 0);
		NewRotation.Yaw = Turn.Yaw; // ֻ��תYaw
		HealthUICompo->SetWorldRotation(NewRotation);
	}

}

// Called to bind functionality to input
void AAIBlogCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIBlogCharacter::HaveSeePawn(APawn* Pawn)
{
	ABlogProjectCharacter* Player = Cast<ABlogProjectCharacter>(Pawn);
	AAIBlogController* AIC = Cast<AAIBlogController>(GetController());

	if (Player != nullptr)
	{
		FVector Location = Player->GetActorLocation(); // ��ȡĿ���λ�ã�������������
		if (AIC != nullptr)
		{
			AIC->GetBlackBoardCompo()->SetValueAsVector(TEXT("TargetLocation"), Location);
			bSeen = true;
		}
	}
}

float AAIBlogCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	if (CurrentHealth <= 0) // �ܵ��㹻���˺��ˣ�����actor
	{
		Destroy();
	}

	return 0.0f;
}

