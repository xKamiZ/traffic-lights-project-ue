// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TrafficLightResponse.h"
#include "Components/StaticMeshComponent.h"

#include "DisplacerActor.generated.h"

UCLASS()
class SEMAFOROS_CPP_FRAN_API ADisplacerActor : public AActor, public ITrafficLightResponse
{
	GENERATED_BODY()

public:

	/// <summary>
	/// Velocidad de movimiento del actor.
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		float movementSpeed;

	/// <summary>
	/// A que distancia tiene que estar el actor de 
	/// la posición objetivo para que se considere
	/// que la ha alcanzado.
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		float offsetToReachPoint;

	/// <summary>
	/// Posición en el mundo que funcionará como punto de referencia a donde moverse
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		FVector wayPointLocation;

	/// <summary>
	/// Malla del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Custom Mesh")
		class UStaticMeshComponent* mesh;

private:

	/// <summary>
	/// Indica si el desplazador se puede mover o no.
	/// </summary>
	bool canMove;

	/// <summary>
	/// Controla la dirección de movimiento del actor.
	/// Se calcula en Init el vector entre firstTargetLocation y secondTargetLocation.
	/// </summary>
	FVector movementDirection;

	/// <summary>
	/// Posición inicial de la que parte el actor.
	/// </summary>
	FVector startLocation;

	/// <summary>
	/// Posición actual del displacer.
	/// </summary>
	FVector currentLocation;

	/// <summary>
	/// Distancia lineal de la dirección.
	/// </summary>
	float pathDistance;

public:	

	ADisplacerActor();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Implementado de la interfaz.
	/// Deshabilita el movimiento del desplazador.
	/// </summary>
	virtual void RefuseAccess() override;

	/// <summary>
	/// Implementado de la interfaz.
	/// Habilita el movimiento del desplazador.
	/// </summary>
	virtual void AllowAccess() override;

	/// <summary>
	/// Activa o desactiva el movimiento del desplazador.
	/// </summary>
	void SetMovement(bool newState);

private:

	/// <summary>
	/// Inicializa las propiedades de clase. Se ejecuta en el constructor.
	/// </summary>
	void Init();

	/// <summary>
	/// Controla el movimiento del actor entre dos puntos.
	/// </summary>
	void HandleDisplacerMovement(float deltaTime);

	/// <summary>
	/// Comprueba si el actor se encuentra en alguna de las posiciones entre las 
	/// que se tiene que mover.
	/// </summary>
	/// <returns>True si ha llegado a la posición</returns>
	bool WaypointReached();

	/// <summary>
	/// Invierte el sentido del movimiento del actor.
	/// </summary>
	inline void InvertMovementSense() { movementDirection *= -1.0f; }
};