// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SideRunnerCharacter.generated.h"

class USRAttributeComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LONA_API ASideRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASideRunnerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	bool bCanStartAction;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	USRAttributeComponent* AttributeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleAnywhere, Category = "Animation")
	FName SocketName;

	UPROPERTY(BlueprintReadWrite, Category = "Direction")
	bool bIsFacingRight;

	UPROPERTY(BlueprintReadWrite, Category = "Action")
	bool bIsCrouching;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	int32 AttackCost;
	
	void MoveRight(float Value);

	void Fire();

	UFUNCTION()
	void Fire_TimeElapsed();

	UFUNCTION()
	void UpdateCharacterFaceDirection();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigateActor, USRAttributeComponent* OwnerComponent, float NewValue, float Delta);
};
