#include "Gui.h"

#include "../../Clock.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui-SFML.h"
#include "../Map/MapRenderer.h"
#include "../Map/Map.h"

sf::RenderWindow* Gui::window_;

sf::Texture Gui::wall_;
sf::Texture Gui::blank_;
sf::Texture Gui::start_;
sf::Texture Gui::end_;
char Gui::width[8], Gui::height[8];

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

	wall_.loadFromFile("./Data/Textures/wall.png");
	blank_.loadFromFile("./Data/Textures/blank.png");
	start_.loadFromFile("./Data/Textures/start.png");
	end_.loadFromFile("./Data/Textures/end.png");
}

void Gui::Update()
{
	ImGui::SFML::Update(*window_, kClock.restart());

	ImGui::Begin("Paint", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({5, 5});

	if (ImGui::ImageButton(wall_)) 
	{
		MapRenderer::SetPaintingMode(TileType::Wall);
	}

	if (ImGui::ImageButton(blank_))
	{
		MapRenderer::SetPaintingMode(TileType::Blank);
	}

	if (ImGui::ImageButton(start_))
	{
		MapRenderer::SetPaintingMode(TileType::Start);
	}

	if (ImGui::ImageButton(end_))
	{
		MapRenderer::SetPaintingMode(TileType::End);
	}

	ImGui::End();

	ImGui::Begin("Map", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::SetWindowPos({ 65, 5 });

	if (ImGui::Button("New"))
	{
		Map::Create(atoi(width), atoi(height));
	}

	ImGui::InputText("Width", width, 8);
	ImGui::InputText("Height", height, 8);

	if (ImGui::Button("Save"))
	{
		Map::Save("new_map.txt");
	}

	if (ImGui::Button("Load"))
	{
		Map::Load("./Data/Maps/test_map.txt");
	}

	ImGui::End();
}

void Gui::Draw()
{
	ImGui::SFML::Render(*window_);
}

