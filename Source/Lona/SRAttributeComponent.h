// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SRAttributeComponent.generated.h"

class USRAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChanged, AActor*, InstigateActor, USRAttributeComponent*, OwnerComponent, float, NewValue, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LONA_API USRAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USRAttributeComponent();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float HealthMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	int32 MagicPool;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	int32 MagicPoolMax;

public:
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeChanged OnMagicPoolChanged;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	static USRAttributeComponent* GetAttributeComponent(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealthMax() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool GetIsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigateActor, float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetMagicPool() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	int32 GetMagicPoolMax() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyMagicPoolChange(float Delta);
};
