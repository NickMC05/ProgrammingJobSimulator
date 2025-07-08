// SpeechToText.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpeechToText.generated.h"

// A Blueprint‐assignable delegate that carries the final string
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnSpeechToTextComplete,
    const FString&, TranscribedText
);

UCLASS()
class JOBSIMULATORV2_API ASpeechToText : public AActor
{
    GENERATED_BODY()

public:
    ASpeechToText();

    // Starts the async process; returns immediately
    UFUNCTION(BlueprintCallable, Category = "Speech")
    void StartAnalyzeAudio();

    // Fired on the game thread when the process finishes
    UPROPERTY(BlueprintAssignable, Category = "Speech")
    FOnSpeechToTextComplete OnSpeechToTextComplete;
};