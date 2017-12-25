#include "Gui.h"
#include <Map>

#include "../../Clock.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui-SFML.h"
#include "../Map/MapRenderer.h"
#include "../Map/Map.h"
#include "../Utilities/FileBrowser.h"

sf::RenderWindow* Gui::window_;

sf::Texture Gui::wall_;
sf::Texture Gui::blank_;
sf::Texture Gui::start_;
sf::Texture Gui::end_;
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

	wall_.loadFromFile("./Data/Textures/wall.png");
	blank_.loadFromFile("./Data/Textures/blank.png");
	start_.loadFromFile("./Data/Textures/start.png");
	end_.loadFromFile("./Data/Textures/end.png");
}

void Gui::Update()
{
	ImGui::SFML::Update(*window_, kClock.restart());

	// Painting window
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

	// Map window
	ImGui::Begin("Map", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
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

	if (ImGui::BeginCombo("", "Select Algorithm"))
	{
		//if (ImGui::Selectable())

		ImGui::EndCombo();
	}

	if (ImGui::Button("Find Path"))
	{
		
	}

	ImGui::End();
}

void Gui::Draw()
{
	ImGui::SFML::Render(*window_);
}

