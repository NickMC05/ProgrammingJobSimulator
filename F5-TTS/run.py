import subprocess
from pathlib import Path

# 1) Locate the directory of this script:
script_dir = Path(__file__).resolve().parent

# 2) Walk up until you find the F5-TTS-main folder
def find_tts_root(start: Path, marker: str = "F5-TTS-main") -> Path:
    for p in (start, *start.parents):
        candidate = p / marker
        if candidate.is_dir():
            return candidate
    raise FileNotFoundError(f"couldn't find '{marker}' above {start!r}")

tts_root = find_tts_root(script_dir)

# 3) Build the relative path to the .wav
ref_audio = (
    tts_root
    / "src"
    / "f5_tts"
    / "infer"
    / "examples"
    / "basic"
    / "basic_ref_en.wav"
)

# 4) Now your command stays short
command = [
    "f5-tts_infer-cli",
    "--model",    "F5TTS_v1_Base",
    "--ref_audio", str(ref_audio),
    "--gen_text",  "Hi, I am Nick."
]

# 5) Run it
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