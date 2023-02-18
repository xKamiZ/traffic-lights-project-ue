// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TrafficLightResponse.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTrafficLightResponse : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SEMAFOROS_CPP_FRAN_API ITrafficLightResponse
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/// <summary>
	/// Se llama cuando un actor entra en el área del semáforo
	/// y éste ya está en uso.
	/// </summary>
	virtual void RefuseAccess();

	/// <summary>
	/// Se llama cuando el semáforo se reinicia y permite
	/// el paso al siguiente actor en el buffer.
	/// </summary>
	virtual void AllowAccess();
};