#pragma once

// Ό³Έν :
class GameBgmPlayer
{
public:
	static std::shared_ptr<GameBgmPlayer> BgmPlayer_;

	GameBgmPlayer();
	~GameBgmPlayer();

	GameBgmPlayer(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer(GameBgmPlayer&& _Other) noexcept = delete;
	GameBgmPlayer& operator=(const GameBgmPlayer& _Other) = delete;
	GameBgmPlayer& operator=(GameBgmPlayer&& _Other) noexcept = delete;

	GameEngineSoundPlayer SoundPlayer_;

public:
	void Stop()
	{
		SoundPlayer_.Stop();
	}

	void ChangeBgm(std::string _BgmName, unsigned int _LoopCount = -1)
	{
		SoundPlayer_.Stop();
		SoundPlayer_ = GameEngineSound::SoundPlayControl(_BgmName, _LoopCount);
	}

	void Destroy()
	{
		if (BgmPlayer_ != nullptr)
		{
			BgmPlayer_.reset();
			BgmPlayer_ = nullptr;
		}
	}

protected:

private:

};

