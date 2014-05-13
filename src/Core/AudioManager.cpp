#include "AudioManager.h"

AudioManager::AudioManager()
{
	//Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio( 11025, MIX_DEFAULT_FORMAT, 2, 4096 );
	LoadAudioAssets();
}

AudioManager::~AudioManager()
{
	FreeResource();
}

void AudioManager::LoadMusic( std::string name )
{
	
#ifdef WIN32
	Mix_Music * pAudio = Mix_LoadMUS( ("assets\\"+name).c_str() );
#endif
#ifdef __ANDROID__
	Mix_Music * pAudio = Mix_LoadMUS( name.c_str() );
#endif
	mAudioMusicMap.insert(std::pair<std::string,Mix_Music*>(name,pAudio));
}

void AudioManager::LoadSFX( std::string name )
{

#ifdef WIN32
	Mix_Chunk * pAudio = Mix_LoadWAV( ("assets\\"+name).c_str() );
#endif
#ifdef __ANDROID__
	Mix_Chunk * pAudio = Mix_LoadWAV( name.c_str() );
#endif
	mSfxMusicMap.insert(std::pair<std::string,Mix_Chunk*>(name,pAudio));
}

void AudioManager::FreeResource()
{
	for(std::map<std::string,Mix_Music*>::iterator it = mAudioMusicMap.begin(); it != mAudioMusicMap.end();++it)
	{
		Mix_FreeMusic(it->second);
	}
	for(std::map<std::string,Mix_Chunk*>::iterator it = mSfxMusicMap.begin(); it != mSfxMusicMap.end();++it)
	{
		Mix_FreeChunk(it->second);
	}
	Mix_CloseAudio();
}

void AudioManager::LoadAudioAssets()
{
	LoadMusic("The Stage is Set.ogg");
	LoadSFX("scifi_explosion-001.ogg");
}

void AudioManager::PlayMusic( std::string name )
{
	Mix_PlayMusic( mAudioMusicMap[name], -1 );
}

void AudioManager::PauseMusic()
{
	if( 1 == Mix_PausedMusic() )
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::PlaySFX( std::string name )
{
	Mix_PlayChannel( -1, mSfxMusicMap[name], 0 );
}

