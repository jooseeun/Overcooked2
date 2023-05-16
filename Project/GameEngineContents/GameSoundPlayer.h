#pragma once


class GameSoundPlayer
{
public:
	static std::shared_ptr<GameSoundPlayer> BgmPlayer_;
	static std::shared_ptr<GameSoundPlayer> EffectPlayer_;

	GameSoundPlayer();
	~GameSoundPlayer();

	GameSoundPlayer(const GameSoundPlayer& _Other) = delete;
	GameSoundPlayer(GameSoundPlayer&& _Other) noexcept = delete;
	GameSoundPlayer& operator=(const GameSoundPlayer& _Other) = delete;
	GameSoundPlayer& operator=(GameSoundPlayer&& _Other) noexcept = delete;

public:
	inline std::string GetBgmName()
	{
		return BgmName_;
	}

	inline float GetVolume()
	{
		return Volume_;
	}

	void SetBgmVolume(float _Value)
	{
		Volume_ = _Value;
		SoundPlayer_Bgm_.Volume(_Value);
	}

	void SetEffectVolume(float _Value)
	{
		Volume_ = _Value;
		SoundPlayer_Effect_.Volume(_Value);
	}

	void BgmStop()
	{
		SoundPlayer_Bgm_.Stop();
	}

	void EffectStop()
	{
		SoundPlayer_Effect_.Stop();
	}


public:
	void Destroy()
	{
		if (BgmPlayer_ != nullptr)
		{
			BgmPlayer_.reset();
			BgmPlayer_ = nullptr;
		}

		if (EffectPlayer_ != nullptr)
		{
			EffectPlayer_.reset();
			EffectPlayer_ = nullptr;
		}
	}

	void ChangeBgm(std::string _BgmName, unsigned int _LoopCount = -1);
	void ChangeEffect(std::string _BgmName, unsigned int _LoopCount = -1);


private:
	GameEngineSoundPlayer SoundPlayer_Bgm_;
	GameEngineSoundPlayer SoundPlayer_Effect_;

private:
	std::string BgmName_;
	float Volume_;
};

