#include "Music.h"
#include "Core.h"
#include <SDL_mixer.h>

#include "ResourceManager.h"
#include "Utillities/Debug_Log.h"
#include "Utillities/Zipper.h"


ArksEngine::Music::Music(ArksEngine::Core* pOwner, const char* fileName)
	:m_pOwner(pOwner)
	,m_pFileName(fileName)
{
}

ArksEngine::Music::~Music()
= default;

void ArksEngine::Music::Load_Music()
{
	const std::vector<char>& resourceData = m_pOwner->GetResourceManager()->GetResource(m_pFileName);

	SDL_RWops* rwops = SDL_RWFromConstMem(resourceData.data(), resourceData.size());
	Mix_Music* pMusic = Mix_LoadMUSType_RW(rwops, MUS_MP3, SDL_TRUE); // SDL_TRUE to automatically close the RWops

	// Check to see if load was successful
	if (pMusic == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Music failed to load" + std::string(Mix_GetError()));
		return;
	}

	m_pMusic = pMusic;


}

void ArksEngine::Music::Load_SoundEffect()
{

	const std::vector<char>& resourceData = m_pOwner->GetResourceManager()->GetResource(m_pFileName);

	SDL_RWops* rwops = SDL_RWFromConstMem(resourceData.data(), resourceData.size());
	Mix_Chunk* pChunk = Mix_LoadWAV_RW(rwops, SDL_TRUE); // SDL_TRUE to automatically close the RWops

	// Check to see if load was successful
	if (pChunk == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Sound Effect failed to load");
	}

	m_pSoundEffect = pChunk;

	// Free pMusic
	Mix_FreeChunk(pChunk);
}

void ArksEngine::Music::Play_Music(int loops) const
{
	if (m_pMusic == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Failed to play music, Tip: Did you load it first?");
		return;
	}

	Mix_PlayMusic(m_pMusic, loops);

	if (!Mix_PlayingMusic())
	{
		// Print some debug information to help diagnose the issue
		std::string error = Mix_GetError();
		std::string message = "Failed to play music: " + error;
		m_pOwner->GetDebug_Log()->Error(message);

		// Print additional debug information about the state of the audio system
		int numChannels = Mix_AllocateChannels(-1);
		int numPlaying = Mix_Playing(-1);
		int numPaused = Mix_Paused(-1);
		int volume = Mix_VolumeMusic(-1);
		message = "Channels: " + std::to_string(numChannels) + ", Playing: " + std::to_string(numPlaying) + ", Paused: " + std::to_string(numPaused) + ", Volume: " + std::to_string(volume);
		m_pOwner->GetDebug_Log()->Error(message);

		return;
	}

}

void ArksEngine::Music::Play_SoundEffect(int loops, int channel) const
{

	if (m_pSoundEffect == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Failed to play sound effect, Tip: Did you load it first?");
		return;
	}

	Mix_PlayChannel(channel, m_pSoundEffect, loops);
}

void ArksEngine::Music::Stop_Music()
{
	Mix_HaltMusic();
}

void ArksEngine::Music::Set_MusicVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void ArksEngine::Music::Set_SoundEffectVolume(int volume) const
{
	if (m_pSoundEffect == nullptr)
	{
		m_pOwner->GetDebug_Log()->Error("Failed to find sound effect, Tip: Did you load it first?");
		return;
	}

	Mix_VolumeChunk(m_pSoundEffect, volume);
}

