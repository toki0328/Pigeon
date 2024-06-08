// 客户端

#include <Pigeon.h>	// 链接的Pigeon项目（添加引用）

class Sandbox : public Pigeon::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

// 创建应用程序的部分交给引擎端去实现
Pigeon::Application* Pigeon::CreateApplication()
{
	return new Sandbox();
}
