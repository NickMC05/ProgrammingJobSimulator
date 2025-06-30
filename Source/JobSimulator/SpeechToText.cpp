#include "SpeechToText.h"
#include "HAL/PlatformProcess.h"
#include "Kismet/KismetSystemLibrary.h"

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

// Function to execute a shell command and return its output
FString ExecuteShellCommand(const FString& Command, const FString& WorkingDirectory = TEXT(""))
{
    void* ReadPipe = nullptr;
    void* WritePipe = nullptr;

    // Create pipes for reading and writing
    FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

    // Execute the command
    FProcHandle ProcessHandle = FPlatformProcess::CreateProc(
        *Command, nullptr, true, false, false, nullptr, 0, *WorkingDirectory, WritePipe);

    FString Output;

    if (ProcessHandle.IsValid())
    {
        // Wait for the command to complete
        while (FPlatformProcess::IsProcRunning(ProcessHandle))
        {
            // Read the pipe content
            Output += FPlatformProcess::ReadPipe(ReadPipe);
        }

        // Close the process handle
        FPlatformProcess::CloseProc(ProcessHandle);
    }

    // Clean up pipes
    FPlatformProcess::ClosePipe(ReadPipe, WritePipe);

    return Output;
}

// AnalyzeAudio function
void ASpeechToText::AnalyzeAudio(UObject* Context)
{
    // Print a test string
    UKismetSystemLibrary::PrintString(Context, "huh");

    // Find the current working directory for Windows or other platforms
    FString Command;
    FString FilePathCommand;

#if PLATFORM_WINDOWS
    FString ExecutablePath = TEXT("cmd.exe");  // Just "cmd.exe" (relies on PATH)
    FString CommandParams = TEXT("/C dir");    // Arguments for cmd.exe

    // Optional: Create pipes if you need output
    void* ReadPipe = nullptr;
    void* WritePipe = nullptr;
    FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

    // Launch the process
    FProcHandle ProcHandle = FPlatformProcess::CreateProc(
        *ExecutablePath,   // Executable (must not include arguments)
        *CommandParams,    // Arguments (must be separate)
        true,              // Launch hidden
        false,             // No minimized window
        false,             // No maximized window
        nullptr,           // Working directory (null = current)
        0,                 // Priority modifier
        nullptr,           // Environment variables
        WritePipe          // Optional write pipe for stdin
    );

    if (!ProcHandle.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to launch cmd.exe"));
    }
    else
    {
        FPlatformProcess::CloseProc(ProcHandle);
    }

    // Clean up pipes if used
    if (ReadPipe)  FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
#endif

    // Execute the directory listing command and get the output
    FString CommandOutput = ExecuteShellCommand(Command);

    // Execute the current file path command and get the output
    FString FilePathOutput = ExecuteShellCommand(FilePathCommand);

    // Print the results
    UKismetSystemLibrary::PrintString(Context, CommandOutput);
    UKismetSystemLibrary::PrintString(Context, FilePathOutput); // Print the current file path
}