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
	/// Posición en el mundo que funcionará como punto de referencia a donde moverse
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		FVector firstTargetLocation;

	/// <summary>
	/// Posición en el mundo que funcionará como punto de referencia a donde moverse
	/// </summary>
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		FVector secondTargetLocation;

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
};