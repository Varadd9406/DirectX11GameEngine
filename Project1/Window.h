#pragma once
#include "Winhead.h"
#include "WinException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"

#include <memory>
#include <optional>

class Window
{
public:
	class Exception : public WinException
	{
	public:
		Exception(int line, const char* file, HRESULT hr);
		const char* what() const override;
		const char* GetType() const;
		static std::string TranslateErrorCode(HRESULT hr) ;
		HRESULT GetErrorCode() const;
		std::string GetErrorString() const;
	private:
		HRESULT hr; 
	};

private:
	class WindowClass
	{
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator = (const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Window_class_name";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator= (const Window&) = delete;
	static std::optional<int> ProcessMessage();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	Keyboard kbd;
	Mouse mouse;
private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;
};


