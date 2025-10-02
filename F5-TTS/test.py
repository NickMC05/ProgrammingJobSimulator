import sys
sys.path.append('./F5-TTS')

import torch
import soundfile as sf
from f5_tts import F5TTS

# Initialize the model
model = F5TTS()

# Generate audio for "hi there"
text = "hi there"
audio = model.generate(text)

# Save the audio
sf.write("hi_there.wav", audio, samplerate=24000)
print("Audio saved as 'hi_there.wav'")