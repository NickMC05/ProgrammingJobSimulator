// TextToSpeech.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TextToSpeech.generated.h"

UCLASS()
class JOBSIMULATORV2_API ATextToSpeech : public AActor
{
    GENERATED_BODY()

public:
    ATextToSpeech();

    UFUNCTION(BlueprintCallable, Category = "TTS")
    void AnalyzeText(UObject* Context, UPARAM(ref)FString& Text);
};