// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "TrafficLightResponse.h"

#include "TrafficLightActor.generated.h"

UCLASS()
class SEMAFOROS_CPP_FRAN_API ATrafficLightActor : public AActor
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Geometría trigger del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Traffic Light Parameters")
		float resetTime;

	/// <summary>
	/// Geometría trigger del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Trigger Collision Params")
		class USphereComponent* sphereCollider;

	/// <summary>
	/// Luz del semáforo
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Light Params")
		UPointLightComponent* light;

private:

	/// <summary>
	/// Indica el estado en el que se encuentra el semáforo.
	/// OPENED: Indica que no hay ningún desplazador esperando la respuesta del semáforo (color verde).
	/// CLOSED: Indica que un desplazador está dentro de la zona (trigger) del semáforo (color rojo).
	/// WAITING: Indica que el semáforo tiene se está reiniciando después de que un desplazador haya 
	/// abandonado el área de influencia.
	/// </summary>
	enum State 
	{
		OPENED,
		CLOSED,
		WAITING
	};

private:

	/// <summary>
	/// Estado actual del semáforo.
	/// </summary>
	State currentState;

	/// <summary>
	///	Buffer de actores que entran en el área de influencia del semáforo.
	/// </summary>
	TQueue<ITrafficLightResponse*> buffer;

	/// <summary>
	/// Delegado único del timer
	/// </summary>
	FTimerHandle stateResetTimer;

public:	

	ATrafficLightActor();

protected:

	virtual void BeginPlay() override;

	/// <summary>
	/// Se llama en el constructor y se encarga de inicializar 
	/// todos los componentes del objeto y de inizializar las variables.
	/// </summary>
	virtual void Init();

public:	

	virtual void Tick(float DeltaTime) override;

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


private:

	/// <summary>
	/// Suscribe una función a cada evento de trigger
	/// generado por la geometría de colisión.
	/// </summary>
	void SusbcribeToTriggerEvents();

	/// <summary>
	/// Establece un nuevo estado para el semáforo
	/// </summary>
	void SetState(const State & newState);

	/// <summary>
	/// Se llama tras finalizar el timer. 
	/// Establece el estado del semáforo tras la espera.
	/// </summary>
	void ResetTrafficLight();
};