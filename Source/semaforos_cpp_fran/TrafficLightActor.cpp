// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLightActor.h"

// Sets default values
ATrafficLightActor::ATrafficLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Init();
	SusbcribeToTriggerEvents();
}

#pragma region Built In Methods

void ATrafficLightActor::BeginPlay()
{
	Super::BeginPlay();

	// Establece el color por defecto del semáforo
	light->SetLightColor(FLinearColor::Green);
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
	currentState = State::ON;

	//Se crea el componente collider
	sphereCollider = CreateDefaultSubobject<USphereComponent>("Sphere Collider");

	//Se establece el radio de la esfera
	sphereCollider->SetSphereRadius(180.0f);

	//Se modifica la jerarquía de compnentes
	sphereCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	// Se crea el componente Point Light
	light = CreateDefaultSubobject<UPointLightComponent>("Point Light");
	
	// Establece el componente padre de la luz en la jerarquía de componentes del objeto
	light->AttachToComponent(sphereCollider, FAttachmentTransformRules::SnapToTargetIncludingScale);
}
void ATrafficLightActor::SusbcribeToTriggerEvents()
{
	//Suscripción al los eventos de beginOverlap (trigger enter)
	sphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLightActor::TriggerEnter);

	//Suscripción al los eventos de endOverlap (trigger exit)
	sphereCollider->OnComponentEndOverlap.AddDynamic(this, &ATrafficLightActor::TriggerExit);
}
void ATrafficLightActor::SetState(const State & newState)
{
	currentState = newState;
}

#pragma endregion

#pragma region Handle Trigger Event Methods

void ATrafficLightActor::TriggerEnter(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	// Añade el actor que ha entrado al buffer.
	buffer.Enqueue(otherActor);

	// Si estado == ON -> estado pasa a OFF. Cambia el color a rojo
	// Si estado == OFF o WAIT, mantiene ese estado. Detiene movimiento del desplazador que ha entrado.
	if (currentState == State::ON)
	{
		SetState(State::OFF);
		light->SetLightColor(FLinearColor::Red);
	}
	else
		OnRestrictedAccess.Broadcast();
}
void ATrafficLightActor::TriggerExit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	// Saca el actor del buffer
	buffer.Pop();

	// Estado == WAIT.
	// Inicia timer del semáforo
	
	 
	// Timer finaliza:
	// Si buffer > 0 -> Estado OFF, permitir paso del siguiente elemento en el buffer.
	// Si buffer <= 0 -> Estado ON. Cambia color a verde.
	if (buffer.IsEmpty()) 
	{
		SetState(State::OFF);
	}
	else
	{
		SetState(State::ON);
		light->SetLightColor(FLinearColor::Green);
	}
}

#pragma endregion