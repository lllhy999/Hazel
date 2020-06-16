#include "hzpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "RendererAPI::None do not support!"); return nullptr;
			case RendererAPI::API::OpenGL: return  CreateRef<OpenGLVertexBuffer>(vertices, size);

			HZ_CORE_ASSERT(false, "Unknown RenderAPI");
			return nullptr;
		}
	}

	Ref<Hazel::VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "RendererAPI::None do not support!"); return nullptr;
			case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexBuffer>( size);

			HZ_CORE_ASSERT(false, "Unknown RenderAPI");
			return nullptr;
		}
	}

	VertexBuffer::~VertexBuffer()
	{

	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "RendererAPI::None do not support!"); return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices, count);

			HZ_CORE_ASSERT(false, "Unknown RenderAPI");
			return nullptr;
		}
	}
	IndexBuffer::~IndexBuffer()
	{

	}
}