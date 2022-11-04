#include "PreCompile.h"
#include "MeshSelectWindow.h"
#include "MeshObject.h"


MeshSelectWindow::MeshSelectWindow() 
    :
    ListIndex_(0),
    OpenFbx_(false),

    PreviewMesh_(nullptr)
{
}

MeshSelectWindow::~MeshSelectWindow() 
{
}

void MeshSelectWindow::Initialize(GameEngineLevel* _Level)
{
}

void MeshSelectWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
    if (true == ImGui::Button("Road FBX"))
    {
        if (AllFBXMesh_.empty())
        {
            AllFBXMesh_ = GameEngineFBXMesh::GetNamedResCopy();
            OpenFbx_ = true;
        }
    }

    static int FbxCurentIndex = 0;
    static int SubSetCurentIndex = 0;

    //std::vector<const char*> FbxNameList;

    //for (GameEngineFBXMesh* Fbx : AllFBXMesh_)
    //{
    //    FbxNameList.push_back(Fbx->GetName().data());
    //}

    if (OpenFbx_ == true)
    {
        //if (ImGui::TreeNode("Fbx List"))
        //{


        //    ImGui::TreePop();
        //}

        if (ImGui::BeginListBox("listbox 1"))
        {
            for (int n = 0; n < AllFBXMesh_.size(); n++)
            {
                const bool is_selected = (FbxCurentIndex == n);
                if (ImGui::Selectable(AllFBXMesh_[n]->GetName().data(), is_selected))
                    FbxCurentIndex = n;

                if (is_selected == true)
                {
                    ImGui::SetItemDefaultFocus();
                }
                   
            }
            ImGui::EndListBox();
        }

        std::vector<FbxExMeshInfo> Mesh = AllFBXMesh_[FbxCurentIndex]->GetMeshInfos();

        //std::vector<std::string> FbxSubSetNameList;
        //for (FbxExMeshInfo Fbx : Mesh)
        //{
        //    FbxSubSetNameList.push_back(Fbx.GetName().data());
        //}


        if (ImGui::BeginListBox(" "))
        {
            for (int n = 0; n < Mesh.size(); n++)
            {
                 const bool is_selected = (SubSetCurentIndex == n);
                ImGui::Selectable(Mesh[n].GetName().c_str(), true);
                SubSetCurentIndex = n;

                if (is_selected == true)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndListBox();
        }

        if (true == ImGui::Button("Preview Mesh"))
        {

            if (PreviewMesh_ == nullptr)
            {
                MeshObject* MeshObject_ = GEngine::GetCurrentLevel()->CreateActor<MeshObject>();
                PreviewMesh_ = MeshObject_-> CreateComponent<GameEngineFBXStaticRenderer>();
                PreviewMesh_->SetFBXMesh(AllFBXMesh_[FbxCurentIndex]->GetName().data(), "Texture", SubSetCurentIndex);
            }

        }

        //if (ImGui::TreeNode("Fbx SubSet List"))
        //{

        //    ImGui::TreePop();
        //}


    }



}

