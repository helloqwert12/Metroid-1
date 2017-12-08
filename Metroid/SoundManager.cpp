#include "SoundManager.h"

SoundManager* SoundManager::_instance = nullptr;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

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

	sound = LoadSound("Resources//Sounds//fire_normal_bullet.wav");
	_listSound[eSoundID::FIRE_NORMAL_BULLET] = sound;

	sound = LoadSound("Resources//Sounds//fire_ice_bullet.wav");
	_listSound[eSoundID::FIRE_ICE_BULLET] = sound;

	sound = LoadSound("Resources//Sounds//fire_missile_rocket.wav");
	_listSound[eSoundID::FIRE_MISSILE_ROCKET] = sound;

	sound = LoadSound("Resources//Sounds//set_bomb.wav");
	_listSound[eSoundID::SET_BOMB] = sound;

	sound = LoadSound("Resources//Sounds//get_energy_tank.wav");
	_listSound[eSoundID::GET_ENERGY_TANK] = sound;

	sound = LoadSound("Resources//Sounds//get_energy_ball.wav");
	_listSound[eSoundID::GET_ENERGY_BALL] = sound;

	sound = LoadSound("Resources//Sounds//get_missile_rocket_ball.wav");
	_listSound[eSoundID::GET_MISSILE_ROCKET_BALL] = sound;

	sound = LoadSound("Resources//Sounds//hit_enemy.wav");
	_listSound[eSoundID::HIT_ENEMY] = sound;

	sound = LoadSound("Resources//Sounds//hit_ripper.wav");
	_listSound[eSoundID::HIT_RIPPER] = sound;

	sound = LoadSound("Resources//Sounds//hit_mother_brain.wav");
	_listSound[eSoundID::HIT_MOTHER_BRAIN] = sound;

	sound = LoadSound("Resources//Sounds//explosion_sound.wav");
	_listSound[eSoundID::EXPLOSION_SOUND] = sound;
}

void SoundManager::play(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		PlaySound(sound);
	}
}

void SoundManager::stop(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

void SoundManager::playLoop(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}

bool SoundManager::isPlaying(eSoundID soundId)
{
	auto sound = _listSound[soundId];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}
