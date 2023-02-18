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
	/// Geometr�a trigger del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Traffic Light Parameters")
		float resetTime;

	/// <summary>
	/// Geometr�a trigger del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Trigger Collision Params")
		class USphereComponent* sphereCollider;

	/// <summary>
	/// Luz del sem�foro
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Light Params")
		UPointLightComponent* light;

private:

	/// <summary>
	/// Indica el estado en el que se encuentra el sem�foro.
	/// OPENED: Indica que no hay ning�n desplazador esperando la respuesta del sem�foro (color verde).
	/// CLOSED: Indica que un desplazador est� dentro de la zona (trigger) del sem�foro (color rojo).
	/// WAITING: Indica que el sem�foro tiene se est� reiniciando despu�s de que un desplazador haya 
	/// abandonado el �rea de influencia.
	/// </summary>
	enum State 
	{
		OPENED,
		CLOSED,
		WAITING
	};

private:

	/// <summary>
	/// Estado actual del sem�foro.
	/// </summary>
	State currentState;

	/// <summary>
	///	Buffer de actores que entran en el �rea de influencia del sem�foro.
	/// </summary>
	TQueue<ITrafficLightResponse*> buffer;

	/// <summary>
	/// Delegado �nico del timer
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
	/// Responde al evento de trigger cuando un objeto entra en la geometr�a de colisiones
	/// </summary>
	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/// <summary>
	/// Responde al evento de trigger cuando un objeto sale de la geometr�a de colisiones
	/// </summary>
	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


private:

	/// <summary>
	/// Suscribe una funci�n a cada evento de trigger
	/// generado por la geometr�a de colisi�n.
	/// </summary>
	void SusbcribeToTriggerEvents();

	/// <summary>
	/// Establece un nuevo estado para el sem�foro
	/// </summary>
	void SetState(const State & newState);

	/// <summary>
	/// Se llama tras finalizar el timer. 
	/// Establece el estado del sem�foro tras la espera.
	/// </summary>
	void ResetTrafficLight();
};