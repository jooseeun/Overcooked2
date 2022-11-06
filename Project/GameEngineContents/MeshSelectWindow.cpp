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
               // SubSetCurentIndex_ = 0;
                SelectMaterial_ = 0;
                PreviewMeshInfo_.clear();
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

                PreviewMeshInfo_.push_back(PreviewMeshInfo{ AllFBXMesh_[i]->GetFbxRenderUnit()[i].MaterialData[0].DifTexturePath
                 ,  AllFBXMesh_[i]->GetFbxRenderUnit()[i].MaterialData[0].DifTextureName });
            }

            PreviewMeshName_ = PreviewMeshRenderer_->GetFBXMesh()->GetName().data();


            // 텍스처 리스트 로드
            GameEngineDirectory Dir;
            Dir.MoveParentToExitsChildDirectory("ContentsResources");
            Dir.Move("ContentsResources");
            Dir.Move("Mesh");
           // Dir.Move("Level");

            std::string FbxName = PreviewMeshName_;
            size_t idx = FbxName.find(".");
            std::string DirName = FbxName.substr(0, idx);

            //만약 경로를 한번 더 걸친다면

            std::string CheckPath = PreviewMeshInfo_[0].DifTexturePath_;

            size_t Test = CheckPath.find("Level");
            int a = 0;

            if (Test == std::string::npos)
            {
                int a = 0;
            }
            Dir.Move(DirName);

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
                PreviewMeshInfo_[SubSetCurentIndex_].DifTextureName_ = AllMaterialTexture_[SelectMaterial_]->GetName();

                std::string Path = PreviewMeshInfo_[SubSetCurentIndex_].DifTexturePath_;
                size_t idx = Path.rfind("\\");
                std::string NewPath = Path.substr(0, idx);

                NewPath += "\\" + PreviewMeshInfo_[SubSetCurentIndex_].DifTextureName_;
                PreviewMeshInfo_[SubSetCurentIndex_].DifTexturePath_ = Path;

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

