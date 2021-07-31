#include "inc.h"

//other
WNDPROC WndProcOriginal = nullptr;

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

HRESULT(*presenthook)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*resizehook)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

uint64_t base_address = (uint64_t)GetModuleHandleA(NULL);
bool OpenIsTrue = false;

WNDPROC oriWndProc = NULL;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYUP && (wParam == VK_INSERT)) {
		OpenIsTrue = !OpenIsTrue;
		ImGui::GetIO().MouseDrawCursor = OpenIsTrue;
	}

	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

	return CallWindowProc(oriWndProc, hWnd, msg, wParam, lParam);
}


//IMGUI Scenes //begin //end

ImGuiWindow& BeginScene() {
	ImGui_ImplDX11_NewFrame();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	ImGui::Begin("##scene", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	return *ImGui::GetCurrentWindow();
}
ImGuiWindow& BeginScene();


VOID EndScene(ImGuiWindow& window);
VOID EndScene(ImGuiWindow& window) {
	window.DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
	ImGui::Render();
}
VOID AddLine(float x, float y, float xx, float yy, ImU32 color, int tickness) { ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(xx, yy), color, tickness); }

//base done by The.LostDev - ProjectHipCon.


//render stuff

//Custom Theme Done By The.LostDev
void CustomTheme()
{
	auto& style = ImGui::GetStyle();
	style.WindowPadding = { 10.f, 10.f };
	style.PopupRounding = 0.f;
	style.FramePadding = { 8.f, 4.f };
	style.ItemSpacing = { 10.f, 8.f };
	style.ItemInnerSpacing = { 6.f, 6.f };
	style.TouchExtraPadding = { 0.f, 0.f };
	style.IndentSpacing = 21.f;
	style.ScrollbarSize = 15.f;
	style.GrabMinSize = 8.f;
	style.WindowBorderSize = 1.5f;
	style.ChildBorderSize = 1.5f;
	style.PopupBorderSize = 1.5f;
	style.FrameBorderSize = 0.f;
	style.WindowRounding = 3.f;
	style.ChildRounding = 3.f;
	style.FrameRounding = 1.0f;
	style.ScrollbarRounding = 1.f;
	style.GrabRounding = 1.f;
	style.ButtonTextAlign = { 0.5f, 0.5f };
	style.DisplaySafeAreaPadding = { 3.f, 3.f };

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImColor(0.14f, 0.16f, 0.19f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImColor(0.89f, 0.89f, 0.89f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImColor(0.89f, 0.89f, 0.89f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImColor(0.89f, 0.89f, 0.89f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(255.f, 255.f, 255.f, 255.f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(255.f, 255.f, 255.f, 255.f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(255.f, 255.f, 255.f, 255.f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImColor(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0, 255, 255, 1.f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0, 255, 255, 1.f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0, 255, 255, 1.f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_Separator] = ImColor(255, 254, 255);


}

/// <summary>
/// fancy Dostyle Lol
/// </summary>
void DoStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.3f, 0.4f, 1.0f });
}

//renderization 
void MyMenuRender()
{
	CustomTheme();

	if (OpenIsTrue)
	{
		DoStyle();
		ImGui::Begin(_xor_("			NightLilBud").c_str(), &OpenIsTrue, ImVec2(300, 200), 1.0f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar); //edit menu here


		static int switchTabs = 3;

		if (ImGui::Button("Aimbot", ImVec2(100.0f, 0.0f)))
			switchTabs = 0;
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("ESP", ImVec2(100.0f, 0.0f)))
			switchTabs = 1;
		ImGui::SameLine(0.0, 2.0f);
		if (ImGui::Button("Misc", ImVec2(100.0f, 0.0f)))
			switchTabs = 2;

		switch (switchTabs) {
		case 0:
			ImGui::Text(("SilentToTheFeature"));
			//Do stuff for Aim tab, next for vis, and last for misc tab
			break;
		case 1:
			ImGui::Text(("SilentToTheFeature"));
			break;
		case 2:
			ImGui::Text(("SilentToTheFeature"));
			break;
		}
		ImGui::End();
	}
}

//base done by The.LostDev - ProjectHipCon.
//hooks for esp/aimbot and Resizing.
__declspec(dllexport) HRESULT hookresize(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return resizehook(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}
_declspec(dllexport) HRESULT hookpresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
	static HWND hWnd = 0;
	static float width = 0;
	static float height = 0;
	//find Unreal Window
	if (!device) {
		swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
		device->GetImmediateContext(&immediateContext);

		ID3D11Texture2D* hookpresent = nullptr;
		swapChain->GetBuffer(0, __uuidof(hookpresent), reinterpret_cast<PVOID*>(&hookpresent));
		device->CreateRenderTargetView(hookpresent, nullptr, &renderTargetView);
		hookpresent->Release();

		ID3D11Texture2D* backendbuffer = 0;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&backendbuffer);
		D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
		backendbuffer->GetDesc(&backBufferDesc);
		backendbuffer->Release();

		hWnd = FindWindow(xorstr(L"UnrealWindow"), xorstr(L"Fortnite  "));
		if (!width) {
			WndProcOriginal = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
		}
		width = (float)backBufferDesc.Width;
		height = (float)backBufferDesc.Height;


		ImGui_ImplDX11_Init(hWnd, device, immediateContext);
		ImGui_ImplDX11_CreateDeviceObjects();
	}
	immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
	auto& window = BeginScene();

	do {
	
	} while (FALSE);

	MyMenuRender();

	EndScene(window);

	return presenthook(swapChain, syncInterval, flags);
}
__declspec(dllexport) HRESULT DoResize(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return resizehook(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

//find window and Dllmain() APIENTRY Hooking
VOID MainFrame() {

	freopen("CONOUT$", "w", stdout);

	Sleep(10000);

	//find process
	HWND window = FindWindow(0, _xor_(L"Fortnite  ").c_str());

	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	auto                 featureLevel = D3D_FEATURE_LEVEL_11_0;



	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.OutputWindow = window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;


	//failed hooking Error
	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBox(0, _xor_(L"error device").c_str(), _xor_(L"error").c_str(), MB_ICONERROR);
		return;
	}

	auto swapchain = *reinterpret_cast<PVOID**>(swapChain);
	auto hookpresent = swapchain[8];
	auto hookresize = swapchain[13];

	context->Release();
	device->Release();
	swapChain->Release();

	MH_Initialize();

	MH_CreateHook(hookpresent, hookpresent, reinterpret_cast<PVOID*>(&presenthook));
	MH_EnableHook(hookpresent);

	MH_CreateHook(hookresize, hookresize, reinterpret_cast<PVOID*>(&resizehook));
	MH_EnableHook(hookresize);

	oriWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		MainFrame();
	}

	return TRUE;
}