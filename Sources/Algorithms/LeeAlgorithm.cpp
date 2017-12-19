#include "LeeAlgorithm.h"

LeeAlgorithm LeeAlgorithm::algorithm_;

void LeeAlgorithm::FindPath(sf::Vector2f start_position, sf::Vector2f end_position, short number_of_directions)
{
	// Инициализация
	algorithm_ = LeeAlgorithm();
	Map* map = Map::GetMap();

	// Начальна/конечная позиция - стена, невозможно определить путь
	if (map->GetTile(map->GetStart())->GetType() == TileType::Wall ||
		map->GetTile(map->GetEnd())->GetType() == TileType::Wall) return;

	// Количество направлений
	algorithm_.SetDirectionCount(number_of_directions);

	bool open_tiles;
	short current_distance = 0;

	// Сбросить предыдущий результат
	LeeAlgorithm::ResetPathMap();

	// Стартовая ячейка помечена 0
	algorithm_.tile_distace_.at(map->GetStart().x).at(map->GetStart().y) = current_distance;

	// Распространение волны
	do {
		open_tiles = false;		 // Предполагаем, что все свободные клетки уже проверены

		for (auto y = 0; y < map->GetHeight(); ++y)
			for (auto x = 0; x < map->GetWidth(); ++x)
			{
				if (algorithm_.tile_distace_.at(x).at(y) == current_distance)		// Ячейка помечена current_distance
				{
					// Отмечаем всех непомеченых соседей(в n направлениях) - current_distance + 1

					for (auto i = 0; i < algorithm_.GetNumberOfDirections(); ++i)
					{
						// Находим координаты соседних ячеек(в n направлениях)
						short delta_y = y + algorithm_.offset_by_y_.at(i),
							  delta_x = x + algorithm_.offset_by_x_.at(i);

						if (delta_y >= 0 && delta_x >= 0 && delta_y < map->GetHeight() && delta_x < map->GetWidth()
							&& algorithm_.tile_distace_.at(delta_x).at(delta_y) == -1)
						{
							open_tiles = true;												// Найдены непомеченые ячейки
							algorithm_.checked_tile_.at(delta_x).at(delta_y) = true;		// Сохраняем помеченые ячейки
							algorithm_.tile_distace_.at(delta_x).at(delta_y) = current_distance + 1;
							
						}
					}
				}
			}
		current_distance++;			// Распространение волны
	} while (open_tiles && algorithm_.tile_distace_.at(map->GetEnd().x).at(map->GetEnd().y) == -1);

	if (algorithm_.tile_distace_.at(map->GetEnd().x).at(map->GetEnd().y) == -1) return;			// Путь не найден

	SetBackTrace();			
	ShowCheckedTiles();		
	ShowPath();				

}

void LeeAlgorithm::SetBackTrace()
{
	Map* map = Map::GetMap();

	// Длина кратчайшего пути из начальной ячейки в конечную
	algorithm_.SetPathLength(algorithm_.tile_distace_.at(map->GetEnd().x).at(map->GetEnd().y));

	// Текущие координаты - координаты конечной ячейки
	sf::Vector2f current_tile_position = map->GetEnd();

	short current_distance = algorithm_.GetPathLength();

	// Ищем путь, начиная с конечной ячейки 
	while (current_distance > 0)
	{
		// Сохраняем текущие координаты в путь
		algorithm_.path_map_.push_back(current_tile_position);
		current_distance--;

		for (auto i = 0; i < algorithm_.GetNumberOfDirections(); ++i)
		{
			// Находим координаты соседних ячеек(в n направлениях)
			short delta_y = current_tile_position.y + algorithm_.offset_by_y_.at(i),
				  delta_x = current_tile_position.x + algorithm_.offset_by_x_.at(i);

			if (delta_y >= 0 && delta_x >= 0 && delta_y < map->GetHeight() && delta_x < map->GetWidth()
				&& algorithm_.tile_distace_.at(delta_x).at(delta_y) == current_distance)
			{
				current_tile_position.y = delta_y;			// Текущие координаты - координаты ячейки, помечена current_distance
				current_tile_position.x = delta_x;			// Переходим в ячейку, которая на 1 ближе к старту
				break;
			}
		}
	}

	// Сохраняем координаты начальной ячейки в путь
	algorithm_.path_map_.push_back(map->GetStart());

}

void LeeAlgorithm::ShowPath()
{
	Map* map = Map::GetMap();

	map->GetTile(map->GetStart())->SetType(TileType::Start);
	map->GetTile(map->GetEnd())->SetType(TileType::End);

	for (auto i = 1; i < algorithm_.path_length_; ++i)
		map->GetTile(algorithm_.path_map_.at(i))->SetType(TileType::Path);
}

void LeeAlgorithm::ShowCheckedTiles()
{
	Map* map = Map::GetMap();

	for (auto y = 0; y < map->GetHeight(); ++y)
		for (auto x = 0; x < map->GetWidth(); ++x)
			if (algorithm_.checked_tile_.at(x).at(y))
				map->GetTile(x, y)->SetType(TileType::Checked);
}

void LeeAlgorithm::ResetPathMap()
{
	Map* map = Map::GetMap();

	algorithm_.path_map_.clear();
	algorithm_.tile_distace_.clear();
	algorithm_.checked_tile_.clear();

	for (auto x = 0; x < map->GetWidth(); ++x)
	{
		std::vector<int> tempurary_vector_i;
		std::vector<bool> tempurary_vector_b;

		for (auto y = 0; y < map->GetHeight(); ++y)
		{
			if (map->GetTile(x, y)->GetType() == TileType::Wall)
				tempurary_vector_i.push_back(-2);
			else
				tempurary_vector_i.push_back(-1);

			tempurary_vector_b.push_back(false);
		}
		
		algorithm_.tile_distace_.push_back(tempurary_vector_i);
		algorithm_.checked_tile_.push_back(tempurary_vector_b);
	}
}

void LeeAlgorithm::SetDirectionCount(const short number_of_directions)
{

	// Количество напрвлений
	number_of_directions_ = number_of_directions;

	// Cмещения, соответствующие соседним ячейкам, в n направлений
	if (algorithm_.GetNumberOfDirections() == 4)
	{
		offset_by_x_ = { 1, 0, -1, 0 };
		offset_by_y_ = { 0, 1, 0, -1 };
	}
	else
		if (algorithm_.GetNumberOfDirections() == 8)
		{
			offset_by_x_ = { 1, 1, 0, -1, -1, -1, 0, 1 };
			offset_by_y_ = { 0, 1, 1, 1, 0, -1, -1, -1 };
		}

}

void LeeAlgorithm::SetPathLength(const short path_length)
{
	path_length_ = path_length;
}

unsigned char LeeAlgorithm::GetNumberOfDirections()
{
	return number_of_directions_;
}

short LeeAlgorithm::GetPathLength()
{
	return path_length_;
}

LeeAlgorithm* LeeAlgorithm::GetAlgorithm()
{
	return &algorithm_;
}

LeeAlgorithm::LeeAlgorithm()
{

}

LeeAlgorithm::~LeeAlgorithm()
{

}