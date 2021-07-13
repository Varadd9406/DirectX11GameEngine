#pragma once
#include "Graphics.h"
#include "Bindable.h"
#include <DirectXMath.h>
#include <memory>
#include "IndexBuffer.h"
#include "Technique.h"



namespace bind
{
	class IndexBuffer;
	class VertexBuffer;
	class Topology;
	class InputLayout;
}


class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void AddTechnique(std::unique_ptr<Technique> tech_in) ;
	virtual DirectX::XMMATRIX GetTransformXM() const = 0;
	void Submit(class FrameCommander& frame) ;
	void Bind(Graphics& gfx) ;
	UINT GetIndexCount() ;
	virtual ~Drawable();
protected:
	std::shared_ptr<bind::IndexBuffer> pIndices;
	std::shared_ptr<bind::VertexBuffer> pVertices;
	std::shared_ptr<bind::Topology> pTopology;
	std::vector<std::shared_ptr<Technique>> techniques;
};