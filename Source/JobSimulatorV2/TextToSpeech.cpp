#include "TextToSpeech.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "Kismet/KismetSystemLibrary.h"

ATextToSpeech::ATextToSpeech()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATextToSpeech::AnalyzeText(UObject* Context, UPARAM(ref)FString& Text)
{
    // 1) Get script path
    const FString ProjectRoot = FPaths::ProjectDir();                  // …\JobSimulator
    const FString ScriptDir = FPaths::Combine(ProjectRoot, TEXT("F5-TTS"));
    const FString ScriptPath = FPaths::Combine(ScriptDir, TEXT("run.py"));

    // 2) Escape the text for command line (wrap in quotes, escape existing quotes)
    FString EscapedText = Text.Replace(TEXT("\""), TEXT("\\\""));
    FString FullCommand = FString::Printf(TEXT("\"%s\" \"%s\""), *ScriptPath, *EscapedText);

    // 3) Run Python with the text argument
    int32 ReturnCode;
    FString StdOut, StdErr;

    bool bSuccess = FPlatformProcess::ExecProcess(
        TEXT("python"),       // "python" must be in PATH
        *FullCommand,         // e.g., "run.py" "Hello, world!"
        &ReturnCode,
        &StdOut,
        &StdErr,
        *ScriptDir            // Working directory (where run.py is)
    );

    // 4) Report back
    if (!bSuccess)
    {
        UKismetSystemLibrary::PrintString(Context, TEXT("Failed to launch python."));
    }
    else if (ReturnCode != 0)
    {
        UKismetSystemLibrary::PrintString(
            Context,
            FString::Printf(TEXT("Python error %d:\n%s"), ReturnCode, *StdErr)
        );
    }
    else
    {
        UKismetSystemLibrary::PrintString(Context, TEXT("run.py executed successfully"));
    }
}