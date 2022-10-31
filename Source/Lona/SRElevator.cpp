// Fill out your copyright notice in the Description page of Project Settings.


#include "SRElevator.h"

#include "SideRunnerCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"

ASRElevator::ASRElevator()
{
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMeshComponent);

	bCanAutoStart = false;
}

void ASRElevator::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASRElevator::OnBeginOverlap);
	//BoxCollision->OnComponentEndOverlap.AddDynamic(this, &)
	
	if(MovementCurve)
	{
		FOnTimelineFloat StartTimelineFloat;
		StartTimelineFloat.BindUFunction(this, "OnBeginMovement");
		ElevatorTimeline.AddInterpFloat(MovementCurve, StartTimelineFloat);

		FOnTimelineEvent EndTimelineEvent;
		EndTimelineEvent.BindUFunction(this, "OnEndMovement");
		ElevatorTimeline.SetTimelineFinishedFunc(EndTimelineEvent);

		ElevatorTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	}

	if(bCanAutoStart)
	{
		ElevatorTimeline.PlayFromStart();
	}
}

void ASRElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ElevatorTimeline.IsPlaying())
	{
		ElevatorTimeline.TickTimeline(DeltaTime);
	}
}

void ASRElevator::OnBeginMovement(float Value)
{
	const float SplineLength = SplineComponent->GetSplineLength();
	FVector CurrentLocation = SplineComponent->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	//FRotator CurrentRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	StaticMeshComponent->SetWorldLocation(CurrentLocation);
	//StaticMeshComponent->SetWorldLocationAndRotation(CurrentLocation, CurrentRotation);
}

void ASRElevator::OnEndMovement()
{
	if(!ElevatorTimeline.IsReversing())
	{
		ElevatorTimeline.Reverse();
	}
	else
	{
		ElevatorTimeline.Stop();
	}
}

void ASRElevator::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ASideRunnerCharacter>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped!"));
		if(!ElevatorTimeline.IsPlaying())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("CanPlay!"));
			ElevatorTimeline.PlayFromStart();
		}
	}
}
