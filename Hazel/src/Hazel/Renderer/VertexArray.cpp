#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:   HZ_CORE_ASSERT(false, "RendererAPI::None do not support!"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();

			HZ_CORE_ASSERT(false, "Unknown RenderAPI");
			return nullptr;
		}
	}
}