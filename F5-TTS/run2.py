import subprocess
import sys
from pathlib import Path
from playsound import playsound

def main():
    # 1) Get the text passed from Unreal (command line argument)
    if len(sys.argv) < 2:
        print("Error: No text provided. Usage: python run.py \"Your text here\"")
        sys.exit(1)
    user_text = sys.argv[1]

    # 2) Locate the directory of this script:
    script_dir = Path(__file__).resolve().parent

    # 3) Walk up until you find the F5-TTS folder (not F5-TTS-main)
    def find_tts_root(start: Path, marker: str = "F5-TTS") -> Path:
        for p in (start, *start.parents):
            candidate = p / marker
            if candidate.is_dir():
                return candidate
        raise FileNotFoundError(f"couldn't find '{marker}' above {start!r}")

    tts_root = find_tts_root(script_dir)

    # 4) Build the relative path to the .wav
    ref_audio = (
        tts_root
        / "F5-TTS-main"  # Add this part here
        / "audio-references"
        / "basic_ref_en.wav"
    )

    # 5) Build command with dynamic text
    command = [
        "python src/f5_tts/infer/infer_cli.py",
        "--model", "F5TTS_v1_Base",
        "--ref_audio", str(ref_audio),
        "--ref_text", "Some call me nature. Others call me mother nature.",
        "--gen_text",  user_text
    ]
    print("command:")
    print(command)
    print()

    # 6) Run it
    try:
        result = subprocess.run(
            command,
            check=True,
            text=True,
            capture_output=True,
        )
        print("Command Output:", result.stdout)

        # Get the generated audio file path
        # The correct path is in F5-TTS/tests/ not F5-TTS/F5-TTS-main/tests/
        generated_audio = tts_root / "tests" / "infer_cli_basic.wav"
        
        # Verify the file exists
        if not generated_audio.exists():
            print(f"Error: Generated audio file not found at {generated_audio}")
            sys.exit(1)
            
        print(f"Playing generated audio from: {generated_audio}")
        
        # 7) Play the generated audio
        playsound(str(generated_audio))

    except subprocess.CalledProcessError as e:
        print("ERROR:", e.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()