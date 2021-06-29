#pragma once
#include "Window.h"
#include "Timer.h"
#include<memory>
#include "ImguiManger.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include "TestPlane.h"
class App
{
	
public:
	App();
	int Go();
private:
	void DoFrame();
	void ImguiStuff();
private:
	int x=0, y=0;
	float speed_factor = 1.0f;
	ImguiManager imgui;
	Window wnd;
	Timer timer;
	Camera cam;
	PointLight light;
	MODEL_DESC hammer_time_desc =
	{
		"Models\\Rune_Hammer\\Rune_Hammer.fbx",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Albedo.png",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Normal.png",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Metallic.png",
		"Models\\Rune_Hammer\\Textures\\Rune_Hammer_Emission.png"

	};
	Model hammer_time{ wnd.Gfx(),hammer_time_desc };

	MODEL_DESC sword_time_desc =
	{
		"Models\\Rune_Sword\\Rune_Sword.fbx",
		"Models\\Rune_Sword\\Textures\\Rune_Sword_Albedo.png",
		"Models\\Rune_Sword\\Textures\\Rune_Sword_Normal.png",
		"Models\\Rune_Sword\\Textures\\Rune_Sword_Metallic.png",
		"Models\\Rune_Sword\\Textures\\Rune_Sword_Emission.png"

	};
	Model sword_time{ wnd.Gfx(),sword_time_desc };
	//TestPlane plane;
	struct
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	} pos;
};