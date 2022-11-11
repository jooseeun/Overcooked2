#pragma once
#include <GameEngineCore/GameEngineGUI.h>

////저장 데이터 구조체
//struct SubSetMeshInfo
//{
//	std::string DifTexturePath_;
//	std::string DifTextureName_;
//
//};
//
//struct SelectMeshData
//{
//	std::string PreviewMeshName_;							// 선택한 Fbx 이름
//	std::vector<SubSetMeshInfo> PreviewMeshInfo_;			// 패스, 파일이름 저장. 실제 렌더유닛 인덱스 순으로 push 하고 있음
//
//	//벡터 인덱스 => 서브셋 인덱스(아마..)
//};


// 설명 :
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

	std::shared_ptr<GameEngineFBXRenderer> PreviewMeshRenderer_;			// 선택한 fbx의 서브셋의 랜더러
	std::shared_ptr<GameEngineFBXMesh> PreviewMesh_;						// 선택한 서브셋의 매쉬정보
	
	std::string FbxName_;
	std::vector<std::shared_ptr<GameEngineFBXMesh>> AllFBXMesh_;			// 게임 내의 모든 fbx
	std::vector<std::shared_ptr<GameEngineTexture>> AllMaterialTexture_;	// 선택한 fbx의 매테리얼

};

