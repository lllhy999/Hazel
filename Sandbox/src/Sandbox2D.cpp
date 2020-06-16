#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name),m_Func(func), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}
	
	~Timer()
	{
		if (!m_Stopped)
		{
			Stop();
		}
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		std::cout << m_Name << ": " << duration << "ms" << std::endl;
		m_Func({m_Name, duration});
	}

	
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); } )

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckboardTexture = Hazel::Texture2D::Create("assets/textures/hq.png");
	
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	
	Hazel::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
	Hazel::RenderCommand::Clear();
	
	static float rotation = 0.0f;
	rotation += ts * 20.0f;
	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f}, { 0.8f, 0.8f},-45.0f, {0.8f,0.2f,0.3f,1.0f});
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f,0.2f,0.3f,1.0f });
	Hazel::Renderer2D::DrawQuad({ 0.5f ,-0.5f },{ 0.5f,0.75f }, { 0.2f,0.3f,0.8f,1.0f });
	Hazel::Renderer2D::DrawQuad(glm::vec3(0.0f), { 10.0f,10.0f }, m_CheckboardTexture, 10.0f );
	Hazel::Renderer2D::DrawRotatedQuad({ -2.0f ,0.0f, 0.0f }, { 1.0f,10.0f }, rotation, m_CheckboardTexture, 20.0f);
	Hazel::Renderer2D::EndScene();

	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
		
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();

}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}
