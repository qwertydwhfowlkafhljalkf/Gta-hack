#include "../Header/Cheat Functions/FiberMain.h"
#include "../../../Header/GUI/ImGui/DearImGui.h"
#include <d3d11.h>
#include <dxgi.h>

using namespace Cheat;

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

HMODULE ourModule = 0;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
Present oPresent;
ResizeBuffers oResizeBuffers;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
bool init = false;

// Functions
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
HRESULT hkResizeBuffers(IDXGISwapChain* pThis, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
DWORD WINAPI RenderHookThread(HMODULE hmod);


void GUI::DearImGui::Init()
{
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)RenderHookThread, CheatModuleHandle, NULL, nullptr);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (CheatFeatures::CursorNavigationState && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) && !Controls::ControlsDisabled)
	{
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (mainRenderTargetView) {
		pContext->OMSetRenderTargets(0, 0, 0);
		mainRenderTargetView->Release();
	}

	HRESULT hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

	pDevice->CreateRenderTargetView(pBuffer, NULL, &mainRenderTargetView);
	pBuffer->Release();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);

	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);
	return hr;
}

//bool WhatsNewDataInitialized = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.IniFilename = NULL;
			io.MouseDrawCursor = true;
			std::string FontLocation = std::getenv("SystemDrive") + (std::string)"\\Windows\\Fonts\\Verdana.ttf";
			io.Fonts->AddFontFromFileTTF(FontLocation.c_str(), 20.f);
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(pDevice, pContext);
			init = true;
		}
		else
		{
			return oPresent(pSwapChain, SyncInterval, Flags);
		}			
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuiIO& io = ImGui::GetIO();

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_TitleBg] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_TitleBgActive] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
	colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0, 0);
	colors[ImGuiCol_Button] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ButtonHovered] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ButtonActive] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ResizeGripHovered] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ResizeGrip] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_ResizeGripActive] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);
	colors[ImGuiCol_CheckMark] = ImColor(GUI::PrimaryColor.r, GUI::PrimaryColor.g, GUI::PrimaryColor.b);

	// Windows
	Logger::CheatWindow();
	Logger::GameChatWindow();

	// On-screen Game & Cheat Info
	if (!CheatFeatures::HideOnScreenGameAndCheatInfo && CheatFunctions::LoadConfigThreadFunctionCompleted)
	{
		// Cursor navigation
		std::string CursurNavigation = "Cursor navigation is ";
		std::string CursorNavigationStatus = CheatFeatures::CursorNavigationState ? "active (Press " + CheatFunctions::VirtualKeyCodeToString(Controls::CursorNavigationKey) + " to deactivate)" : "inactive (Press " + CheatFunctions::VirtualKeyCodeToString(Controls::CursorNavigationKey) + " to activate)";
		std::string CursorText = CursurNavigation + CursorNavigationStatus;

		// Menu GUI
		std::string MenuGUI = "Menu GUI is ";
		std::string MenuGUIStatus = GUI::menuLevel > 0 ? "visible (Press " + CheatFunctions::VirtualKeyCodeToString(Controls::OpenMenuGUIKey) + " to hide)" : "hidden (Press " + CheatFunctions::VirtualKeyCodeToString(Controls::OpenMenuGUIKey) + " to show)";
		std::string MenuGUIText = MenuGUI + MenuGUIStatus;

		// Log window
		std::string LogWindow = "Log window is ";
		std::string LogWindowStatus = Logger::CheatWindowVisible ? "open (Press ~ to close)" : "closed (Press ~ to open)";
		std::string LogWindowText = LogWindow + LogWindowStatus;

		ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(24, 24, 24, 255));
		ImGui::Begin("Game & Cheat Information", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
		ImGui::Text(CursorText.c_str());
		ImGui::Text(MenuGUIText.c_str());
		ImGui::Text(LogWindowText.c_str());
		ImGui::SetWindowPos(ImVec2(io.DisplaySize.x - ImGui::GetWindowWidth() - 20.f, io.DisplaySize.y - ImGui::GetWindowHeight() - 50.f));
		ImGui::PopStyleColor();
		ImGui::End();
	}

	/* 
	What's new popup - TODO
	const char* ChangelogText = "";
	if (!WhatsNewDataInitialized)
	{
		Json::Value JsonDataObject = CheatFunctions::ReturnGithubAPIJsonDataCheat("v" + (std::string)CHEAT_BUILD_NUMBER);
		if (JsonDataObject.isMember("body"))
		{
			ChangelogText = JsonDataObject["body"].asCString();

		}
		else
		{
			ChangelogText = "Changelog text is unavailable";
		}
		WhatsNewDataInitialized = true;
	}
	else
	{
		ImGui::SetNextWindowSize(ImVec2(800, 800));
		ImGui::OpenPopup("GTAV Cheat - What's New");
		if (ImGui::BeginPopupModal("GTAV Cheat - What's New", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
			ImGui::Text(ChangelogText);

			if (ImGui::Button("Close", ImVec2(200, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}	
	*/
	
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI RenderHookThread(HMODULE hmod)
{
	if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
	{
		kiero::bind(8, (void**)&oPresent, hkPresent);
		kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
	}
	else
	{
		Logger::Error("Kiero initialization failed", true);
	}
	return TRUE;
}