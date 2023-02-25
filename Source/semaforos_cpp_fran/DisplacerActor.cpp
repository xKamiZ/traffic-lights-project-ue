// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplacerActor.h"
#include "TrafficLightActor.h"
#include "Math/UnrealMathUtility.h"

ADisplacerActor::ADisplacerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Init();
}

#pragma region Built In Methods

void ADisplacerActor::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();

	movementDirection = GetActorForwardVector();

	SetMovement(true);

	squareOffset = FMath::Pow(offsetToReachPoint, 2);

	currentTargetLocation = wayPoint;
}
void ADisplacerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!canMove) return;

	if (WaypointReached()) InvertMovementSense();

	currentLocation = GetActorLocation();

	HandleDisplacerMovement(DeltaTime);
}

#pragma endregion

#pragma region Custom Methods

void ADisplacerActor::Init()
{
	mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Displacer Mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void ADisplacerActor::HandleDisplacerMovement(float deltaTime)
{
	currentLocation += movementDirection * movementSpeed * deltaTime;

	SetActorLocation(currentLocation);
}

bool ADisplacerActor::WaypointReached()
{
	// Se calculan las distancias cuadradas para evitar calcular la magnitud del vector en cada frame
	float xSquareDistanceToTarget = FMath::Pow((currentTargetLocation.X - currentLocation.X), 2);
	float ySquareDistanceToTarget = FMath::Pow((currentTargetLocation.Y - currentLocation.Y), 2);

	float squareDistanceToTarget = xSquareDistanceToTarget + ySquareDistanceToTarget;

	if (squareDistanceToTarget < squareOffset)
	{
		// Se cambia la posición objetivo
		if (currentTargetLocation == wayPoint) currentTargetLocation = startLocation;
		else currentTargetLocation = wayPoint;

		return true;
	}

	return false;
}

void ADisplacerActor::RefuseAccess()
{
	SetMovement(false);
}

void ADisplacerActor::AllowAccess()
{
	SetMovement(true);
}

void ADisplacerActor::SetMovement(bool newState)
{
	canMove = newState;
}

#pragma endregion