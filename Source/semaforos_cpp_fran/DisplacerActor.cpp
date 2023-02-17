// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplacerActor.h"

// Sets default values
ADisplacerActor::ADisplacerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Init();

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ADisplacerActor::TriggerEnter);
	mesh->OnComponentEndOverlap.AddDynamic(this, &ADisplacerActor::TriggerExit);
}

#pragma region Built In Methods

void ADisplacerActor::BeginPlay()
{
	Super::BeginPlay();

}
void ADisplacerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma endregion

#pragma region Custom Methods

void ADisplacerActor::Init()
{
	mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Displacer Mesh"));
	mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}
void ADisplacerActor::RestrictedAccessResponse()
{

}

#pragma endregion


#pragma region Handle Trigger Event Methods

void ADisplacerActor::TriggerEnter(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trigger Enter"));
	// Castear a ATrafficLightActor
	// Si casting correcto -> Conectar su evento del semáforo al método correspondiente
}
void ADisplacerActor::TriggerExit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trigger Exit"));
	// Castear a ATrafficLightActor
	// Si casting correcto -> Desconectar su evento del semáforo al método correspondiente
}

#pragma endregion