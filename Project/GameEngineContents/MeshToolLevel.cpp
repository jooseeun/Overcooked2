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
	std::map<std::string, class GameEngineLevel*> Levels = GameEngineCore::GetAllLevelRef();

	std::map<std::string, class GameEngineLevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class GameEngineLevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		std::map<int, std::list<class GameEngineRenderer*>> AllRenderer = StartIter->second->GetMainCamera()->GetAllRenderer();
		std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer.begin();
		std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer.end();

		for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
		{
			std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
			std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
			std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

			for (; GroupStart != GroupEnd; ++GroupStart)
			{
				GameEngineFBXRenderer* GameEngineFBXRenderer_ = dynamic_cast<GameEngineFBXRenderer*>((*GroupStart));
				if (GameEngineFBXRenderer_ != nullptr)
				{
					GameEngineFBXRenderer_->ChangeLoadMaterial();
				}

			}
		}


	}
}
