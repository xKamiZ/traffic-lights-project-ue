// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DisplacerActor.generated.h"

UCLASS()
class SEMAFOROS_CPP_FRAN_API ADisplacerActor : public AActor
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

public:	

	ADisplacerActor();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Se llama como respuesta al delegado invocado por el semáforo
	/// cuando éste está siendo utilizado. 
	/// Detiene el movimiento del desplazador.
	/// </summary>
	UFUNCTION()
		void RestrictedAccessResponse();

	/// <summary>
	/// Responde al evento de trigger cuando un objeto entra en la geometría de colisiones
	/// </summary>
	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* hitComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	/// <summary>
	/// Responde al evento de trigger cuando un objeto sale de la geometría de colisiones
	/// </summary>
	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* hitComp, class AActor* otherActor, class UPrimitiveComponent* otherComp, int32 otherBodyIndex);

private:

	/// <summary>
	/// Inicializa las propiedades de clase. Se ejecuta en el constructor.
	/// </summary>
	void Init();
};