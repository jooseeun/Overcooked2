#include "PreCompile.h"
#include "MeshSelectWindow.h"
#include "MeshObject.h"


MeshSelectWindow::MeshSelectWindow()
    :
    FbxCurentIndex_(0),
    SubSetCurentIndex_(0),
    SelectMaterial_(0),

    OpenFbx_(false),

    PreviewMeshRenderer_(nullptr),

    FbxName_("")
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
    if (AllFBXMesh_.empty())
    {
        AllFBXMesh_ = GameEngineFBXMesh::GetNamedResCopy();
        OpenFbx_ = true;
    }



    if (ImGui::BeginListBox("FBX List"))
    {
        for (int n = 0; n < AllFBXMesh_.size(); n++)
        {
            const bool is_selected = (FbxCurentIndex_ == n);
            if (ImGui::Selectable(AllFBXMesh_[n]->GetName().data(), is_selected))
            {
                FbxCurentIndex_ = n;
                SubSetCurentIndex_ = 0;
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

                if (PreviewMeshRenderer_ != nullptr)
                {
                    PreviewMeshRenderer_->Death();
                    //  SubSetCurentIndex_ = 0;
                    SelectMaterial_ = 0;
                    MeshData_.PreviewMeshInfo_.clear();
                    AllMaterialTexture_.clear();
                }
                FbxName_ = AllFBXMesh_[FbxCurentIndex_]->GetName().data();
                MeshObject* MeshObject_ = GEngine::GetCurrentLevel()->CreateActor<MeshObject>();
                PreviewMeshRenderer_ = MeshObject_->CreateComponent<GameEngineFBXStaticRenderer>();
                PreviewMeshRenderer_->SetFBXMesh(FbxName_, "Texture", SubSetCurentIndex_);
                PreviewMesh_ = PreviewMeshRenderer_->GetFBXMesh();

                //매쉬 데이터 세팅
                for (int i = 0; i < PreviewMesh_->GetFbxRenderUnit().size(); ++i)
                {

                    MeshData_.PreviewMeshInfo_.push_back(SubSetMeshData{ PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTexturePath
                                     , PreviewMesh_->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName });
                }

                MeshData_.PreviewMeshName_ = PreviewMeshRenderer_->GetFBXMesh()->GetName().data();

                std::string Path = GameEngineDirectory::GetFolderPath(PreviewMesh_->GetPath());

                // 텍스처 리스트 로드
                GameEngineDirectory Dir(Path.data());

                std::vector<GameEngineFile> Textures = Dir.GetAllFile();

                for (int i = 0; i < Textures.size(); ++i)
                {
                    std::string FileName = Textures[i].GetFileName();
                    std::string Ex = GameEngineString::ToUpperReturn(GameEnginePath::GetExtension(FileName));
                    if (Ex == ".FBX")
                    {
                        continue;
                    }

                    if (GameEngineTexture::Find(Textures[i].GetFileName()) == nullptr)
                    {
                        AllMaterialTexture_.push_back(GameEngineTexture::Load(Textures[i].GetFullPath()));
                    }
                    else
                    {
                        AllMaterialTexture_.push_back(GameEngineTexture::Find(Textures[i].GetFileName()));
                    }

                }
            }

            if (is_selected == true)
            {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndListBox();
    }


    //선택한 매쉬가 있어야 텍스처가 나와요
    if (AllMaterialTexture_.size() > 0)
    {
        ImGui::BeginChildFrame((ImGuiID)"MateralSelect", { 450, 500 });

        for (size_t i = 0; i < AllMaterialTexture_.size(); i++)
        {
            GameEngineTexture* MaterialImage = AllMaterialTexture_[i];
            // MaterialImage->Get
            if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(MaterialImage->CreateShaderResourceView()), { 2048 / 7, 2048 / 7 }))
            {
                SelectMaterial_ = i;
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

                GameEngineFBXMesh* EditMesh = GameEngineFBXMesh::Find("Chef.FBX");

                for (int j = 0; j < EditMesh->GetFbxRenderUnit().size(); ++j)
                {
                    EditMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTexturePath = MeshData_.PreviewMeshInfo_[j].DifTexturePath_;
                    EditMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTextureName = MeshData_.PreviewMeshInfo_[j].DifTextureName_;



                }




                GlobalIOManager::SetMeshData(MeshData_);
                GlobalIOManager::Save(IOType::Mesh, "_" + FbxName_);
            }

            if (0 != (i + 1) % 1)
            {
                ImGui::SameLine();
            }
        }

        ImGui::EndChildFrame();


    }


}

