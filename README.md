<img width="3508" height="4967" alt="NVIDIA Poster (1)" src="https://github.com/user-attachments/assets/0f478a7c-049d-4863-b771-5abe3268d0d3" />

Job Task System:
- Game pulls tasks from a LeetCode database.
- Unreal Engine parses and sends the problem to a local LLM.
- The LLM reformats it into a narrative in-game email from a CEO or manager.

NPC Behavior Details:
- NPCs controlled by Behavior Trees and Blackboards.
- Game runs on a simulated clock.
- NPCs have randomized daily schedules (Work, Rest, Eat, etc.). Schedules are behavior trees with weighted selectors for variability.
- Scheduling uses Selectors and Sequences to pick activities (Work, Rest, Eat, Meeting, Home) based on time, energy, and task load.
- Randomization is added with decorators using probability checks.
- Priority System uses a high-priority service node to interrupt the current task for urgent activities.
- Pathfinding uses UE5’s NavMesh system.

How does Player-to-NPC-to-Player Communication Work?
- Type Chat: Press a hotkey ('T') to open a text box. Submitted text goes to the dialogue system.
- Or, Voice Chat: UE5 captures audio. A local Python script uses OpenAI's Whisper to convert speech to text, which is then sent to the dialogue system.
- Player input and game context (NPC, task, relationship) are sent to a local LLM. The LLM generates a contextual NPC response, which is returned to the game.
- NPC text responses are sent to a local TTS server (F5-TTS) to generate MP3 audio. The audio is streamed and played in-game as a 3D sound source attached to the NPC.
- The TTS audio is streamed to NVIDIA Audio2Face. Audio2Face generates a real-time blendshape animation stream. Unreal Engine receives this via LiveLink, driving the MetaHuman facial animation for lip-syncing.

References:
1. Unreal Engine. Epic Games, Inc. [Online] https://www.unrealengine.com 
2. MetaHuman. Epic Games, Inc. [Online] https://www.unrealengine.com/metahuman 
3. Touvron, H., et al. (2023). Llama 2: Open Foundation and Fine-Tuned Chat Models. arXiv:2307.09288.
4. Radford, A., et al. (2022). Robust Speech Recognition via Large-Scale Weak Supervision. Proceedings of the 40th International Conference on Machine Learning.
5. NVIDIA Audio2Face. NVIDIA Corporation. [Online] https://developer.nvidia.com/audio2face 
6. LeetCode. LeetCode. [Online] https://leetcode.com
