# test_models.py
import sys
import os

try:
    from models.f5_tts import F5TTS
    model = F5TTS()
    print("✓ Success with models.f5_tts.F5TTS")
except ImportError as e:
    print(f"✗ models.f5_tts import failed: {e}")

try:
    from models import F5TTS
    model = F5TTS()
    print("✓ Success with models.F5TTS")
except ImportError as e:
    print(f"✗ models import failed: {e}")

try:
    from f5_tts.models import F5TTS
    model = F5TTS()
    print("✓ Success with f5_tts.models.F5TTS")
except ImportError as e:
    print(f"✗ f5_tts.models import failed: {e}")