#define _CRT_SECURE_NO_WARNINGS 

#include "includes.h"
#include "imgui/elements.h"
#include "menu.h"
#include "fonts/byte.h"
#include <filesystem>
#include "skStr.h"
#include <wininet.h>
#include <nlohmann/json.hpp>
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;


void OpenURL(const char* url) {
	SHELLEXECUTEINFOA execInfo = { 0 };
	execInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
	execInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
	execInfo.hwnd = NULL;
	execInfo.lpVerb = "open";
	execInfo.lpFile = url;
	execInfo.lpParameters = NULL;
	execInfo.lpDirectory = NULL;
	execInfo.nShow = SW_SHOWNORMAL;
	execInfo.hInstApp = NULL;
}

using json = nlohmann::json;
namespace fs = std::filesystem;


std::string GetHWID() {
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfile(&hwProfileInfo)) {
		std::string hwid = std::string(hwProfileInfo.szHwProfileGuid);
		hwid.erase(remove(hwid.begin(), hwid.end(), L'{'), hwid.end());
		hwid.erase(remove(hwid.begin(), hwid.end(), L'}'), hwid.end());
		hwid.erase(remove(hwid.begin(), hwid.end(), L' '), hwid.end());
		return hwid;
	}
	return "";
}

std::string HWID = GetHWID();
void InitImGui()
{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImFontConfig font_config;
		font_config.PixelSnapH = false;
		font_config.OversampleH = 5;
		font_config.OversampleV = 5;
		font_config.RasterizerMultiply = 1.2f;
		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0xE000, 0xE226, // icons
			0,
		};
		printf(OBFUSCATE_STR("\n[I] ONI Has been successfully injected , Press F1 to show/hide window.\n"));
		//ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		fonts::medium = io.Fonts->AddFontFromMemoryTTF(InterMedium, sizeof(InterMedium), 15.0f, &font_config, ranges);
		fonts::semibold = io.Fonts->AddFontFromMemoryTTF(InterSemiBold, sizeof(InterSemiBold), 17.0f, &font_config, ranges);
		//fonts::logo = io.Fonts->AddFontFromMemoryTTF(logos, sizeof(logos), 17.0f, &font_config, ranges);
		
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
}

ImVec2 windowPos;
ImVec2 windowSize;
bool visible;
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_F1) {
			visible = !visible;
			if (!visible)
			{
				::ShowCursor(FALSE);
				RECT clipRect;
				clipRect.left = windowPos.x;
				clipRect.top = windowPos.y;
				clipRect.right = windowPos.x + windowSize.x;
				clipRect.bottom = windowPos.y + windowSize.y;
				ClipCursor(&clipRect);
			}
			else {
				::ShowCursor(TRUE);
				ClipCursor(NULL);
			}
		}
		break;

	default:
		break;
	}

	if (!visible)
		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void UseFov()
{
	ImGui::GetForegroundDrawList()->AddCircle(ImVec2(resolutionX / 2, resolutionY / 2), fovRadius, ImColor(255, 255, 255, 255), 360);
}


void UpdateResolution() {
	HWND PG3D = FindWindow(NULL, OBFUSCATE_STR("Pixel Gun 3D"));
	RECT rect;
	GetWindowRect(PG3D, &rect);

	resolutionX = rect.right - rect.left;
	resolutionY = rect.bottom - rect.top;
}


bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;https://chat.openai.com/
			pSwapChain->GetDesc(&sd);
			SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}
		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	UpdateResolution();

	if (esp)
		DrawESP();

	if(visible)
		DrawMenu();

	if (fov)
		UseFov();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		AllocConsole();

		// Redirect stdout to the console
		FILE* pFile = nullptr;
		freopen_s(&pFile, OBFUSCATE_STR("CONOUT$"), OBFUSCATE_STR("w"), stdout);
		if (pFile == nullptr) {
			return FALSE;
		}

		freopen_s(&pFile, OBFUSCATE_STR("CONOUT$"), OBFUSCATE_STR("w"), stderr);
		if (pFile == nullptr) {
			return FALSE;
		}

		HWND hwnd = GetConsoleWindow();
		if (hwnd != NULL)
		{
			HMENU hMenu = GetSystemMenu(hwnd, FALSE);
			if (hMenu != NULL)
				DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
		}

		try {
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success && !anti_injection_vm())
			{

				InitHook();
				kiero::bind(8, (void**)&oPresent, hkPresent);
				init_hook = true;
			}
		}
		catch (std::runtime_error& e) {
			std::cout << OBFUSCATE_STR("Init failed") << e.what() << std::endl;
		}
		
	} while (!init_hook);
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
			break;
		case DLL_PROCESS_DETACH:
			kiero::shutdown();
			break;
	}
	return TRUE;
}