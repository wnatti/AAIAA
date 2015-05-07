#include "Audio.h"
#include "../core/ErrorHandler.h"
#include "../core/ResourceManager.h"

using namespace audio;

Audio::Audio(std::string fileName, core::ResourceManager* resourceManager) : maxPlayerCount(3), playerCount(1)
{
	core::Audio* tempAudioAsset = resourceManager->loadAudio(fileName);
	s2d_assert( (tempAudioAsset != nullptr) );
	player.push_back(new AudioPlayer(tempAudioAsset));
	AudioInitializer::GetInstance()->InitAudioPlayer(player[0]);
}

Audio::~Audio()
{
	for (int i = 0; i < playerCount; i++)
		delete player[i];
}

bool Audio::Play()
{
	AudioPlayer* tempPointer = GetAvailable();
	
	if (tempPointer != nullptr)
	{
		tempPointer->SetPlayState(SL_PLAYSTATE_PLAYING);
		return true;
	}
	else
		return false;
}

void Audio::Stop()
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetPlayState(SL_PLAYSTATE_STOPPED);
}

void Audio::Pause()
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetPlayState(SL_PLAYSTATE_PAUSED);
}

void Audio::SetVolume(float volumeLevel)
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetVolume(volumeLevel);
}

void Audio::SetLooping(bool isEnabled)
{
	for (int i = 0; i < playerCount; i++)
		player[i]->SetLooping(isEnabled);
}

void Audio::SetMaxPlayerCount(unsigned newMaxCount)
{
	if (newMaxCount < maxPlayerCount)
	{
		for (int i = 0; i < playerCount; i++)
		{
			player[i]->SetPlayState(SL_PLAYSTATE_STOPPED);
		}

		s2d_info(("Removing AudioPlayers. Possible loss of data!"));

		for (int i = newMaxCount - 1; i < playerCount; i++)
		{
			delete player[i];
			player.erase(player.begin() + i);
			playerCount--;
		}
	}

	maxPlayerCount = newMaxCount;
}

AudioPlayer* Audio::GetAvailable()
{
	for (int i = 0; i < playerCount; i++)
	{
		SLuint32 temp = player.at(i)->GetPlayState();
		if ( temp == SL_PLAYSTATE_STOPPED )
			return player[i];
	}

	if (playerCount < maxPlayerCount)
	{
		playerCount++;
		player.push_back(new AudioPlayer(player[0]));
		AudioInitializer::GetInstance()->InitAudioPlayer(player[playerCount - 1]);

		return player[playerCount-1];
	}
	else
		return nullptr;
}