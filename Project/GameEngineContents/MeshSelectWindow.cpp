#include "PreCompile.h"
#include "MeshSelectWindow.h"
#include "MeshObject.h"


MeshSelectWindow::MeshSelectWindow()
    :
    FbxCurentIndex_(0),
    SubSetCurentIndex_(0),
    SelectMaterial_(0),

    OpenFbx_(false),

    PreviewMeshRenderer_(),

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
            if (ImGui::Selectable(AllFBXMesh_[n].lock()->GetName().data(), is_selected))
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

    std::vector<FbxExMeshInfo> MeshInfo = AllFBXMesh_[FbxCurentIndex_].lock()->GetMeshInfos();

    if (ImGui::BeginListBox("Mesh List"))
    {
        for (int n = 0; n < MeshInfo.size(); n++)
        {
            const bool is_selected = (SubSetCurentIndex_ == n);
            if (ImGui::Selectable(MeshInfo[n].GetName().c_str(), is_selected))
            {
                SubSetCurentIndex_ = n;

                if (PreviewMeshRenderer_.lock() != nullptr)
                {
                    PreviewMeshRenderer_.lock()->Death();
                    PreviewMeshRenderer_.reset();
                    //  SubSetCurentIndex_ = 0;
                    SelectMaterial_ = 0;
                    MeshData_.PreviewMeshInfo_.clear();
                    AllMaterialTexture_.clear();
                }
                FbxName_ = AllFBXMesh_[FbxCurentIndex_].lock()->GetName().data();
                std::weak_ptr<MeshObject> MeshObject_ = GEngine::GetCurrentLevel()->CreateActor<MeshObject>();
                PreviewMeshRenderer_ = MeshObject_.lock()->CreateComponent<GameEngineFBXStaticRenderer>();
                PreviewMeshRenderer_.lock()->SetFBXMesh(FbxName_, "Texture", SubSetCurentIndex_);
                PreviewMesh_ = PreviewMeshRenderer_.lock()->GetFBXMesh();

                //매쉬 데이터 세팅
                for (int i = 0; i < PreviewMesh_.lock()->GetFbxRenderUnit().size(); ++i)
                {
                    MeshData_.PreviewMeshInfo_.push_back(SubSetMeshData{ PreviewMesh_.lock()->GetFbxRenderUnit()[i].MaterialData[0].DifTexturePath
                                     , PreviewMesh_.lock()->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName });
                }

                MeshData_.PreviewMeshName_ = PreviewMeshRenderer_.lock()->GetFBXMesh()->GetName().data();

                std::string Path = GameEngineDirectory::GetFolderPath(PreviewMesh_.lock()->GetPath());

                // 텍스처 리스트 로드
                GameEngineDirectory Dir(Path.data());

                std::vector<GameEngineFile> Textures = Dir.GetAllFile();

                for (int i = 0; i < Textures.size(); ++i)
                {
                    std::string FileName = Textures[i].GetFileName();
                    std::string Ex = GameEngineString::ToUpperReturn(GameEnginePath::GetExtension(FileName));
                    if (Ex == ".PNG")
                    {
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
            std::weak_ptr<GameEngineTexture> MaterialImage = AllMaterialTexture_[i];
            // MaterialImage->Get
            if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(MaterialImage.lock()->CreateShaderResourceView()), { 2048 / 7, 2048 / 7 }))
            {
                SelectMaterial_ = static_cast<int>(i);
                MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTextureName_ = AllMaterialTexture_[SelectMaterial_].lock()->GetName();

                std::string Path = MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTexturePath_;
                size_t idx = Path.rfind("\\");
                std::string NewPath = Path.substr(0, idx);

                NewPath += "\\" + MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTextureName_;
                MeshData_.PreviewMeshInfo_[SubSetCurentIndex_].DifTexturePath_ = Path;

                PreviewMesh_.lock()->GetFbxRenderUnit()[SubSetCurentIndex_].MaterialData[0].DifTexturePath = NewPath;
                PreviewMesh_.lock()->GetFbxRenderUnit()[SubSetCurentIndex_].MaterialData[0].DifTextureName = AllMaterialTexture_[SelectMaterial_].lock()->GetName();

                // 바꾼 매테리얼로 SetMesh
                PreviewMeshRenderer_.lock()->Death();
                PreviewMeshRenderer_.reset();

                std::shared_ptr<MeshObject> MeshObject_ = GEngine::GetCurrentLevel()->CreateActor<MeshObject>();
                PreviewMeshRenderer_ = MeshObject_->CreateComponent<GameEngineFBXStaticRenderer>();
                PreviewMeshRenderer_.lock()->SetFBXMesh(AllFBXMesh_[FbxCurentIndex_].lock()->GetName().data(), "Texture", SubSetCurentIndex_);

                //GameEngineFBXMesh* EditMesh = GameEngineFBXMesh::Find("Chef.FBX");

                //for (int j = 0; j < EditMesh->GetFbxRenderUnit().size(); ++j)
                //{
                //    if (EditMesh->GetFbxRenderUnit().empty() ==0)
                //    {
                //        int i = 0;
                //    }

                //    EditMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTexturePath = MeshData_.PreviewMeshInfo_[j].DifTexturePath_;
                //    EditMesh->GetFbxRenderUnit()[j].MaterialData[0].DifTextureName = MeshData_.PreviewMeshInfo_[j].DifTextureName_;



                //}




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

