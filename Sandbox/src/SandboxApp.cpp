// 客户端

#include <Pigeon.h>	// 链接的Pigeon项目（添加引用）

class ExampleLayer : public Pigeon::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		PG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Pigeon::Event& event) override
	{
		PG_TRACE("{0}", event.ToString());
	}
};

class Sandbox : public Pigeon::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {}
};

// 创建应用程序的部分交给引擎端去实现
Pigeon::Application* Pigeon::CreateApplication()
{
	return new Sandbox();
}
