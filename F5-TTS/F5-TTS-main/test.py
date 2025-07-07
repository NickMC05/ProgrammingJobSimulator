import os
import sys

# Add the F5-TTS directory to Python path
f5_tts_path = os.path.join(os.getcwd(), '.')
sys.path.append(f5_tts_path)

# Now try importing
try:
    from F5TTS.tts import F5TTS
    print("Successfully imported F5TTS")
except ImportError as e:
    print(f"Import failed: {e}")
    print("Please check the actual module structure in the F5-TTS directory")

def txt_to_speech(input_txt, output_audio, format='mp3', voice='default'):
    """
    Convert text file to speech audio file using F5-TTS
    
    Parameters:
    - input_txt: Path to input text file
    - output_audio: Path for output audio file (include .mp3 or .wav extension)
    - format: 'mp3' or 'wav'
    - voice: Voice model to use (check F5-TTS docs for available voices)
    """
    
    # Initialize TTS engine
    tts = F5TTS()
    
    # Read text from file
    with open(input_txt, 'r', encoding='utf-8') as file:
        text = file.read()
    
    # Generate speech
    audio = tts.synthesize(text, voice=voice)
    
    # Save to file
    if format.lower() == 'mp3':
        audio.export(output_audio, format='mp3')
    elif format.lower() == 'wav':
        audio.export(output_audio, format='wav')
    else:
        raise ValueError("Unsupported format. Use 'mp3' or 'wav'")

# Example usage
if __name__ == "__main__":
    # Input and output paths
    input_file = "input.txt"
    output_file = "output.mp3"  # or "output.wav"
    
    # Convert text to speech
    txt_to_speech(input_file, output_file, format='mp3', voice='default')
    
    print(f"Successfully converted {input_file} to {output_file}")