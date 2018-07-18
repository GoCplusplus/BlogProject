// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

UCLASS()
class BLOGPROJECT_API AWeaponActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = mesh)
	class USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, Category = Collision)
	class UBoxComponent* WeaponCollision;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bCanAttack;

public:
	// Sets default values for this actor's properties
	AWeaponActor();

	void ActiveAttack(); // ¼¤»îÎäÆ÷

	void DeActiveAttack(); // ²»¼¤»îÎäÆ÷

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }

	FORCEINLINE class UBoxComponent* GetWeaponCollision() { return WeaponCollision; }
	
};
