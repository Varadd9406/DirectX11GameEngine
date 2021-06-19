#pragma once
#define DX_EXCEPT( hr ) Graphics::DxException( __LINE__,__FILE__,hr )
#define DX_EXCEPT_THROW( hr ) if(FAILED(hr)) throw DX_EXCEPT(hr)
#define DX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw Graphics::InfoException( __LINE__,__FILE__,v);}}



#define INFOMAN(gfx) HRESULT hr; DxgiManager& infoManager = GetInfoManager((gfx))