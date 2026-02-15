<img width="3508" height="4967" alt="NVIDIA Poster (1)" src="https://github.com/user-attachments/assets/0f478a7c-049d-4863-b771-5abe3268d0d3" />

[![Unreal Engine 5](https://img.shields.io/badge/Unreal_Engine_5-313131?logo=unrealengine&logoColor=white)](https://www.unrealengine.com)
[![NVIDIA](https://img.shields.io/badge/NVIDIA-76B900?logo=nvidia&logoColor=white)](https://developer.nvidia.com)
[![Llama 2](https://img.shields.io/badge/Llama_2-000?logo=meta&logoColor=white)](https://ai.meta.com/llama/)
[![OpenAI Whisper](https://img.shields.io/badge/Whisper-000?logo=openai&logoColor=white)](https://openai.com/research/whisper)

---

## 🌟 Overview  
Players solve real coding challenges delivered as narrative emails from AI-driven NPCs, converse naturally via voice/text chat, and navigate a dynamic tech workplace.

---

## ⚙️ Core Systems  

| System | Tech Stack | What It Does |
|--------|------------|--------------|
| **Task Pipeline** | LeetCode API → Llama 2 (7B/13B) | Pulls coding problems & rewrites them as in-game emails from CEO/manager NPCs |
| **NPC Brains** | UE5 Behavior Trees + Blackboard | Randomized daily schedules (Work/Eat/Rest/Meetings) with priority interrupts based on time/energy/task load |
| **Voice Chat** | Whisper.cpp → F5-TTS | Player speaks → transcribed → sent to LLM → NPC replies via realistic TTS with 3D spatial audio |
| **Face Animation** | NVIDIA Audio2Face → LiveLink | TTS audio drives MetaHuman blendshapes in real-time for cinematic lip-sync & expressions |
| **World Sim** | UE5 NavMesh + Simulated Clock | NPCs autonomously navigate office spaces based on dynamic behavior trees |

---

## 💬 How Player ↔ NPC Chat Works  

👇 **Text or Voice Input**  
↓  
🗣️ **Whisper.cpp** transcribes speech → text  
↓  
🧠 **Game Engine** bundles context:  
 `{player_msg + npc_state + task_progress + relationship}`  
↓  
🤖 **Local LLM** generates narrative NPC response  
↓  
🔊 **F5-TTS** converts text → MP3 audio stream  
↓  
🎭 **NVIDIA Audio2Face** generates blendshape animation from audio  
↓  
👤 **UE5 + MetaHuman** plays 3D audio + live facial animation via LiveLink  

---

## 🚀 Quick Start *(Coming Soon)*  

> ✨ **X** One-click installer (Windows/Linux) for LLM + Whisper + Audio2Face setup  
> ✨ **X** Docker Compose config with GPU passthrough  
> ✨ **X** Pre-built binaries with embedded quantized LLMs (GGUF format)

### Requirements  
| Component | Minimum | Recommended |
|-----------|---------|-------------|
| GPU | GTX 1660 | **RTX 3060+** (for real-time Audio2Face) |
| RAM | 16 GB | 32 GB |
| Storage | 20 GB free | 50 GB SSD |
| OS | Win 10 / Ubuntu 22.04+ | Win 11 / Ubuntu 24.04 |
| Engine | **Unreal Engine 5.6+** | **Unreal Engine 5.6+** |

---

## 🌈 Planned Features  

| Priority | Feature | Description |
|----------|---------|-------------|
| ⭐ | **NPC-to-NPC Interaction** | NPCs converse with each other, share task updates, and react to player progress organically |
| ⭐ | **Working Collaboration Workflows** | Players and NPCs jointly debug code, review PRs, and solve multi-stage challenges in shared virtual workspaces |

---

## 📚 References  

1. Unreal Engine. Epic Games, Inc. [Online] https://www.unrealengine.com
2. MetaHuman. Epic Games, Inc. [Online] https://www.unrealengine.com/metahuman
3. Touvron, H., et al. (2023). Llama 2: Open Foundation and Fine-Tuned Chat Models. arXiv:2307.09288.
4. Radford, A., et al. (2022). Robust Speech Recognition via Large-Scale Weak Supervision. Proceedings of the 40th International Conference on Machine Learning.
5. NVIDIA Audio2Face. NVIDIA Corporation. [Online] https://developer.nvidia.com/audio2face
6. LeetCode. LeetCode. [Online] https://leetcode.com 

---
 
© 2026 Nicholas Wilson Kurniawan
