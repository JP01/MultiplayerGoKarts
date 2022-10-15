// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

	UPROPERTY()
	float Throttle;
	UPROPERTY()
	float SteeringThrow;

	UPROPERTY()
	float DeltaTime;
	UPROPERTY()
	float Time;

	bool IsValid() const
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

	FVector GetVelocity() { return Velocity; }
	void SetVelocity(FVector val) { Velocity = val; }

	void SetThrottle(float val) { Throttle = val; }
	void SetSteeringThrow(float val) { SteeringThrow = val; }

	FGoKartMove GetLastMove() { return LastMove; }

private:
	float Throttle;
	float SteeringThrow;
	FVector Velocity;
	FGoKartMove LastMove;

	FGoKartMove CreateMove(float DeltaTime);

	// Mass of the car in (kg)
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	// Force applied to car when throttle is full down (N)
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	// The minimum radus of the car turning circle at full lock (m)
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10;

	// Higher means more drag
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	// Higher means more rolling resistance
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = 0.015;

	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime, float _SteeringThrow);
	FVector GetAirResistance();
	FVector GetRollingResistance();
};
