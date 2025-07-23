// SpeechToText.cpp

#include "SpeechToText.h"
#include "Async/Async.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"

ASpeechToText::ASpeechToText()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASpeechToText::StartAnalyzeAudio()
{
    const FString RootDir = FPaths::ProjectDir();
    const FString WhisperDir = FPaths::Combine(RootDir, TEXT("whisper.cpp-master"));
    const FString RunScript = FPaths::Combine(WhisperDir, TEXT("run.py"));
    const FString AudioIn = FPaths::Combine(RootDir, TEXT("TempData/AudioCapture.wav"));
    const FString AudioOutTxt = AudioIn + TEXT(".txt");

    // Run asynchronously to avoid blocking the game thread
    Async(EAsyncExecution::ThreadPool, [this, WhisperDir, RunScript, AudioIn, AudioOutTxt]()
        {
            FString CmdLine = FString::Printf(TEXT("\"%s\" \"%s\""), *RunScript, *AudioIn);

            // Launch the process in a non-blocking and hidden manner
            FProcHandle ProcHandle = FPlatformProcess::CreateProc(
                TEXT("python"),                   // Python executable
                *CmdLine,                         // Command line arguments
                true,                             // bLaunchDetached (run independently from UE process)
                true,                             // bLaunchHidden (hide the console window)
                true,                             // bLaunchReallyHidden (completely hidden, no window at all)
                nullptr,                          // Process ID (not required here)
                0,                                // Priority (default priority)
                *WhisperDir,                      // Working directory
                nullptr                           // Pipe (not redirecting output here)
            );

            if (!ProcHandle.IsValid())
            {
                // Handle failure to launch
                Async(EAsyncExecution::TaskGraphMainThread, [this]()
                    {
                        OnSpeechToTextComplete.Broadcast(TEXT("Failed to launch Python process."));
                    });
                return;
            }

            // Wait for the process to complete
            FPlatformProcess::WaitForProc(ProcHandle);

            // Check return code
            int32 ReturnCode;
            FPlatformProcess::GetProcReturnCode(ProcHandle, &ReturnCode);

            // Clean up process handle
            FPlatformProcess::CloseProc(ProcHandle);

            FString FinalResult;
            if (ReturnCode != 0)
            {
                FinalResult = FString::Printf(TEXT("Python error %d"), ReturnCode);
            }
            else
            {
                // Read the output file if the process succeeded
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

            // Return to the game thread and broadcast the result
            Async(EAsyncExecution::TaskGraphMainThread, [this, FinalResult]()
                {
                    OnSpeechToTextComplete.Broadcast(FinalResult);
                });
        });
}