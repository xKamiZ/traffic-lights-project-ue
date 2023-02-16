// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"

#include "TrafficLightActor.generated.h"

UCLASS()
class SEMAFOROS_CPP_FRAN_API ATrafficLightActor : public AActor
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Geometría trigger del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Trigger Collision Params")
		class USphereComponent* _sphereCollider;

	/// <summary>
	/// Luz del semáforo
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Light Params")
		UPointLightComponent* _light;

private:

	/// <summary>
	/// Indica el estado en el que se encuentra el semáforo
	/// </summary>
	enum State 
	{
		ON,
		OFF,
		WAIT
	};

private:

	/// <summary>
	/// Estado actual del semáforo
	/// </summary>
	State _currentState;

	/// <summary>
	/// Colores del semáforo
	/// </summary>
	TArray<FColor> _colors;

public:	
	// Sets default values for this actor's properties
	ATrafficLightActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/// <summary>
	/// Se llama en el constructor y se encarga de inicializar 
	/// todos los componentes del objeto y de inizializar las variables.
	/// </summary>
	virtual void Init();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// Responde al evento de trigger cuando un objeto entra en la geometría de colisiones
	/// </summary>
	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// Responde al evento de trigger cuando un objeto sale de la geometría de colisiones
	/// </summary>
	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/// <summary>
	/// Suscribe una función a cada evento de trigger
	/// generado por la geometría de colisión.
	/// </summary>
	void SusbcribeToTriggerEvents();
};