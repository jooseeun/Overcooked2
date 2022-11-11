#include "PreCompile.h"
#include "MeshToolLevel.h"
#include "MeshEditorGUI.h"

MeshToolLevel::MeshToolLevel() 
{
}

MeshToolLevel::~MeshToolLevel() 
{
}


void MeshToolLevel::Start()
{
	MeshSelectWindow_ = MeshEditorGUI::CreateGUIWindow<MeshSelectWindow>("MeshSelectWindow", nullptr);
	MeshSelectWindow_->Off();
}

void MeshToolLevel::Update(float _DeltaTime)
{
}

void MeshToolLevel::End()
{
}

void MeshToolLevel::LevelStartEvent()
{
	MeshSelectWindow_->On();
	GetMainCameraActorTransform().SetWorldPosition({2.f, 200.f, -900.f});

}

void MeshToolLevel::LevelEndEvent()
{
	MeshSelectWindow_->Off();
	std::map<std::string, GameEngineLevel*> Levels = GameEngineCore::GetAllLevelRef();

	std::map<std::string, GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> AllRenderer = StartIter->second->GetMainCamera()->GetAllRenderer();
		std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator StartGroupIter = AllRenderer.begin();
		std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>>::iterator EndGroupIter = AllRenderer.end();

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<std::shared_ptr<GameEngineRenderer>>& Group = StartGroupIter->second;
			std::list<std::shared_ptr<GameEngineRenderer>>::iterator GroupStart = Group.begin();
			std::list<std::shared_ptr<GameEngineRenderer>>::iterator GroupEnd = Group.end();

			for (; GroupStart != GroupEnd; ++GroupStart)
			{
				std::shared_ptr<GameEngineFBXRenderer> GameEngineFBXRenderer_ = std::dynamic_pointer_cast<GameEngineFBXRenderer>((*GroupStart));
				if (GameEngineFBXRenderer_ != nullptr)
				{
					GameEngineFBXRenderer_->ChangeLoadMaterial();
				}

			}
		}


	}
}
