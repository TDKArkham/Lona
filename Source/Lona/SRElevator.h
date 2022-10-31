// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "SRElevator.generated.h"

class UBoxComponent;
class USplineComponent;

UCLASS()
class LONA_API ASRElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	ASRElevator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FTimeline ElevatorTimeline;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator")
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elevator")
	USplineComponent* SplineComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elevator")
	UCurveFloat* MovementCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Elevator")
	bool bCanAutoStart;

public:
	UFUNCTION()
	void OnBeginMovement(float Value);

	UFUNCTION()
	void OnEndMovement();

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
