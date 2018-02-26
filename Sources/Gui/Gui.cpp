#include "Gui.h"
#include <Map>
#include <sstream>
#include "../../Clock.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui-SFML.h"
#include "../Map/MapRenderer.h"
#include "../Map/Map.h"
#include "../Utilities/FileBrowser.h"
#include "../Algorithms/Algorithm.h"

sf::RenderWindow* Gui::window_;

sf::Texture Gui::wall_;
sf::Texture Gui::blank_;
sf::Texture Gui::start_;
sf::Texture Gui::end_;
Algorithm Gui::selected_algorithm_;

sf::Time Gui::run_time_;
double Gui::memory_baseline_;
double Gui::memory_used_;
bool Gui::use_8_directions_;
bool Gui::is_running_;
int Gui::path_length_;
char width[8] = "50", height[8] = "50";

Gui::Gui()
{

}

Gui::~Gui()
{

}

void Gui::Initialize(sf::RenderWindow* window)
{
	ImGui::SFML::Init(*window);
	window_ = window;
	use_8_directions_ = true;
	is_running_ = false;
	memory_used_ = 0;
	path_length_ = 0;

	wall_.loadFromFile("./Data/Textures/wall.png");
	blank_.loadFromFile("./Data/Textures/blank.png");
	start_.loadFromFile("./Data/Textures/start.png");
	end_.loadFromFile("./Data/Textures/end.png");

	InitializeAlgorithms();
}

void Gui::Update()
{
	ImGui::SFML::Update(*window_, kClock.restart());

	// Disable imgui.ini
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;

	// Painting window
	ImGui::Begin("Paint", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({5, 5});

	if (ImGui::ImageButton(wall_)) 
		MapRenderer::SetPaintingMode(TileType::Wall);
	if (ImGui::ImageButton(blank_))
		MapRenderer::SetPaintingMode(TileType::Blank);
	if (ImGui::ImageButton(start_))
		MapRenderer::SetPaintingMode(TileType::Start);
	if (ImGui::ImageButton(end_))
		MapRenderer::SetPaintingMode(TileType::End);

	ImGui::End();

	// Map window
	ImGui::Begin("Map", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({ 68, 5 });

	if (ImGui::Button("New"))
	{
		Map::Create(atoi(width), atoi(height));
	}

	ImGui::InputText("Width", width, 8);
	ImGui::InputText("Height", height, 8);

	if (ImGui::Button("Load"))
	{
		std::string path = FileBrowser::OpenFile("Load Map...");
		if (path != std::string())
			Map::Load(path);
	}

	ImGui::SameLine();
	if (ImGui::Button("Save"))
	{
		std::string path = FileBrowser::SaveFile("Save Map...");
		if (path != std::string())
			Map::Save(path);
	}

	ImGui::End();

	// Algorithm window

	ImGui::Begin("Algorithms", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

	ImGui::SetWindowPos({ 343, 5 });

	if (ImGui::BeginCombo("", algorithm_names.at(selected_algorithm_).c_str()))
	{
		for (auto algorithm : algorithm_names)
			if (ImGui::Selectable(algorithm.second.c_str(), algorithm.first == selected_algorithm_))
			{
				selected_algorithm_ = algorithm.first;
			}
		
		ImGui::EndCombo();
	}

	if (ImGui::Button("Find Path"))
	{
		if (!is_running_)
		{
			Map::GetMap()->ClearAlgorithmResults();
			CreateThread(nullptr, 0, &ProcessAlgorithm, nullptr, 0, nullptr);
		}
	}

	ImGui::SameLine();
	if (ImGui::Button("Clear Results"))
	{
		Map::GetMap()->ClearAlgorithmResults();
	}

	if (ImGui::Button("Dump Time"))
	{
		std::fstream file("./results.txt");
		file << time << std::endl;
		file.close();
	}

	ImGui::Checkbox("8 Directions", &use_8_directions_);

	char time[15];
	char path[15];

	//std::stringstream ss(std::stringstream::in | std::stringstream::out);
	//ss << memory_used_;
	//std::string memory_str = ss.str();

	sprintf_s(time, "%f", run_time_.asSeconds());
	_itoa_s(path_length_, path, 10);

	ImGui::Text("Time:"); ImGui::SameLine();
	ImGui::Text(time); ImGui::SameLine();
	ImGui::Text("seconds");

	ImGui::Text("Path:"); ImGui::SameLine();
	ImGui::Text(path); ImGui::SameLine();
	(path_length_ == 1) ? ImGui::Text("tile") : ImGui::Text("tiles");

	//ImGui::Text("Memory:"); ImGui::SameLine();
	//ImGui::Text(memory_str.c_str()); ImGui::SameLine();
	//ImGui::Text("MB");

	ImGui::End();
}

void Gui::Draw()
{
	ImGui::SFML::Render(*window_);
}

void Gui::SetRunTime(sf::Time time)
{
	run_time_ = time;
}

void Gui::SetPathLength(int path_length)
{
	path_length_ = path_length;
}

void Gui::SetRunning(bool is_running)
{
	is_running_ = is_running;
}

void Gui::SetMemoryBaseline(double memory)
{
	memory_baseline_ = memory;
	memory_used_ = memory;
}

void Gui::SetMemory(double memory)
{
	if (memory_baseline_ - memory > memory_used_)
		memory_used_ = memory_baseline_ - memory;
}

bool Gui::Get8Directions()
{
	return use_8_directions_;
}


Algorithm Gui::GetSelectedAlgorithm()
{
	return selected_algorithm_;
}

