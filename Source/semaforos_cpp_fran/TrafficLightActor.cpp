// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLightActor.h"
#include "DisplacerActor.h"

// Sets default values
ATrafficLightActor::ATrafficLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Init();
	SusbcribeToTriggerEvents();
}

#pragma region Built In Methods

void ATrafficLightActor::BeginPlay()
{
	Super::BeginPlay();

	// Establece el color por defecto del semáforo
	_light->SetLightColor(FLinearColor::Green);
}
void ATrafficLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma endregion

#pragma region Custom Methods

void ATrafficLightActor::Init()
{
	// El estado por defecto del semáforo es ON
	_currentState = State::ON;

	//Se crea el componente collider
	_sphereCollider = CreateDefaultSubobject<USphereComponent>("Sphere Collider");

	//Se establece el radio de la esfera
	_sphereCollider->SetSphereRadius(180.0f);

	//Se modifica la jerarquía de compnentes
	_sphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Se crea el componente Point Light
	_light = CreateDefaultSubobject<UPointLightComponent>("Point Light");
	
	// Establece el componente padre de la luz en la jerarquía de componentes del objeto
	_light->AttachToComponent(_sphereCollider, FAttachmentTransformRules::SnapToTargetIncludingScale);
}
void ATrafficLightActor::SusbcribeToTriggerEvents()
{
	//Suscripción al los eventos de beginOverlap (trigger enter)
	_sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLightActor::TriggerEnter);

	//Suscripción al los eventos de endOverlap (trigger exit)
	_sphereCollider->OnComponentEndOverlap.AddDynamic(this, &ATrafficLightActor::TriggerExit);
}

#pragma endregion

#pragma region Handle Trigger Event Methods

void ATrafficLightActor::TriggerEnter(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	// Comprobar si es un ADisplacerActor.
	
	// Si lo es, detener su movimiento.
	// Iniciar timer del semáforo.
	// Cuando
}
void ATrafficLightActor::TriggerExit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{

}

#pragma endregion