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
		float displacementSpeed;
		
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		FVector firstTargetLocation;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Custom Properties")
		FVector secondTargetLocation;

	/// <summary>
	/// Malla del objeto
	/// </summary>
	UPROPERTY(EditAnyWhere, Category = "Custom Mesh")
		class UStaticMeshComponent* mesh;

public:	
	// Sets default values for this actor's properties
	ADisplacerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
