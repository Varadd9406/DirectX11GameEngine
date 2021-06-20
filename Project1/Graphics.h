#pragma once
#include "Winhead.h"
#include "WinException.h"
#include "DxgiManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include<DirectXMath.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

class Graphics
{
	friend class Bindable;
public:
	class Exception : public WinException
	{
		using WinException::WinException;
	};
	class DxException : public Exception
	{
	public:
		DxException(int line, const char* file, HRESULT hr);
		const char* what() const override;
		const char* GetType() const;
		static std::string TranslateErrorCode(HRESULT hr);
		HRESULT GetErrorCode() const;
		std::string GetErrorString() const;
	private:
		HRESULT hr;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) ;
		const char* what() const  override;
		const char* GetType() const  override;
		std::string GetErrorInfo() const ;
	private:
		std::string info;
	};
	Graphics(HWND hWnd,int width,int height);
	Graphics(const Graphics&) = delete;
	Graphics& operator= (const Graphics) = delete;
	~Graphics() = default;
	void EndFrame();
	void BeginFrame();
	void ClearBuffer(float red, float green, float blue);
	void DrawIndexed(UINT count);
	void SetProjection(DirectX::FXMMATRIX proj);
	DirectX::XMMATRIX GetProjection() const;
	void SetCamera(DirectX::FXMMATRIX cam);
	DirectX::XMMATRIX GetCamera() const;
	void EnableImgui();
	void DiableImgui();
	bool IsImguiEnabled() const;
private:
	bool imguiEnabled = true;
	HRESULT hr;
	DxgiManager infoManager;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};