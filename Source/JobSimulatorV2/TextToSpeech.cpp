#include "TextToSpeech.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Async/Async.h"

ATextToSpeech::ATextToSpeech()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATextToSpeech::AnalyzeText(UObject* Context, UPARAM(ref) FString& Text)
{
    // 1) Get script path
    const FString ProjectRoot = FPaths::ProjectDir();
    const FString ScriptDir = FPaths::Combine(ProjectRoot, TEXT("F5-TTS"));
    const FString ScriptPath = FPaths::Combine(ScriptDir, TEXT("run.py"));

    // 2) Escape the text for command line
    FString EscapedText = Text.Replace(TEXT("\""), TEXT("\\\""));
    FString FullCommand = FString::Printf(TEXT("\"%s\" \"%s\""), *ScriptPath, *EscapedText);

    // Run asynchronously to avoid freezing
    Async(EAsyncExecution::Thread, [Context, ScriptDir, FullCommand]()
        {
            // 3) Create the process without showing a console window
            FProcHandle ProcHandle = FPlatformProcess::CreateProc(
                TEXT("python"),                   // Python executable
                *FullCommand,                     // Command line arguments
                true,                             // bLaunchDetached (run independently of parent process)
                true,                             // bLaunchHidden (hide the command prompt window)
                true,                             // bLaunchReallyHidden (completely hide, no focus or window at all)
                nullptr,                          // Process ID (not needed here)
                0,                                // Priority (default priority)
                *ScriptDir,                       // Working directory
                nullptr                           // Pipe (not redirecting output here)
            );

            if (!ProcHandle.IsValid())
            {
                // Report failure to spawn process
                AsyncTask(ENamedThreads::GameThread, [Context]()
                    {
                        UKismetSystemLibrary::PrintString(Context, TEXT("Failed to launch Python process."));
                    });
                return;
            }

            // Wait for the process to complete
            FPlatformProcess::WaitForProc(ProcHandle);

            // Get the return code
            int32 ReturnCode;
            FPlatformProcess::GetProcReturnCode(ProcHandle, &ReturnCode);

            // Clean up process handle
            FPlatformProcess::CloseProc(ProcHandle);

            // 4) Use the Game Thread to update the UI or print messages
            AsyncTask(ENamedThreads::GameThread, [Context, ReturnCode]()
                {
                    if (ReturnCode != 0)
                    {
                        UKismetSystemLibrary::PrintString(
                            Context,
                            FString::Printf(TEXT("Python error %d"), ReturnCode)
                        );
                    }
                    else
                    {
                        UKismetSystemLibrary::PrintString(Context, TEXT("run.py executed successfully"));
                    }
                });
        });
}