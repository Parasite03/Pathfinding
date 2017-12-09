#include "GuiManager.h"
#include "../../Clock.h"

sf::RenderWindow* GuiManager::render_window_;

sfg::SFGUI GuiManager::sfgui_;
sfg::Window::Ptr GuiManager::window_;
sfg::Desktop GuiManager::desktop_;
sfg::Button::Ptr GuiManager::button_;

GuiManager::GuiManager()
{

}

GuiManager::~GuiManager()
{

}

void GuiManager::Initialize(sf::RenderWindow* render_window)
{
	render_window_ = render_window;

	window_ = sfg::Window::Create();
	window_->SetTitle("Pathfinding");

	button_ = sfg::Button::Create("Hello");
	window_->Add(button_);

	desktop_.Add(window_);

	
}

void GuiManager::HandleEvent(const sf::Event event)
{
	window_->HandleEvent(event);
}

void GuiManager::Update()
{
	desktop_.Update(kClock.getElapsedTime().asSeconds());
	sfgui_.Display(*render_window_);
}
