#pragma once
#include "../Algorithms/Algorithms.h"

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

	static Algorithms selected_algorithm_;

	static sf::Time run_time_;
	static DWORDLONG virtualMemUsedPassive_;
	static DWORDLONG virtualMemUsedActive_;

public:
	static void Initialize(sf::RenderWindow* window);
	static void Update();
	static void Draw();
	static void SetRunTime(sf::Time time);
	static void SetVirtualMemUsedActive(DWORDLONG mem);
	static DWORDLONG GetVirtualMemUsedActive();
	static void SetVirtualMemUsedPassive(DWORDLONG mem);
	static Algorithms GetSelectedtAlgorithm();
};

