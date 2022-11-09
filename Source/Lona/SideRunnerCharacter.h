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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	USRAttributeComponent* AttributeComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Direction")
	bool bIsFacingRight;

	UPROPERTY(BlueprintReadWrite, Category = "Action")
	bool bIsCrouching;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;
	
	void MoveRight(float Value);

	void Fire();

	UFUNCTION()
	void UpdateCharacterFaceDirection();

public:
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	USRAttributeComponent* GetAttributeComponent() const;
};
