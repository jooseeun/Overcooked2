#include "PreCompile.h"
#include "MeshSelectWindow.h"
#include "MeshObject.h"


MeshSelectWindow::MeshSelectWindow() 
    :
    FbxCurentIndex_(0),
    SubSetCurentIndex_(0),
    SelectMaterial_(0),


    OpenFbx_(false),

    PreviewMeshRenderer_(nullptr)
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



    //std::vector<const char*> FbxNameList;

    //for (GameEngineFBXMesh* Fbx : AllFBXMesh_)
    //{
    //    FbxNameList.push_back(Fbx->GetName().data());
    //}

    if (OpenFbx_ == true)
    {

        if (ImGui::BeginListBox("FBX List"))
        {
            for (int n = 0; n < AllFBXMesh_.size(); n++)
            {
                const bool is_selected = (FbxCurentIndex_ == n);
                if (ImGui::Selectable(AllFBXMesh_[n]->GetName().data(), is_selected))
                {
                    FbxCurentIndex_ = n;
                }
                   
                if (is_selected == true)
                {
                    ImGui::SetItemDefaultFocus();
                }
                   
            }
            ImGui::EndListBox();
        }

        std::vector<FbxExMeshInfo> MeshInfo = AllFBXMesh_[FbxCurentIndex_]->GetMeshInfos();

        if (ImGui::BeginListBox("Mesh List"))
        {
            for (int n = 0; n < MeshInfo.size(); n++)
            {
                 const bool is_selected = (SubSetCurentIndex_ == n);
                 if (ImGui::Selectable(MeshInfo[n].GetName().c_str(), is_selected))
                 {
                     SubSetCurentIndex_ = n;
                 }

                if (is_selected == true)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndListBox();
        }

        if (true == ImGui::Button("Preview Mesh"))
        {

            if (PreviewMeshRenderer_ != nullptr)
            {
                PreviewMeshRenderer_->Death();
              //  SubSetCurentIndex_ = 0;
                SelectMaterial_ = 0;
                MeshData_. PreviewMeshInfo_.clear();
                AllMaterialTexture_.clear();
            }

            MeshObject* MeshObject_ = GEngine::GetCurrentLevel()->CreateActor<MeshObject>();
            PreviewMeshRenderer_ = MeshObject_->CreateComponent<GameEngineFBXStaticRenderer>();
            PreviewMeshRenderer_->SetFBXMesh(AllFBXMesh_[FbxCurentIndex_]->GetName().data(), "Texture", SubSetCurentIndex_);
            PreviewMesh_ = PreviewMeshRenderer_->GetFBXMesh();

            //매쉬 데이터 세팅
            for (int i = 0; i < PreviewMesh_->GetFbxRenderUnit().size(); ++i)
            {            
                //fbxsdk::FbxNode* pMeshNode = MeshInfo[i].Mesh->GetNode();
                //fbxsdk::FbxSurfaceMaterial* pMtrl = pMeshNode->GetMaterial(0);
                //std::string Path = PreviewMesh_->MaterialTex(pMtrl, "DiffuseColor");

                //PreviewMeshInfo_.push_back(PreviewMeshInfo{ Path
                //    ,  PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName });

                MeshData_.PreviewMeshInfo_.push_back(SubSetMeshInfo{ PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTexturePath
                                 , PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName });
            }

            MeshData_.PreviewMeshName_ = PreviewMeshRenderer_->GetFBXMesh()->GetName().data();


            for (int i = 0; i < PreviewMesh_->GetFbxRenderUnit().size(); ++i)
            {
                std::string Name = PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName;
                std::string Path = GameEngineDirectory::GetFolderPath(PreviewMesh_->GetPath());
                GameEngineTexture* Texture = GameEngineTexture::Find(PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName);
                if (nullptr == Texture)
                {
                    std::string FilePath = Path + Name;
                    //GameEngineTexture::Load(FilePath);

                    AllMaterialTexture_.push_back(GameEngineTexture::Load(FilePath));

                }
                else
                {
                    //동일한 리소스 있는지 체크
                    bool CheckTexture = false;
                    for (int j = 0; j < AllMaterialTexture_.size(); ++j)
                    {
                        if (AllMaterialTexture_[j] == Texture)
                        {
                            CheckTexture = true;
                            break;
                        }
                    }

                    if (CheckTexture == true)
                    {
                        continue;

                    }
                    else
                    {
                        AllMaterialTexture_.push_back(GameEngineTexture::Find(Name));
                    }

                }

            }

        }

        //선택한 매쉬가 있어야 텍스처가 나와요
        if (AllMaterialTexture_.size() > 0)
        {
            ImGui::BeginChildFrame((ImGuiID)"MateralSelect", { 450, 500 });

            for (size_t i = 0; i < AllMaterialTexture_.size(); i++)
            {
                GameEngineTexture* MaterialImage = AllMaterialTexture_[i];
               // MaterialImage->Get
                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(MaterialImage->CreateShaderResourceView()), { 2048/7, 2048/7 }))
                {
                    SelectMaterial_ = i;
                }

                if (0 != (i + 1) % 1)
                {
                    ImGui::SameLine();
                }
            }

            ImGui::EndChildFrame();

            if (true == ImGui::Button("Change Material"))
            {
                MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTextureName_ = AllMaterialTexture_[SelectMaterial_]->GetName();

                std::string Path = MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTexturePath_;
                size_t idx = Path.rfind("\\");
                std::string NewPath = Path.substr(0, idx);

                NewPath += "\\" + MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTextureName_;
                MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTexturePath_ = Path;

                PreviewMesh_->GetFbxRenderUnit()[SubSetCurentIndex_].MaterialData[0].DifTexturePath = NewPath;
                PreviewMesh_->GetFbxRenderUnit()[SubSetCurentIndex_].MaterialData[0].DifTextureName = AllMaterialTexture_[SelectMaterial_]->GetName();

                // 바꾼 매테리얼로 SetMesh
                PreviewMeshRenderer_->Death();
                PreviewMeshRenderer_ = nullptr;

                MeshObject* MeshObject_ = GEngine::GetCurrentLevel()->CreateActor<MeshObject>();
                PreviewMeshRenderer_ = MeshObject_->CreateComponent<GameEngineFBXStaticRenderer>();
                PreviewMeshRenderer_->SetFBXMesh(AllFBXMesh_[FbxCurentIndex_]->GetName().data(), "Texture", SubSetCurentIndex_);
            }

        }

    }


}

