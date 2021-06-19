#pragma once
#include "Winhead.h"
#include <string>
#include <wrl.h>
#include <vector>
#include <dxgidebug.h>

class DxgiManager
{
public:
	DxgiManager();
	~DxgiManager() = default;
	DxgiManager(const DxgiManager&) = delete;
	DxgiManager& operator=(const DxgiManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
private:
	unsigned long long next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};