import subprocess
import sys
import os

def run_f5_tts(gen_text):
    # Define the command and arguments
    command = [
        sys.executable,  # Use the current Python executable
        os.path.join("F5-TTS-main", "src", "f5_tts", "infer", "infer_cli.py"),
        "--model", "F5TTS_v1_Base",
        "--ref_audio", os.path.join(".", "F5-TTS-main", "audio-references", "basic_ref_en.wav"),
        "--ref_text", "Some call me nature. Others call me mother nature.",
        "--gen_text", gen_text
    ]

    # Set environment variable to disable oneDNN optimizations (from previous log)
    os.environ["TF_ENABLE_ONEDNN_OPTS"] = "0"

    try:
        # Run the command
        result = subprocess.run(
            command,
            check=True,
            text=True,
            capture_output=True
        )
        print("Command executed successfully!")
        print("Output:", result.stdout)
    except subprocess.CalledProcessError as e:
        print("Error running command:", e)
        print("Error output:", e.stderr)
    except FileNotFoundError:
        print("Error: Python executable or script not found. Ensure the paths are correct and dependencies are installed.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

if __name__ == "__main__":
    # Get the text from command line arguments
    if len(sys.argv) < 2:
        print("Usage: python script.py \"text to synthesize\"")
        sys.exit(1)
    
    user_gen_text = sys.argv[1]
    print(f"Generating speech for: {user_gen_text}")
    run_f5_tts(user_gen_text)