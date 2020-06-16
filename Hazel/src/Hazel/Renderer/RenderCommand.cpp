#include "hzpch.h"
#include "RenderCommand.h"
#include "Hazel/Platform/OpenGL/OpenGLRenererAPI.h"

namespace Hazel {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
