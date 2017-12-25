#pragma once

enum class Algorithm
{
	Lee
};

class Gui
{
private:
	Gui();
	~Gui();

	static sf::RenderWindow* window_;

	static sf::Texture wall_;
	static sf::Texture blank_;
	static sf::Texture start_;
	static sf::Texture end_;

	static Algorithm selected_algorithm_;

public:
	static void Initialize(sf::RenderWindow* window);
	static void Update();
	static void Draw();
};

