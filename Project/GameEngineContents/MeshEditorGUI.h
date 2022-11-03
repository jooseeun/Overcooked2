#pragma once
#include <GameEngineCore/GameEngineGUI.h>

// ���� :
class MeshEditorGUI : public GameEngineGUI
{
public:
	// constrcuter destructer
	MeshEditorGUI();
	~MeshEditorGUI();

	// delete Function
	MeshEditorGUI(const MeshEditorGUI& _Other) = delete;
	MeshEditorGUI(MeshEditorGUI&& _Other) noexcept = delete;
	MeshEditorGUI& operator=(const MeshEditorGUI& _Other) = delete;
	MeshEditorGUI& operator=(MeshEditorGUI&& _Other) noexcept = delete;

protected:

private:

};

