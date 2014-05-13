#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "../pch.h"

class AudioManager
{
public:
	static AudioManager& Instance()
	{
		static AudioManager instance;
		return instance;
	}
	~AudioManager();
	void FreeResource();
	
	void LoadMusic(std::string name);
	void LoadSFX(std::string name);

	void PlayMusic(std::string name);
	void PauseMusic();
	void StopMusic();

	void PlaySFX(std::string name);
private:
	AudioManager();
	AudioManager( const AudioManager& other ){};
	AudioManager& operator=( const AudioManager& rhs ){};
	void LoadAudioAssets();
	std::map<std::string, Mix_Music*> mAudioMusicMap;
	std::map<std::string, Mix_Chunk*> mSfxMusicMap;

};

#endif