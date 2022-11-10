#include "PreCompile.h"
#include "GameEngineGUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineDevice.h"
#include "portable-file-dialogs.h"


std::list<std::shared_ptr<GameEngineGUIWindow>> GameEngineGUI::Windows;

GameEngineGUI::GameEngineGUI() 
{
}

GameEngineGUI::~GameEngineGUI() 
{
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void GameEngineGUI::Initialize()
{
	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    GameEngineDirectory Dir;

    Dir.MoveParentToExitsChildDirectory("GameEngineResources");
    Dir.Move("GameEngineResources");
    Dir.Move("Font");


    io.Fonts->AddFontFromFileTTF(Dir.PlusFilePath("malgun.ttf").c_str(), 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());


    ImGui_ImplWin32_Init(GameEngineWindow::GetHWND());
    ImGui_ImplDX11_Init(GameEngineDevice::GetDevice(), GameEngineDevice::GetContext());

    GameEngineWindow::GetInst()->SetMessageCallBack(ImGui_ImplWin32_WndProcHandler);
}



void GameEngineGUI::GUIRender(GameEngineLevel* _Level, float _DeltaTime)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    for (std::shared_ptr<GameEngineGUIWindow> GUIWIndow : Windows)
    {
        if (false == GUIWIndow->IsUpdate())
        {
            continue;
        }
        GUIWIndow->Begin();
        GUIWIndow->OnGUI(_Level, _DeltaTime);
        GUIWIndow->End();
    }

    //std::string Text = GameEngineString::AnsiToUTF8Return("윈도우창 하나");
    //std::string Button = GameEngineString::AnsiToUTF8Return("버튼");

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

std::string GameEngineGUI::OpenFolderDlg(const std::string& _Title, const std::string& _StartPath)
{
    pfd::select_folder Dlg = pfd::select_folder(_Title, _StartPath, pfd::opt::force_path);

    Dlg.kill();

    return Dlg.result();
}

std::string GameEngineGUI::OpenFileDlg(const std::string& _Title, const std::string& _StartPath)
{
    pfd::open_file Dlg = pfd::open_file(_Title, _StartPath, { "All Files", "*" }, pfd::opt::force_path);

    Dlg.kill();

    if (0 != Dlg.result().size())
    {
        return Dlg.result()[0];
    }

    return "";
}

void GameEngineGUI::GUIDestroy()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}