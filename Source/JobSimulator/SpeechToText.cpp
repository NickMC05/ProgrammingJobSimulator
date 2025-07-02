#include "SpeechToText.h"
#include "HAL/PlatformProcess.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

// Sets default values
ASpeechToText::ASpeechToText()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpeechToText::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ASpeechToText::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASpeechToText::AnalyzeAudio(UObject* Context)
{
    // 1. Execute Python script
    system("python C:\\Users\\FTV\\Documents\\Unreal Projects\\JobSimulator\\whisper.cpp-master\\test.py");
    UKismetSystemLibrary::PrintString(Context, "1 executed");

    // 2. Read the output file using Unreal's file system
    FString FilePath = TEXT("C:\\Users\\FTV\\Documents\\Unreal Projects\\JobSimulator\\whisper.cpp-master\\samples\\jfk.mp3.txt");
    FString FileContent;

    if (FFileHelper::LoadFileToString(FileContent, *FilePath))
    {
        TArray<FString> Lines;
        FileContent.ParseIntoArrayLines(Lines);

        for (const FString& Line : Lines)
        {
            UKismetSystemLibrary::PrintString(Context, Line);
        }
    }
    else
    {
        UKismetSystemLibrary::PrintString(Context, TEXT("Unable to open file"));
    }

    UKismetSystemLibrary::PrintString(Context, "3 executed");
}