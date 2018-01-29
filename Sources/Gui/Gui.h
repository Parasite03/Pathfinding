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
	static double memory_baseline_;
	static double memory_used_;
	
	static bool use_8_directions_;
	static bool is_running_;
	static int path_length_;

public:
	static void Initialize(sf::RenderWindow* window);
	static void Update();
	static void Draw();

	static void SetRunTime(sf::Time time);
	static void SetPathLength(int path_length);
	static void SetRunning(bool is_running);

	static void SetMemoryBaseline(double memory);
	static void SetMemory(double memory);

	static bool Get8Directions();
	static Algorithm GetSelectedAlgorithm();
};

