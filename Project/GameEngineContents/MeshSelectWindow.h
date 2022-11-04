#pragma once
#include <GameEngineCore/GameEngineGUI.h>

struct PreviewMeshInfo
{
	std::string DifTexturePath_;
	std::string DifTextureName_;
};

// ���� :
class MeshSelectWindow : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	MeshSelectWindow();
	~MeshSelectWindow();

	// delete Function
	MeshSelectWindow(const MeshSelectWindow& _Other) = delete;
	MeshSelectWindow(MeshSelectWindow&& _Other) noexcept = delete;
	MeshSelectWindow& operator=(const MeshSelectWindow& _Other) = delete;
	MeshSelectWindow& operator=(MeshSelectWindow&& _Other) noexcept = delete;

protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


private:

	bool OpenFbx_;
	int ListIndex_;

	std::string PreviewMeshName_;							// ������ Fbx �̸�
	std::vector<PreviewMeshInfo> PreviewMeshInfo_;			// �н�, �����̸� ����. ���� �������� �ε��� ������ push �ϰ� ����

	GameEngineFBXRenderer* PreviewMeshRenderer_;			// ������ fbx�� ������� ������
	GameEngineFBXMesh* PreviewMesh_;						// ������ ������� �Ž�����
	std::vector<GameEngineFBXMesh*> AllFBXMesh_;			// ���� ���� ��� fbx

	std::vector<GameEngineTexture*> AllMaterialTexture_;	// ������ fbx�� ���׸���

};

