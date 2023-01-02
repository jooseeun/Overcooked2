#pragma once

// Ό³Έν :
class GameBgmPlayer
{
public:
	static std::shared_ptr<GameBgmPlayer> BgmPlayer_;
	static std::shared_ptr<GameBgmPlayer> EffectBgmPlayer_;

	GameBgmPlayer();
	~GameBgmPlayer();

	GameBgmPlayer(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer(GameBgmPlayer&& _Other) noexcept = delete;
	GameBgmPlayer& operator=(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer& operator=(GameBgmPlayer&& _Other) noexcept = delete;


public:
	void BgmStop()
	{
		SoundPlayer_.Stop();
	}

	void EffectBgmStop()
	{
		EffectSoundPlayer_.Stop();
	}

	void ChangeBgm(std::string _BgmName, unsigned int _LoopCount = -1)
	{
		SoundPlayer_.Stop();
		SoundPlayer_ = GameEngineSound::SoundPlayControl(_BgmName, _LoopCount);
	}

	void ChangeEffectBgm(std::string _BgmName, unsigned int _LoopCount = -1)
	{
		EffectSoundPlayer_.Stop();
		EffectSoundPlayer_ = GameEngineSound::SoundPlayControl(_BgmName, _LoopCount);
	}

	void Destroy()
	{
		if (BgmPlayer_ != nullptr)
		{
			BgmPlayer_.reset();
			BgmPlayer_ = nullptr;
		}

		if (EffectBgmPlayer_ != nullptr)
		{
			EffectBgmPlayer_.reset();
			EffectBgmPlayer_ = nullptr;
		}
	}

protected:

private:
	GameEngineSoundPlayer SoundPlayer_;
	GameEngineSoundPlayer EffectSoundPlayer_;
};

