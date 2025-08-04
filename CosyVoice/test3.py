import sys
from cosyvoice.cli.cosyvoice import CosyVoice2
import torchaudio
import time

# Initialize the CosyVoice2 model
model_path = "pretrained_models/CosyVoice2-0.5B"
cosyvoice = CosyVoice2(model_path, load_jit=False, load_trt=False, fp16=False)

# Input text for TTS
input_text = "Hi, I am Nick"

# Output file
output_file = "output.wav"

# Start timing for latency measurement
start_time = time.time()

# Perform TTS inference
for i, result in enumerate(
    cosyvoice.inference_zero_shot(
        input_text,  # The text to convert
        "",          # An empty string as the second parameter for optional text continuation
        None,        # No zero-shot prompt audio
        stream=False # Disable streaming for simplicity
    )
):
    # Save the output audio
    torchaudio.save(output_file, result["tts_speech"], cosyvoice.sample_rate)

# End timing
end_time = time.time()

# Print the runtime
print(f"TTS completed. Output saved to {output_file}. Runtime: {end_time - start_time:.2f} seconds.")