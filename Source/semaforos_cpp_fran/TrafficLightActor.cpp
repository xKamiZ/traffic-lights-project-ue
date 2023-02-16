// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficLightActor.h"

// Sets default values
ATrafficLightActor::ATrafficLightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Init();
	SusbcribeToTriggerEvents();
}

void ATrafficLightActor::BeginPlay()
{
	Super::BeginPlay();
}
void ATrafficLightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

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

void ATrafficLightActor::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
void ATrafficLightActor::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}