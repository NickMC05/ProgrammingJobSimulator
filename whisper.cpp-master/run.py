import subprocess

# Run the command and wait for completion
result = subprocess.run(
    ["./build/bin/Release/whisper-cli", "-otxt", "./samples/jfk.mp3"],
    capture_output=True,
    text=True
)

# Print the output
print("STDOUT:", result.stdout)
if result.stderr:
    print("STDERR:", result.stderr)