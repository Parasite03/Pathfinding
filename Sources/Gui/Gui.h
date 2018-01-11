#pragma once
#include "../Algorithms/Algorithm.h"

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

	static sf::Time run_time_;
	static DWORDLONG virtual_mem_used_passive_;
	static DWORDLONG virtual_mem_used_active_;
	
	static bool use_8_directions_;

public:
	static void Initialize(sf::RenderWindow* window);
	static void Update();
	static void Draw();

	static void SetRunTime(sf::Time time);
	static void SetVirtualMemUsedActive(DWORDLONG mem);
	static DWORDLONG GetVirtualMemUsedActive();
	static void SetVirtualMemUsedPassive(DWORDLONG mem);

	static bool Get8Directions();
	static Algorithm GetSelectedAlgorithm();
};

