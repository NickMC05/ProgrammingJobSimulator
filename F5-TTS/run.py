import subprocess
import sys
from pathlib import Path

def main():
    # 1) Get the text passed from Unreal (command line argument)
    if len(sys.argv) < 2:
        print("Error: No text provided. Usage: python run.py \"Your text here\"")
        sys.exit(1)
    user_text = sys.argv[1]

    # 2) Locate the directory of this script:
    script_dir = Path(__file__).resolve().parent

    # 3) Walk up until you find the F5-TTS-main folder
    def find_tts_root(start: Path, marker: str = "F5-TTS-main") -> Path:
        for p in (start, *start.parents):
            candidate = p / marker
            if candidate.is_dir():
                return candidate
        raise FileNotFoundError(f"couldn't find '{marker}' above {start!r}")

    tts_root = find_tts_root(script_dir)

    # 4) Build the relative path to the .wav
    ref_audio = (
        tts_root
        / "audio-references"
        / "basic_ref_en.wav"
    )

    # 5) Build command with dynamic text
    command = [
        "f5-tts_infer-cli",
        "--model",    "F5TTS_v1_Base",
        "--ref_audio", str(ref_audio),
        "--gen_text",  user_text  # Using the text from Unreal
    ]

    # 6) Run it
    try:
        result = subprocess.run(
            command,
            check=True,
            text=True,
            capture_output=True,
        )
        print("Command Output:", result.stdout)
    except subprocess.CalledProcessError as e:
        print("ERROR:", e.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()