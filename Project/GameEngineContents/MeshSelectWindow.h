#pragma once
#include <GameEngineCore/GameEngineGUI.h>

////���� ������ ����ü
//struct SubSetMeshInfo
//{
//	std::string DifTexturePath_;
//	std::string DifTextureName_;
//
//};
//
//struct SelectMeshData
//{
//	std::string PreviewMeshName_;							// ������ Fbx �̸�
//	std::vector<SubSetMeshInfo> PreviewMeshInfo_;			// �н�, �����̸� ����. ���� �������� �ε��� ������ push �ϰ� ����
//
//	//���� �ε��� => ����� �ε���(�Ƹ�..)
//};


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

	int FbxCurentIndex_;
	int SubSetCurentIndex_;
	int SelectMaterial_;

	bool OpenFbx_;

	MeshData MeshData_;

	std::shared_ptr<GameEngineFBXRenderer> PreviewMeshRenderer_;			// ������ fbx�� ������� ������
	std::shared_ptr<GameEngineFBXMesh> PreviewMesh_;						// ������ ������� �Ž�����
	
	std::string FbxName_;
	std::vector<std::shared_ptr<GameEngineFBXMesh>> AllFBXMesh_;			// ���� ���� ��� fbx
	std::vector<std::shared_ptr<GameEngineTexture>> AllMaterialTexture_;	// ������ fbx�� ���׸���

};

