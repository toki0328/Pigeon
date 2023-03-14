#include <Pigeon.h>


class Sandbox : public Pigeon::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Pigeon::Application* Pigeon::CreateApplication()
{
	return new Sandbox;

}