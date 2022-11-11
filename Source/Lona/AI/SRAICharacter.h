// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SRAICharacter.generated.h"

class UPawnSensingComponent;
class USRAttributeComponent;

UCLASS()
class LONA_API ASRAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASRAICharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	USRAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPawnSensingComponent* PawnSensingComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathMontage;

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigateActor, USRAttributeComponent* OwnerComponent, float NewValue, float Delta);
	
public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<FVector> LocationsToGo;
};
