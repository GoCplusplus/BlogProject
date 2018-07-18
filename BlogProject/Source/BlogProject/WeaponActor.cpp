// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "BeAttackInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAssert(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight"));
	WeaponMesh->SetSkeletalMesh(MeshAssert.Object);

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	if (WeaponCollision != nullptr)
	{
		RootComponent = WeaponCollision; // ���ø�
		//RootComponent = WeaponMesh;
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		//WeaponCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		WeaponCollision->SetVisibility(true); // �ڹؿ��пɼ�
	}

	bCanAttack = false;

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponCollision != nullptr)
	{
		WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponActor::OnHit);
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	if (bCanAttack && OtherActor != this) // �ڹ�����Чʱ������˺�
	{
		IBeAttackInterface* AC = Cast<IBeAttackInterface>(OtherActor);
		if (AC != nullptr)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10.0f, nullptr, this, UDamageType::StaticClass()); // ���10���˺�
		}
	}
}

void AWeaponActor::ActiveAttack()
{
	bCanAttack = true;
	if (WeaponCollision != nullptr) // ������ײ
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AWeaponActor::DeActiveAttack() // �ر���ײ
{
	bCanAttack = false;
	if (WeaponCollision != nullptr)
	{
		WeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}



