import sys
import os
import warnings
import torch
from cosyvoice.cli.cosyvoice import CosyVoice
from cosyvoice.utils.file_utils import load_wav
import torchaudio

# Suppress ttsfrd warning if it's non-critical
warnings.filterwarnings("ignore", message="failed to import ttsfrd")

def text_to_speech(
    text,
    output_path="output.wav",
    model_dir="pretrained_models/CosyVoice-ttsfrd",  # Use ttsfrd variant
    prompt_audio_path="./asset/zero_shot_prompt.wav",
    chinese_prompt='希望你以后能够做的比我还好呦。'
):
    try:
        # --- 1. Load Model ---
        print(f"Loading model from: {model_dir}")
        if not os.path.exists(model_dir):
            raise FileNotFoundError(f"Model directory not found: {model_dir}")
        
        cosyvoice = CosyVoice(model_dir)  # Initialize with ttsfrd-based model

        # --- 2. Load Prompt Audio ---
        if not os.path.exists(prompt_audio_path):
            raise FileNotFoundError(f"Prompt audio not found: {prompt_audio_path}")
        
        prompt_audio = load_wav(prompt_audio_path, sample_rate=16000)

        # --- 3. Generate Speech ---
        print(f"Generating speech for: '{text}'")
        result = next(cosyvoice.inference_zero_shot(
            text=text,
            prompt_text=chinese_prompt,  # Required for zero-shot TTS
            prompt_audio=prompt_audio,
            stream=False
        ))

        # --- 4. Save Output ---
        torchaudio.save(output_path, result["tts_speech"], cosyvoice.sample_rate)
        print(f"Success! Output saved to: {output_path}")
        return True

    except Exception as e:
        print(f"Error: {e}")
        return False

if __name__ == "__main__":
    # Example usage
    text_to_speech("Hi, I am Nick. Nice to meet you")