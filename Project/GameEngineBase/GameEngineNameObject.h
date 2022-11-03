#pragma once
#include <string>

// Ό³Έν :
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	virtual ~GameEngineNameObject();

	inline void SetName(const std::string& _Name) 
	{
		ObjectName_ = _Name;
	}

	std::string_view GetName() const
	{
		return ObjectName_;
	}

	std::string GetNameCopy() const
	{
		return ObjectName_;
	}

protected:

private:
	std::string ObjectName_;

};

