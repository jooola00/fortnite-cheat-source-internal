//imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

//d3d11 overlay
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

//Hooking
#include "minhook/MinHook.h"
#pragma comment(lib, "minhook.lib");

//others
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <map>
#include <stdio.h>
#include <psapi.h>
#include <intrin.h>
#include <string>
#include <vector>
#include <winnt.h>

#include "xorstr.h"
#include "xor.hpp"