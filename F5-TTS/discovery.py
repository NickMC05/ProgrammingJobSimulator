# discovery.py
import os
import importlib.util

def explore_repo():
    print("=== F5-TTS Repository Exploration ===")
    
    # List all files
    print("\n📁 All files in F5-TTS:")
    for item in os.listdir('.'):
        if item.endswith('.py') or item in ['models', 'configs', 'utils']:
            print(f"  - {item}")
    
    # Check f5_tts.py specifically
    if os.path.exists('f5_tts.py'):
        print("\n📄 Contents of f5_tts.py:")
        with open('f5_tts.py', 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()[:20]  # First 20 lines
            for i, line in enumerate(lines):
                print(f"  {i+1:3}: {line.rstrip()}")
    
    # Check what's importable from f5_tts
    print("\n🔍 Checking f5_tts module:")
    try:
        import f5_tts
        print("✓ Successfully imported f5_tts")
        print("Available attributes:", [x for x in dir(f5_tts) if not x.startswith('_')])
    except Exception as e:
        print(f"✗ Import failed: {e}")

if __name__ == "__main__":
    explore_repo()