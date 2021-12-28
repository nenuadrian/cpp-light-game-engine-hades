#pragma once

class SoundManager {
public:
	SoundManager();
	void play();
	static void PlayThread(SoundManager* soundManager);
};

