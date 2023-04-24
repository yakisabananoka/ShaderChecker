#pragma once

class Application
{
public:
	Application() = default;
	~Application();

	bool Run(void);

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	Application(Application&&) = default;
	Application& operator=(Application&&) = default;

private:
	bool Initialize(void);
	void Update(void);
};
