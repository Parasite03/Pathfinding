#include "LeeAlgorithm.h"
#include "../Map/Map.h"

LeeAlgorithm  LeeAlgorithm::current_algorithm_;

LeeAlgorithm::LeeAlgorithm()
{

}

LeeAlgorithm::~LeeAlgorithm()
{

}

void LeeAlgorithm::FindPath(sf::Vector2f start_position, sf::Vector2f end_position, short direction_count)
{

	current_algorithm_ = LeeAlgorithm();

	SetStartPosition(start_position);
	SetEndPosition(end_position);

	current_algorithm_.direction_count_ = direction_count;

	std::vector<short> y_direction;
	std::vector<short> x_direction;

	if (current_algorithm_.direction_count_ == 4)
	{
		y_direction = { 1, 0, -1, 0 };
		x_direction = { 0, 1, 0, -1 };
	}
	else
		if (current_algorithm_.direction_count_ == 8)
		{
			y_direction = { 1, 1, 0, -1, -1, -1, 0, 1 };
			x_direction = { 0, 1, 1, 1, 0, -1, -1, -1 };
		}

	LeeAlgorithm::ResetPath();

	bool stop;
	short distance = 0;
	sf::Vector2f path;

	Map::GetTile(LeeAlgorithm::GetStartPosition())->g_cost = distance;

	do {
		stop = true;
		for (auto y = 0; y < Map::GetHeight(); ++y)
			for (auto x = 0; x < Map::GetWidth(); ++x)
			{
				if (Map::GetTile(x, y)->g_cost == distance)
				{
					for (auto i = 0; i < LeeAlgorithm::GetDirectionCount(); ++i)
					{
						int iy = y + y_direction.at(i), ix = x + x_direction.at(i);
						if (iy >= 0 && ix >= 0 && iy < Map::GetHeight() && ix < Map::GetWidth() && Map::GetTile(ix, iy)->g_cost == -1)
						{
							stop = false;
							Map::GetTile(ix, iy)->g_cost = distance + 1;
							Map::GetTile(ix, iy)->type = TILE_CHECKED;
						}
					}
				}
			}
		distance++;
	} while (!stop && Map::GetTile(LeeAlgorithm::GetEndPosition())->g_cost == -1);

	if (Map::GetTile(LeeAlgorithm::GetEndPosition())->g_cost == -1) return;

	// Trace path

	current_algorithm_.path_length_ = Map::GetTile(LeeAlgorithm::GetEndPosition())->g_cost;
	path = LeeAlgorithm::GetEndPosition();
	distance = current_algorithm_.path_length_;

	while (distance > 0)
	{
		current_algorithm_.path_.push_back(path);
		distance--;
		for (auto i = 0; i < LeeAlgorithm::GetDirectionCount(); ++i)
		{
			int iy = path.y + y_direction.at(i), ix = path.x + x_direction.at(i);
			if (iy >= 0 && ix >= 0 && iy < Map::GetHeight() && ix < Map::GetWidth() && Map::GetTile(ix, iy)->g_cost == distance)
			{
				path.y += y_direction[i];
				path.x += x_direction[i];
				break;
			}
		}
	}

	current_algorithm_.path_.push_back(LeeAlgorithm::GetStartPosition());

	LeeAlgorithm::ShowPath();

	return;

}

void LeeAlgorithm::ShowPath()
{
	Map::GetTile(LeeAlgorithm::GetStartPosition())->type = TILE_START;
	Map::GetTile(LeeAlgorithm::GetEndPosition())->type = TILE_END;

	for (auto i = 1; i < current_algorithm_.path_length_; ++i)
	{
		Map::GetTile(current_algorithm_.path_.at(i))->type = TILE_PATH;
	}
}

void LeeAlgorithm::ResetPath()
{
	for (auto y = 0; y < Map::GetHeight(); ++y)
		for (auto x = 0; x < Map::GetWidth(); ++x)
		{
			if (Map::GetTile(x, y)->type == TILE_CHECKED || Map::GetTile(x, y)->type == TILE_PATH)
				Map::GetTile(x, y)->type = TILE_BLANK;

			if (Map::GetTile(x, y)->type == TILE_WALL)
				Map::GetTile(x, y)->g_cost = -2;
			else
				Map::GetTile(x, y)->g_cost = -1;
		}
}

void LeeAlgorithm::SetStartPosition(const short x, const short y)
{
	current_algorithm_.start_position_.x = x;
	current_algorithm_.start_position_.y = y;
}

void LeeAlgorithm::SetStartPosition(const sf::Vector2f position)
{
	current_algorithm_.start_position_ = position;
}

sf::Vector2f LeeAlgorithm::GetStartPosition()
{
	return current_algorithm_.start_position_;
}

void LeeAlgorithm::SetEndPosition(const short x, const short y)
{
	current_algorithm_.end_position_.x = x;
	current_algorithm_.end_position_.y = y;
}

void LeeAlgorithm::SetEndPosition(const sf::Vector2f position)
{
	current_algorithm_.end_position_ = position;
}

sf::Vector2f LeeAlgorithm::GetEndPosition()
{
	return current_algorithm_.end_position_;
}

short LeeAlgorithm::GetDirectionCount()
{
	return current_algorithm_.direction_count_;
}