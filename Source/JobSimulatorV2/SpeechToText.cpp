// SpeechToText.cpp

#include "SpeechToText.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformProcess.h"
#include "Async/Async.h"

ASpeechToText::ASpeechToText()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASpeechToText::StartAnalyzeAudio()
{
    const FString RootDir     = FPaths::ProjectDir();
    const FString WhisperDir  = FPaths::Combine(RootDir, TEXT("whisper.cpp-master"));
    const FString RunScript   = FPaths::Combine(WhisperDir, TEXT("run.py"));
    const FString AudioIn     = FPaths::Combine(RootDir, TEXT("TempData/AudioCapture.wav"));
    const FString AudioOutTxt = AudioIn + TEXT(".txt");

    Async(EAsyncExecution::ThreadPool, [this, WhisperDir, RunScript, AudioIn, AudioOutTxt]()
    {
        // build: "run.py" "AudioCapture.wav"
        FString CmdLine = FString::Printf(TEXT("\"%s\" \"%s\""), *RunScript, *AudioIn);

        int32   ReturnCode;
        FString StdOut, StdErr;
        bool    bLaunched = FPlatformProcess::ExecProcess(
            TEXT("python"), *CmdLine, &ReturnCode, &StdOut, &StdErr, *WhisperDir
        );

        FString FinalResult;
        if (!bLaunched)
        {
            FinalResult = TEXT("Failed to launch python.");
        }
        else if (ReturnCode != 0)
        {
            FinalResult = FString::Printf(TEXT("Python error %d: %s"), ReturnCode, *StdErr);
        }
        else
        {
            FString FileContent;
            if (FFileHelper::LoadFileToString(FileContent, *AudioOutTxt))
            {
                TArray<FString> Lines;
                FileContent.ParseIntoArrayLines(Lines);
                FinalResult = FString::Join(Lines, TEXT(" "));
            }
            else
            {
                FinalResult = TEXT("Could not read output file.");
            }
        }

        // back on game-thread
        Async(EAsyncExecution::TaskGraphMainThread, [this, FinalResult]()
        {
            OnSpeechToTextComplete.Broadcast(FinalResult);
        });
    });
}