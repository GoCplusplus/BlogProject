// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BeAttackInterface.h"
#include "AIBlogCharacter.generated.h"

UCLASS()
class BLOGPROJECT_API AAIBlogCharacter : public ACharacter, public IBeAttackInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = See)
	class UPawnSensingComponent* Sight;

	UPROPERTY(EditAnywhere, Category = HealthUI)
	class UWidgetComponent* HealthUICompo;

	TSubclassOf<UUserWidget> HealthUIWidget;

	float CurrentHealth;
	float MaxHealth;

public:
	//class UBlackboardData* HeroData;
	class UBlackboardComponent* HeroData;
	bool bSeen;

public:
	// Sets default values for this character's properties
	AAIBlogCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void HaveSeePawn(APawn* Pawn);

	FORCEINLINE class UWidgetComponent* GetHealthUICompo() { return HealthUICompo; }

	virtual void BeAttacked(float fDamage) {};
	
	
};
