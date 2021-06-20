#include "App.h"
#include<sstream>
#include<random>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"


App::App() :wnd(800,600, "Honey I'm Home"),light(wnd.Gfx())
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10000.0f));
	wnd.Gfx().SetCamera(DirectX::XMMatrixTranslation(0.0f,0.0f, 20.0f));

}




void App::DoFrame()
{
	wnd.Gfx().BeginFrame();
	wnd.Gfx().SetCamera(cam.GetMatrix());
	auto dt = timer.Mark()* speed_factor;
	wnd.Gfx().ClearBuffer(0.07f, 0.0f, 0.12f);
	light.Bind(wnd.Gfx(), cam.GetMatrix());
	const auto transform = DirectX::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	AWP.Draw(wnd.Gfx(), transform);
	light.Draw(wnd.Gfx());

	ImguiStuff();
	cam.SpawnControlWindow();
	light.SpawnControlWindow();
	wnd.Gfx().EndFrame();
}

void App::ImguiStuff()
{
	if (!wnd.Gfx().IsImguiEnabled()) return;
	static char buffer[1024];
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &speed_factor, 0.0f, 6.0f, "%.2f");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", wnd.kbd.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
	}
	ImGui::End();
}


int App::Go()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessage())
		{
			return *ecode;
		}
		DoFrame();
	}
}