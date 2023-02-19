// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplacerActor.h"
#include "TrafficLightActor.h"

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

	movementDirection = wayPointLocation - startLocation;

	pathDistance = movementDirection.Size();

	movementDirection = movementDirection.GetSafeNormal();

	SetMovement(true);
}
void ADisplacerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!canMove) return;

	currentLocation = GetActorLocation();

	//if (WaypointReached()) InvertMovementSense();

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
	if (currentLocation == wayPointLocation || currentLocation == startLocation) InvertMovementSense();

	currentLocation += movementDirection * movementSpeed * deltaTime;

	SetActorLocation(currentLocation);
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