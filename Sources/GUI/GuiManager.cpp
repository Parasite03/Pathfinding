#include "GuiManager.h"
#include "../../Clock.h"

GuiManager::GuiManager()
{

}

GuiManager::GuiManager(sf::RenderWindow* render_window)
{
	render_window_ = render_window;

	// Setting up the interface
	
	// Painting box
	paint_blank_button_ = sfg::Button::Create();
	paint_blank_button_->SetLabel("Blank");
	paint_wall_button_ = sfg::Button::Create();
	paint_wall_button_->SetLabel("Wall");
	paint_start_button_ = sfg::Button::Create();
	paint_start_button_->SetLabel("Start");
	paint_end_button_ = sfg::Button::Create();
	paint_end_button_->SetLabel("End");

	painting_box_ = sfg::Box::Create();
	//painting_box_->SetTitle("Painting");
	painting_box_->Pack(paint_blank_button_);
	painting_box_->Pack(paint_wall_button_);
	painting_box_->Pack(paint_start_button_);
	painting_box_->Pack(paint_end_button_);

	// Map management box
	create_map_button_ = sfg::Button::Create();
	create_map_button_->SetLabel("Create Map");
	load_map_button_ = sfg::Button::Create();
	load_map_button_->SetLabel("Load Map");
	save_map_button_ = sfg::Button::Create();
	save_map_button_->SetLabel("Save Map");

	map_management_box_ = sfg::Box::Create();
	map_management_box_->Pack(create_map_button_);
	map_management_box_->Pack(load_map_button_);
	map_management_box_->Pack(save_map_button_);

	// Add boxes to a window
	box_ = sfg::Box::Create();
	box_->Pack(painting_box_);
	box_->Pack(map_management_box_);

	// Add the box to the window and te windw o the desktop
	window_ = sfg::Window::Create();
	window_->Add(box_);
	desktop_.Add(window_);
}


GuiManager::~GuiManager()
{

}

void GuiManager::HandleEvent(const sf::Event event)
{
	window_->HandleEvent(event);
}

void GuiManager::Update()
{
	desktop_.Update(kClock.getElapsedTime().asSeconds());
	//sfgui_.Display(*render_window_);
}

sfg::SFGUI GuiManager::GetSfgui()
{
	return sfgui_;
}
