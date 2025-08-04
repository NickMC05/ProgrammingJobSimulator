import sys
sys.path.append('third_party/Matcha-TTS')
from cosyvoice.cli.cosyvoice import CosyVoice2
from cosyvoice.utils.file_utils import load_wav
import torchaudio

# Initialize CosyVoice2
cosyvoice = CosyVoice2('pretrained_models/CosyVoice2-0.5B', load_jit=False, load_trt=False, load_vllm=False, fp16=False)

# Synthesize the target text and save as output.wav
text = "Hi, I am Nick. Nice to meet you"
prompt_speech_16k = load_wav('./asset/zero_shot_prompt.wav', 16000)
for i, j in enumerate(cosyvoice.inference_zero_shot(text, '希望你以后能够做的比我还好呦。', prompt_speech_16k, stream=False)):
    torchaudio.save('output_test_2_{}.wav'.format(i), j['tts_speech'], cosyvoice.sample_rate)