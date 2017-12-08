#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;

SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::loadSound(HWND hWnd)
{
	// Khởi tạo CSoundManager.
	DirectSound_Init(hWnd);

	CSound* sound = nullptr;

	sound = LoadSound("Resources//Sounds//intro_scene.wav");
	_listSound[eSoundID::INTRO_SCENE] = sound;

	sound = LoadSound("Resources//Sounds//play_scene.wav");
	_listSound[eSoundID::PLAY_SCENE] = sound;

	sound = LoadSound("Resources//Sounds//victory_scene.wav");
	_listSound[eSoundID::VICTORY_SCENE] = sound;

	sound = LoadSound("Resources//Sounds//player_jump.wav");
	_listSound[eSoundID::PLAYER_JUMP] = sound;

	sound = LoadSound("Resources//Sounds//player_be_hit.wav");
	_listSound[eSoundID::PLAYER_BE_HIT] = sound;

	sound = LoadSound("Resources//Sounds//player_die.wav");
	_listSound[eSoundID::PLAYER_DIE] = sound;

	sound = LoadSound("Resources//Sounds//normal_bullet_fire.wav");
	_listSound[eSoundID::NORMAL_BULLET_FIRE] = sound;

	sound = LoadSound("Resources//Sounds//ice_bullet_fire.wav");
	_listSound[eSoundID::ICE_BULLET_FIRE] = sound;

	sound = LoadSound("Resources//Sounds//missile_rocket_fire.wav");
	_listSound[eSoundID::MISSILE_ROCKET_FIRE] = sound;

	sound = LoadSound("Resources//Sounds//bomb_set.wav");
	_listSound[eSoundID::BOMB_SET] = sound;
}

bool SoundManager::IsPlaying(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}

void SoundManager::Play(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		PlaySound(sound);
	}
}

void SoundManager::PlayLoop(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}

void SoundManager::Stop(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}
