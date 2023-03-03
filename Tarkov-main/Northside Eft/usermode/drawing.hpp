#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "common.hpp"
#include <d3d11.h>
#include <random>
#include <dwmapi.h>
#include "globals.hpp"

bool b_Shutdown = false;
HWND h_Game;
bool is_menu = false;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace draw
{
    HWND h_hWnd;
    WNDCLASSEX wc;

    ID3D11Device* g_pd3dDevice = NULL;
    ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
    IDXGISwapChain* g_pSwapChain = NULL;
    ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

    static const char* options[]{ "Head", "Chest", "Leg" };
    int selected;

    void UpdateWND()
    {
        while (true)
        {
            if (GetAsyncKeyState(VK_UP) != 0)
                is_menu = !is_menu;

            long style = GetWindowLongPtr(h_hWnd, GWL_EXSTYLE);


            if (is_menu)
            {
                style &= ~WS_EX_LAYERED;
                SetWindowLongPtr(h_hWnd, GWL_EXSTYLE, style);
            }
            else
            {
                style |= WS_EX_LAYERED;
                SetWindowLongPtr(h_hWnd, GWL_EXSTYLE, style);
            }
            Sleep(100);
        }
    }

    void draw_box(ImVec2 p1, ImVec2 p2, ImDrawList* draw_list)
    {
        draw_list->AddRect(p1, p2, ImGui::ColorConvertFloat4ToU32(ImVec4(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z, 1)), 0.f, 0, 1.5);
    }

    auto CleanupRenderTarget() -> void
    {
        if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
    }

    auto CleanupDeviceD3D() -> void
    {
        CleanupRenderTarget();
        if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
        if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
        if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    }
    void DrawCross(float x, float y, float width, float height, ImColor col) {
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x - width, y), ImVec2(x + width, y), col, 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(y - height, x), ImVec2(y + height, x), col, 3);
    }
     
    void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
    {
        float lineW = (W / 3);
        float lineH = (H / 3);

        ////black outlines
        
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

        //corners
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
        ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
    }
    void CreateRenderTarget()
    {
        ID3D11Texture2D* pBackBuffer;
        g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
        pBackBuffer->Release();
    }

    bool CreateDeviceD3D()
    {
        /* setup swap chain */
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 300;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = h_hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
            return false;

        CreateRenderTarget();
        return true;
    }

    void Shutdown()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        CleanupDeviceD3D();
        DestroyWindow(h_hWnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        std::exit(0);
    }

    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application Render
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        default: break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    /**
     * initializes the renderer
     */


    int FrameRate()
    {
        static int iFps, iLastFps;
        static float flLastTickCount, flTickCount;
        flTickCount = clock() * 0.001f;
        iFps++;
        if ((flTickCount - flLastTickCount) >= 1.0f) {
            flLastTickCount = flTickCount;
            iLastFps = iFps;
            iFps = 0;
        }
        return iLastFps;
    }
    bool Initialize()
    {
        WINDOWPLACEMENT g_wpPrev;
        DWORD dwStyle = GetWindowLong(h_Game, GWL_STYLE);
        MONITORINFO mi = { sizeof(mi) };
        if (GetWindowPlacement(h_Game, &g_wpPrev) &&
            GetMonitorInfo(MonitorFromWindow(h_Game,
                MONITOR_DEFAULTTOPRIMARY), &mi)) {
            SetWindowLong(h_Game, GWL_STYLE,
                dwStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(h_Game, HWND_TOP,
                mi.rcMonitor.left, mi.rcMonitor.top,
                mi.rcMonitor.right - mi.rcMonitor.left,
                mi.rcMonitor.bottom - mi.rcMonitor.top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
        }

        // Create application window
        wc = { sizeof(WNDCLASSEX), ACS_TRANSPARENT, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, ("Windows Task Assistant"), NULL };
        RegisterClassEx(&wc);
        h_hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LAYERED, wc.lpszClassName, (""), WS_POPUP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, wc.hInstance, NULL);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateWND, 0, 0, 0);
        MARGINS margins = { -1 };
        DwmExtendFrameIntoClientArea(h_hWnd, &margins);

        SetLayeredWindowAttributes(h_hWnd, 0, 1.0f, LWA_ALPHA);
        SetLayeredWindowAttributes(h_hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);

        // Initialize Direct3D
        if (!CreateDeviceD3D())
        {
            CleanupDeviceD3D();
            UnregisterClass(wc.lpszClassName, wc.hInstance);
            return 1;
        }

        ShowWindow(h_hWnd, SW_SHOWDEFAULT);
        UpdateWindow(h_hWnd);

        SetForegroundWindow(h_hWnd);

        //IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = nullptr;
        io.Fonts->AddFontDefault();
        //ImFont* mdFont1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 16.f);
        //ImFont* mdFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 16.f);


        ImGui_ImplWin32_Init(h_hWnd);
        ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

        MSG msg;
        ZeroMemory(&msg, sizeof(msg));

        while (msg.message != WM_QUIT)
        {
            if (b_Shutdown)
                break;

            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                continue;
            }
           
            ImGui_ImplDX11_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
           // ImGui::PopFont;
            bool linesa;
            if (is_menu)
            {
                ImGui::SetWindowSize(ImVec2(650.0f, 400.0f));
                ImGui::SetNextWindowSize(ImVec2(650.0f, 400.0f));
                ImGui::Begin("Northside Tarkov", 0, ImGuiWindowFlags_NoTitleBar);
                {
               //     ImGui::PushFont(mdFont1);
                    auto& Style = ImGui::GetStyle();

                    Style.WindowPadding = ImVec2(5.000f, 8.000f);
                    Style.WindowRounding = 7.000f;
                    Style.WindowBorderSize = 0.000f;
                    Style.ChildRounding = 8.000f;
                    Style.ChildBorderSize = 0.000f;
                    Style.PopupRounding = 8.000f;
                    Style.FramePadding = ImVec2(0.000f, 3.000f);
                    Style.FrameRounding = 10.000f;
                    Style.ItemInnerSpacing = ImVec2(14.000f, 0.000f);
                    Style.CellPadding = ImVec2(4.000f, 1.000f);
                    Style.IndentSpacing = 15.000f;
                    Style.ScrollbarSize = 1.000f;
                    Style.ScrollbarRounding = 5.000f;
                    Style.GrabRounding = 7.000f;
                    // io.Fonts->AddFontDefault();
                     //ImFont* mainfont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\ntailu.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
                    // IM_ASSERT(mainfont != NULL);

                   // ImGui::PopFont();



                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.f, 0.f, 0.1f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.f, 0.f, 0.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.f, 0.f, 0.0f));
                    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.0f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.0f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.0f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.0f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.f, 0.f, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.078, 0.094, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 0.078, 0.094, 1.f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 1.f));

                    if (settings::is_in_raid)
                    {
                        ImVec2 P1, P2;
                        ImDrawList* pDrawList;
                        const auto& CurrentWindowPos = ImGui::GetWindowPos();
                        const auto& pWindowDrawList = ImGui::GetWindowDrawList();
                        //const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
                        //const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();

                        P1 = ImVec2(149.000f, 9.000f);
                        P1.x += CurrentWindowPos.x;
                        P1.y += CurrentWindowPos.y;
                        P2 = ImVec2(150.000f, 390.000f);
                        P2.x += CurrentWindowPos.x;
                        P2.y += CurrentWindowPos.y;
                        pDrawList = pWindowDrawList;
                        pDrawList->AddRectFilledMultiColor(P1, P2,
                            ImColor(1.000f, 0.000f, 0.000f, 1.000f),
                            ImColor(1.000f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.248f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.243f, 0.000f, 0.000f, 1.000f));

                        P1 = ImVec2(170.000f, 48.000f);
                        P1.x += CurrentWindowPos.x;
                        P1.y += CurrentWindowPos.y;
                        P2 = ImVec2(300.000f, 50.000f);
                        P2.x += CurrentWindowPos.x;
                        P2.y += CurrentWindowPos.y;
                        pDrawList = pWindowDrawList;
                        pDrawList->AddRectFilledMultiColor(P1, P2,
                            ImColor(1.000f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.386f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.000f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.000f, 0.000f, 0.000f, 1.000f));

                        P1 = ImVec2(160.000f, 70.000f);
                        P1.x += CurrentWindowPos.x;
                        P1.y += CurrentWindowPos.y;
                        P2 = ImVec2(625.000f, 380.000f);
                        P2.x += CurrentWindowPos.x;
                        P2.y += CurrentWindowPos.y;
                        pDrawList = pWindowDrawList;
                        pDrawList->AddRectFilledMultiColor(P1, P2,
                            ImColor(1.000f, 0.000f, 0.000f, 1.000f),
                            ImColor(1.000f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.253f, 0.000f, 0.000f, 1.000f),
                            ImColor(0.253f, 0.000f, 0.000f, 1.000f));

                        P1 = ImVec2(161.000f, 71.000f);
                        P1.x += CurrentWindowPos.x;
                        P1.y += CurrentWindowPos.y;
                        P2 = ImVec2(624.000f, 379.000f);
                        P2.x += CurrentWindowPos.x;
                        P2.y += CurrentWindowPos.y;
                        pDrawList = pWindowDrawList;
                        pDrawList->AddRectFilled(P1, P2, ImColor(0.055f, 0.051f, 0.055f, 1.000f), 0.000f);


                        int tab;

                        ImGui::SetCursorPos(ImVec2(15, 25));
                        if (ImGui::Button("Visuals", ImVec2(125, 45)))
                        {
                            tab = 1;

                        }

                        ImGui::SetCursorPos(ImVec2(15, 100));
                        if (ImGui::Button("Combat", ImVec2(125, 45)))
                        {
                            tab = 2;
                        }

                        ImGui::SetCursorPos(ImVec2(15, 175));
                        if (ImGui::Button("Loot Esp", ImVec2(125, 45)))
                        {
                            tab = 5;
                        }
                        ImGui::SetCursorPos(ImVec2(15, 250));
                        if (ImGui::Button("Misc", ImVec2(125, 45)))
                        {
                            tab = 3;
                        }
                        ImGui::SetCursorPos(ImVec2(15, 325));
                        if (ImGui::Button("Colors", ImVec2(125, 45)))
                        {
                            tab = 4;
                        }



                        if (tab == 0)
                        {
                            ImGui::SetCursorPos(ImVec2(250, 19));
                            ImGui::Text("Visuals");
                        }
                        if (tab == 1)
                        {
                            //top
                            ImGui::SetCursorPos(ImVec2(175, 35));
                            ImGui::Text("Visuals");

                            //inside child
                            bool test;
                            float distance;
                            ImGui::SetCursorPos(ImVec2(170, 80));
                            ImGui::ToggleButton("Render Box", &settings::box); ImGui::SameLine(); ImGui::Text("Render 2D Box");
                            ImGui::SetCursorPos(ImVec2(170, 110));
                            ImGui::ToggleButton("Render Corner Box", &settings::corner); ImGui::SameLine(); ImGui::Text("Render 2D Corner Box");
                            ImGui::SetCursorPos(ImVec2(170, 140));
                            ImGui::ToggleButton("Render Player Health", &settings::esp::show_health); ImGui::SameLine(); ImGui::Text("Render Enemys Heath");
                            ImGui::SetCursorPos(ImVec2(170, 170));
                            ImGui::ToggleButton("Render Player Name", &settings::esp::show_role); ImGui::SameLine(); ImGui::Text("Render Enemeys Name");
                            ImGui::SetCursorPos(ImVec2(170, 200));
                            ImGui::ToggleButton("Render Player Skeleton", &settings::skeleton); ImGui::SameLine(); ImGui::Text("Render Enemeys Skeleton");
                            ImGui::SetCursorPos(ImVec2(170, 230));
                            ImGui::ToggleButton("Render Player Distance", &settings::esp::show_distance); ImGui::SameLine(); ImGui::Text("Render Enemeys Distance");
                            ImGui::SetCursorPos(ImVec2(170, 260));
                            ImGui::ToggleButton("Render Snaplines", &settings::snaplinesnigga); ImGui::SameLine(); ImGui::Text("Render Snaplines To Enemeys");
                            ImGui::SetCursorPos(ImVec2(170, 290));
                            ImGui::ToggleButton("Extract Esp", &settings::esp::show_extracts); ImGui::SameLine(); ImGui::Text("Extract ESP");
                            ImGui::SetCursorPos(ImVec2(170, 310));
                            ImGui::Text("Render Distance");
                            ImGui::SetCursorPos(ImVec2(170, 340));
                            ImGui::SliderFloat("[M]", &settings::esp::max_distance, 50.0f, 750.0f, "%10.0f");


                        }

                        if (tab == 2)
                        {
                            //top
                            ImGui::SetCursorPos(ImVec2(175, 35));
                            ImGui::Text("Combat");

                            //inside child
                            bool test1;
                            float circle;
                            float smoothing;
                            float distance1;



                            ImGui::SetCursorPos(ImVec2(170, 80));
                            ImGui::ToggleButton("Enable Sticky Aimbot", &settings::is_aimbot); ImGui::SameLine(); ImGui::Text("Enable Aimbot");
                            ImGui::SetCursorPos(ImVec2(170, 110));
                            ImGui::ToggleButton("Enable Silent Aimbot", &settings::silent); ImGui::SameLine(); ImGui::Text("Enable Aimbot");
                            ImGui::SetCursorPos(ImVec2(170, 140));
                            ImGui::ToggleButton("Render Fov Circle", &settings::aim::enable_fov_circle); ImGui::SameLine(); ImGui::Text("Render field of view");
                            ImGui::SetCursorPos(ImVec2(170, 190));
                            ImGui::ToggleButton("Line To Target", &settings::esp::show_aim_line); ImGui::SameLine(); ImGui::Text("Render Locked Target");
                            ImGui::SetCursorPos(ImVec2(170, 220));
                            ImGui::Text("Size Of Circle");
                            ImGui::SetCursorPos(ImVec2(170, 250));
                            ImGui::SliderFloat("Size", &settings::aim::aim_fov, 1.0f, 100.0f, "%1.0f");

                            ImGui::SetCursorPos(ImVec2(170, 280));
                            ImGui::Text("Attack Distance");
                            ImGui::SetCursorPos(ImVec2(170, 310));
                            ImGui::SliderFloat("[M]", &settings::aim::max_distance, 50.0f, 750.0f, "%10.0f");
                            ImGui::SetCursorPos(ImVec2(170, 340));
                            ImGui::Text("Aim Bone"); ImGui::SameLine(); ImGui::Combo(" ", &selected, options, IM_ARRAYSIZE(options));

                            switch (selected)
                            {
                            case 0:
                                settings::aim::aim_bone = Bone::bones::HumanHead;
                                break;
                            case 1:
                                settings::aim::aim_bone = Bone::bones::HumanSpine2;
                                break;
                            case 2:
                                settings::aim::aim_bone = Bone::bones::HumanLCalf;
                                break;
                            }


                        }

                        if (tab == 3)
                        {

                            ImGui::SetCursorPos(ImVec2(175, 35));
                            ImGui::Text("Misc");
                            bool test2;
                            ImGui::SetCursorPos(ImVec2(170, 80));
                            ImGui::ToggleButton("No Recoil", &settings::is_no_recoil); ImGui::SameLine(); ImGui::Text("No Recoil");
                            ImGui::SetCursorPos(ImVec2(170, 110));
                            ImGui::ToggleButton("No Sway", &settings::is_no_spread); ImGui::SameLine(); ImGui::Text("No Sway");
                            ImGui::SetCursorPos(ImVec2(170, 140));
                            ImGui::ToggleButton("Infinite Stamina", &settings::is_infinite_stamina); ImGui::SameLine(); ImGui::Text("Infinite Stamina");
                            ImGui::SetCursorPos(ImVec2(170, 170));
                            ImGui::ToggleButton("Night Vision", &settings::nightvision); ImGui::SameLine(); ImGui::Text("Night Vision");
                            ImGui::SetCursorPos(ImVec2(170, 200));
                            ImGui::ToggleButton("Thermal Vision", &settings::is_thermal_vision); ImGui::SameLine(); ImGui::Text("Thermal Vision");
                            ImGui::SetCursorPos(ImVec2(170, 230));
                            ImGui::ToggleButton("No Visor", &settings::is_no_visor); ImGui::SameLine(); ImGui::Text("No Visor");
                            ImGui::SetCursorPos(ImVec2(170, 260));
                            ImGui::ToggleButton("Chams", &settings::is_chams); ImGui::SameLine(); ImGui::Text("Chams");
                            ImGui::SetCursorPos(ImVec2(170, 290));
                            ImGui::ToggleButton("Instant Aim", &settings::is_instant_aim); ImGui::SameLine(); ImGui::Text("Instant Aim");
                            ImGui::SetCursorPos(ImVec2(170, 320));
                            ImGui::ToggleButton("Loot Through Walls", &settings::is_loot_thru_walls); ImGui::SameLine(); ImGui::Text("Loot Through Walls");
                            ImGui::SetCursorPos(ImVec2(350, 80));
                            ImGui::ToggleButton("Fov Changer", &settings::chanfov); ImGui::SameLine(); ImGui::Text("Fov Changer");
                            ImGui::SetCursorPos(ImVec2(350, 110));
                            ImGui::Text("FOV Amount");
                            ImGui::SetCursorPos(ImVec2(350, 140));
                            ImGui::SliderFloat("FOV", &fov, 1.0f, 175.0f, "%1.0f");

                        }

                        if (tab == 4)
                        {
                            ImGui::SetCursorPos(ImVec2(175, 35));
                            ImGui::Text("Colors");
                            bool test2;


                            float col1[3] = { settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z };
                            ImGui::SetCursorPos(ImVec2(170, 80));

                            ImGui::ColorEdit3("2D Box Color", col1, 0);

                            settings::esp::box_color.x = col1[0]; settings::esp::box_color.y = col1[1]; settings::esp::box_color.z = col1[2];
                            float col2[3] = { settings::esp::loot_esp::loot_color.x, settings::esp::loot_esp::loot_color.y, settings::esp::loot_esp::loot_color.z };
                            ImGui::SetCursorPos(ImVec2(170, 110));

                            ImGui::ColorEdit3("Loot Color", col2, 0);
                            settings::esp::loot_esp::loot_color.x = col2[0]; settings::esp::loot_esp::loot_color.y = col2[1]; settings::esp::loot_esp::loot_color.z = col2[2];
                            float col3[3] = { settings::aim::aim_circle_color.x, settings::aim::aim_circle_color.y, settings::aim::aim_circle_color.z };
                            ImGui::SetCursorPos(ImVec2(170, 140));
                            ImGui::ColorEdit3("Field of view Color", col3, 0);
                            settings::aim::aim_circle_color.x = col3[0]; settings::aim::aim_circle_color.y = col3[1]; settings::aim::aim_circle_color.z = col3[2];
                        }

                        if (tab == 5)
                        {
                            ImGui::SetCursorPos(ImVec2(175, 35));
                            ImGui::Text("Loot");
                            bool test2;
                            float fov;
                            ImGui::SetCursorPos(ImVec2(170, 50));
                            ImGui::Checkbox("Render Corpse", &settings::corpse);
                            ImGui::SetCursorPos(ImVec2(170, 80));
                            ImGui::Checkbox("Render Items", &settings::esp::is_loot_esp);
                            ImGui::SetCursorPos(ImVec2(170, 110));
                            ImGui::SliderFloat("Distance", &settings::esp::loot_esp::max_distance, 100.0f, 500.0f);
                            ImGui::SetCursorPos(ImVec2(170, 140));
                            ImGui::SliderFloat("Price", &settings::esp::loot_esp::min_price, 100.0f, 10000000.0f);

                        }

                    }

                }
                ImGui::PopStyleColor(12);
                ImGui::End();
            }

            int width = 100;
            float rainbowSpeed = 0.01;
            static float staticHue = 0;
            staticHue -= rainbowSpeed;
            ImColor cRainbow;
            if (staticHue < -1.f) staticHue += 1.f;
            for (int i = 0; i < width; i++)
            {
                float hue = staticHue + (1.f / (float)width) * i;
                if (hue < 0.f) hue += 1.f;
                cRainbow = ImColor::HSV(hue, 1.f, 1.f);
            }


            ImDrawList* draw_list = ImGui::GetForegroundDrawList();

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (settings::esp::is_loot_esp)
            {
                for (auto& loot : loot_list.world_loot_list)
                {

                    if (settings::corpse)
                    {
                        std::string line1 = loot.short_name + " [" + std::to_string((int)loot.distance) + "]";
                        ImVec2 text_size = ImGui::CalcTextSize2(line1.c_str(), 12.f);
                        draw_list->AddText(ImVec2(loot.location.x - text_size.x / 2, loot.location.y + text_size.y / 2), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::esp::loot_esp::loot_color.x, settings::esp::loot_esp::loot_color.y, settings::esp::loot_esp::loot_color.z, 1)), line1.c_str(), NULL, NULL, 12.f);
                        if (loot.short_name != "Corpse")
                            draw_list->AddText(ImVec2(loot.location.x - text_size.x / 2, loot.location.y + (text_size.y / 2) + 10), ImGui::ColorConvertFloat4ToU32(ImVec4(settings::esp::loot_esp::loot_color.x, settings::esp::loot_esp::loot_color.y, settings::esp::loot_esp::loot_color.z, 1)), std::to_string(loot.price).c_str(), NULL, NULL, 12.f);

                    }
                 
                }
            }
            if (settings::esp::show_extracts)
            {
                for (auto& temp : exfil_list.extract_info_list)
                {
                    draw_list->AddText(ImVec2(temp.screen_pos.x, temp.screen_pos.y), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), (temp.name + "[" + std::to_string((int)temp.distance) + "m]").c_str(), NULL, NULL, 12.f);
                }
            }

            if (settings::is_esp)
            {
                for (auto& info : vars::drawing_list)
                {
                    float height = info.Base_Position.y - info.Head_Position.y;
                    float width = height / 2.f;

                    float x = info.Base_Position.x - (width / 2.f);
                    float y = info.Head_Position.y;
                   

                    if (settings::box)
                    {
                             draw_box(ImVec2(x, y), ImVec2(x + width, y + height), draw_list);

                    }

                    if (settings::snaplinesnigga)
                    {
                        draw_list->AddLine(ImVec2(ScreenCenterX, ScreenCenterY * 2), ImVec2(info.Base_Position.x, info.Base_Position.y), ImColor(255.0f, 0.0f, 255.0f, 1.0f), 1.0f);
                    }

                    if (settings::corner)
                    {
                        DrawCorneredBox(x, y, width, height, cRainbow, 3);
                        DrawCorneredBox(x, y, width, height, ImColor(0.0f, 0.0f, 0.0f, 1.0f), 4);
                        DrawCorneredBox(x, y, width, height, cRainbow, 2);


                    }
                    if (settings::is_aimbot && vars::aim_player && settings::esp::show_aim_line)
                    {
                        draw_list->AddLine(ImVec2(ScreenCenterX, ScreenCenterY), ImVec2(vars::target_info.PlayerPos.x, vars::target_info.PlayerPos.y), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), 1.f);
                    }

                    if (settings::esp::show_health)
                    {
                      
                        std::string health = "[ HP " + std::to_string(int(info.p_info.health)) + " ]";
                        ImVec2 text_size = ImGui::CalcTextSize2(health.c_str(), 12.f);

                        draw_list->AddText(ImVec2(info.Base_Position.x - text_size.x / 2, y + height + text_size.y * 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), health.c_str(), NULL, NULL, 12.f);

                        draw_list->AddRect(ImVec2(x + width * 1.1, y + height), ImVec2(x + width * 1.1, y + (height - height * info.p_info.health)), ImColor(healthr, healthg, healthb), 1.5);
                    }
                    if (settings::esp::show_role)
                    {
                        std::string name = info.p_info.type;
                        if (settings::esp::show_distance)
                        {
                            name.append(" [" + std::to_string(info.p_info.distance) + "m]");
                        }
                        ImVec2 text_size = ImGui::CalcTextSize2(name.c_str(), 12.f);
                        draw_list->AddText(ImVec2(info.Base_Position.x - text_size.x / 2, y + height + text_size.y / 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), name.c_str(), NULL, NULL, 12.f);
                    }
                    else if (settings::esp::show_distance)
                    {
                        std::string distance = "[" + std::to_string(info.p_info.distance) + "]";
                        ImVec2 text_size = ImGui::CalcTextSize2(distance.c_str(), 12.f);
                        draw_list->AddText(ImVec2(info.Base_Position.x - text_size.x / 2, y + height + text_size.y / 2), ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)), distance.c_str(), NULL, NULL, 12.f);
                    }

                    if (settings::skeleton)
                    {
                        draw_list->AddLine(ImVec2(info.Skeleton_Head_position.x, info.Skeleton_Head_position.y), ImVec2(info.Neck.x, info.Neck.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Head to Neck
                        draw_list->AddLine(ImVec2(info.Neck.x, info.Neck.y), ImVec2(info.Pevlis.x, info.Pevlis.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Neck to Pelvis

                        draw_list->AddLine(ImVec2(info.Neck.x, info.Neck.y), ImVec2(info.Left_Upper_Arm.x, info.Left_Upper_Arm.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Neck to UL Arm
                        draw_list->AddLine(ImVec2(info.Neck.x, info.Neck.y), ImVec2(info.Right_Upper_Arm.x, info.Right_Upper_Arm.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Neck to UR Arm
                        draw_list->AddLine(ImVec2(info.Right_Upper_Arm.x, info.Right_Upper_Arm.y), ImVec2(info.Right_Forearm.x, info.Right_Forearm.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // UR to LR Arm
                        draw_list->AddLine(ImVec2(info.Left_Upper_Arm.x, info.Left_Upper_Arm.y), ImVec2(info.Left_Forearm.x, info.Left_Forearm.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // UL to LL Arm

                        draw_list->AddLine(ImVec2(info.Pevlis.x, info.Pevlis.y), ImVec2(info.Left_Leg.x, info.Left_Leg.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Pelvis to UL Leg
                        draw_list->AddLine(ImVec2(info.Pevlis.x, info.Pevlis.y), ImVec2(info.Right_Leg.x, info.Right_Leg.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Pelvis to UR Leg
                        draw_list->AddLine(ImVec2(info.Left_Leg.x, info.Left_Leg.y), ImVec2(info.Left_Leg2.x, info.Left_Leg2.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // UL to LL Leg
                        draw_list->AddLine(ImVec2(info.Right_Leg.x, info.Right_Leg.y), ImVec2(info.Right_Leg2.x, info.Right_Leg2.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // UR to LR Leg

                        draw_list->AddLine(ImVec2(info.Left_Leg2.x, info.Left_Leg2.y), ImVec2(info.Left_Foot.x, info.Left_Foot.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Lower L Leg to Left foot
                        draw_list->AddLine(ImVec2(info.Right_Leg2.x, info.Right_Leg2.y), ImVec2(info.Right_Foot.x, info.Right_Foot.y), ImColor(settings::esp::box_color.x, settings::esp::box_color.y, settings::esp::box_color.z), 2); // Lower R Leg to Right foot
                    }
                }
            }

            if (settings::aim::enable_fov_circle)
                draw_list->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), settings::aim::aim_fov, ImGui::ColorConvertFloat4ToU32(ImVec4(settings::aim::aim_circle_color.x, settings::aim::aim_circle_color.y, settings::aim::aim_circle_color.z, 1)), 0, 1.f);

            ImGui::EndFrame();

            g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);

            ImVec4 clear_color = ImVec4(0, 0, 0, 0);
            g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clear_color);

            ImGui::Render();
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            g_pSwapChain->Present(0, 0);
        }
        Shutdown();
        return 0;
    }
}