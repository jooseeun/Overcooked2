#include "PreCompile.h"
#include "GameEngineInstancing.h"
#include "GameEngineRenderer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineStructuredBuffer.h"

void GameEngineInstancing::InstancingData::Link(const std::string_view& _Name, const void* _Data)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Name.data());
	if (Data.end() == Data.find(UpperName))
	{
		MsgBoxAssertString("�ν��Ͻ̿� �����Ͱ� �������� �ʽ��ϴ� => " + UpperName);
	}

	std::multimap<std::string, const void*>::iterator Start = Data.lower_bound(UpperName);
	std::multimap<std::string, const void*>::iterator End = Data.upper_bound(UpperName);
	for (; Start != End; ++Start)
	{
		Start->second = _Data;
	}
}

void GameEngineInstancing::InstancingData::Init(std::multiset<std::string>& _Set)
{
	for (const std::string& _Name : _Set)
	{
		Data.insert(std::make_pair(_Name, nullptr));
	}
}

size_t GameEngineInstancing::MaxInstancingCount = 100;

GameEngineInstancing::GameEngineInstancing()
{
	// CreateInstancingUnit();
}

std::list<GameEngineInstancing::InstancingData>& GameEngineInstancing::CreateInstancingUnit()
{
	std::list<InstancingData>& NewGroup = Units.emplace_back();
	GameEngineShaderResourcesHelper& Helper = ShaderResources.emplace_back();
	Helper.ShaderCheck(InitUnit->GetMaterial()->GetVertexShader()->GetInstancingShader());

	std::shared_ptr<GameEngineInstancingBuffer>& BufferPtr = InstancingBuffer.emplace_back();

	std::vector<char>& BufferData = InstancingBufferData.emplace_back();

	Helper.ShaderCheck(InitUnit->GetMaterial()->GetVertexShader()->GetInstancingShader());

	unsigned int size = static_cast<unsigned int>(InitUnit->GetMesh()->GetLayOutDesc().InstancingSize);
	BufferPtr = GameEngineInstancingBuffer::Create(MaxInstancingCount, size);

	BufferData.resize(MaxInstancingCount * BufferPtr->GetDataSize());

	std::multimap<std::string, GameEngineStructuredBufferSetter>& StructuredBuffers	= Helper.GetStructuredBufferSettingMap();

	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator Start = StructuredBuffers.begin();
	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator End = StructuredBuffers.end();
	for (; Start != End; ++Start)
	{
		if (std::string::npos != Start->first.find("INST_"))
		{
			Start->second.Res = GameEngineStructuredBuffer::Create(Start->second.Res->GetShaderDesc(), static_cast<int>(MaxInstancingCount));
			Start->second.Resize(MaxInstancingCount);
			Start->second.Bind();
		}
	}

	if (StructuredBufferSet.empty())
	{
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator Start = StructuredBuffers.begin();
		std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator End = StructuredBuffers.end();
		for (; Start != End; ++Start)
		{
			if (std::string::npos != Start->first.find("INST_"))
			{

				StructuredBufferSet.insert(Start->first);
			}
		}
	}

	return NewGroup;
}

GameEngineInstancing::~GameEngineInstancing()
{
}

void GameEngineInstancing::RenderInstancing(float _DeltaTime)
{
	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator SetterStart;
	std::multimap<std::string, GameEngineStructuredBufferSetter>::iterator SetterEnd;
	for (size_t instancingGroupIndex = 0; instancingGroupIndex < Units.size(); instancingGroupIndex++)
	{
		std::list<InstancingData>& Group = Units[instancingGroupIndex];

		GameEngineShaderResourcesHelper& ShaderResource = ShaderResources[instancingGroupIndex];

		std::multimap<std::string, GameEngineStructuredBufferSetter>& StructuredBuffers	= ShaderResource.GetStructuredBufferSettingMap();

		std::shared_ptr<GameEngineInstancingBuffer> Buffer = InstancingBuffer[instancingGroupIndex];

		std::vector<char>& Data = InstancingBufferData[instancingGroupIndex];

		int Count = 0;

		int* Ptr = reinterpret_cast<int*>(&Data[0]);

		for (InstancingData& Data : Group)
		{
			std::map<std::string, const void*>::iterator DataStart = Data.Data.begin();
			std::map<std::string, const void*>::iterator DataEnd = Data.Data.end();
			for (; DataStart != DataEnd; ++DataStart)
			{
				SetterStart = StructuredBuffers.lower_bound(DataStart->first);
				SetterEnd = StructuredBuffers.upper_bound(DataStart->first);

				for (; SetterStart != SetterEnd; ++SetterStart)
				{
					char* DataPtr = &SetterStart->second.OriginalData[Count * SetterStart->second.Size];
					size_t DataSize = SetterStart->second.Size;

					memcpy_s(DataPtr, SetterStart->second.Size, DataStart->second, DataSize);
				}
			}

			*Ptr = Count;
			++Count;
			Ptr += 1;
		}

		Buffer->ChangeData(&Data[0], Data.size());
		ShaderResource.AllResourcesSetting();
		InitUnit->RenderInstancing(_DeltaTime, Group.size(), Buffer);
	}

	for (size_t instancingGroupIndex = 0; instancingGroupIndex < Units.size(); instancingGroupIndex++)
	{
	}

	int a = 0;
}

void GameEngineInstancing::PushUnit(std::shared_ptr<GameEngineRenderUnit> _Unit, std::function<void(InstancingData&)> _Function)
{
	if (nullptr == InitUnit)
	{
		InitUnit = _Unit;

		if (false == InitUnit->GetMaterial()->GetVertexShader()->IsInstancing())
		{
			MsgBoxAssert("�ν��Ͻ̿� ���׸����� �ƴմϴ�.");
		}

		CreateInstancingUnit();
	}

	_Unit->Off();

	if (false == _Unit->GetMaterial()->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("�ν��Ͻ̿� ���׸����� ������ ���� ����Ʈ �Դϴ�");
	}

	bool Push = false;
	for (size_t i = 0; i < Units.size(); i++)
	{
		if (MaxInstancingCount <= Units[i].size())
		{
			continue;
		}

		Push = true;
		InstancingData NewData = { _Unit };

		NewData.Init(StructuredBufferSet);

		_Function(NewData);

		Units[i].push_back(NewData);
	}

	if (false == Push)
	{
		std::list<InstancingData>& Insert = CreateInstancingUnit();

		InstancingData NewData = { _Unit };

		NewData.Init(StructuredBufferSet);

		_Function(NewData);

		Insert.push_back(NewData);
	}
}

