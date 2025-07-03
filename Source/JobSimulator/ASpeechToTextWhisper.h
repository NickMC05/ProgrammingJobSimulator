// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASpeechToTextWhisper.generated.h"

UCLASS()
class JOBSIMULATOR_API AASpeechToTextWhisper : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASpeechToTextWhisper();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
