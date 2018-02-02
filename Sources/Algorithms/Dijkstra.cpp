#include "Dijkstra.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"

void Dijkstra::FindPath()
{
	Map* map = Map::GetMap();

	Gui::SetRunning(true);
	sf::Clock clock;
	
		setWorldSize({ map->GetWidth(), map->GetHeight() });
		setDiagonalMovement();
		setCollisionMap();

		Node *current = nullptr;
		NodeSet openSet, closedSet;

		clock.restart();

		openSet.insert(new Node(ftoi(map->GetStart())));

		while (!openSet.empty())
		{
			current = *openSet.begin();
			for (auto node : openSet)
			{
				if (node->getScore() <= current->getScore())
				{
					current = node;
				}
			}

			if (current->coordinates_ == ftoi(map->GetEnd()))
			{
				break;
			}

			closedSet.insert(current);
			openSet.erase(std::find(openSet.begin(), openSet.end(), current));

			for (uint i = 0; i < directions_; ++i)
			{
				sf::Vector2i newCoordinates(current->coordinates_ + direction_[i]);
				if (detectCollision(newCoordinates) || findNodeOnList(closedSet, newCoordinates))
				{
					continue;
				}

				uint totalCost = current->g_cost_ + ((i < 4) ? 10 : 14);

				Node *successor = findNodeOnList(openSet, newCoordinates);
				if (successor == nullptr)
				{
					successor = new Node(newCoordinates, current);
					successor->g_cost_ = totalCost;
					map->GetTile(itof(successor->coordinates_))->SetType(TileType::Checked);
					openSet.insert(successor);
				}
				else if (totalCost < successor->g_cost_)
				{
					successor->parent_ = current;
					successor->g_cost_ = totalCost;
				}
			}
		}

		CoordinateList path;
		while (current != nullptr)
		{
			path.push_back(current->coordinates_);
			map->GetTile(itof(current->coordinates_))->SetType(TileType::Path);
			current = current->parent_;
		}

		Gui::SetPathLength(path.size());

		map->GetTile(map->GetStart())->SetType(TileType::Start);
		map->GetTile(map->GetEnd())->SetType(TileType::End);

		Gui::SetRunTime(clock.getElapsedTime());
		Gui::SetRunning(false);
		
		clearCollisions();
		releaseNodes(openSet);
		releaseNodes(closedSet);
		
}

void Dijkstra::addCollision(sf::Vector2i coordinates)
{
	walls_.push_back(coordinates);
}

bool Dijkstra::detectCollision(sf::Vector2i coordinates)
{
	if (coordinates.x < 0 || coordinates.x >= world_size_.x ||
		coordinates.y < 0 || coordinates.y >= world_size_.y ||
		std::find(walls_.begin(), walls_.end(), coordinates) != walls_.end()) {
		return true;
	}
	return false;
}

void Dijkstra::removeCollision(sf::Vector2i coordinates)
{
	auto it = std::find(walls_.begin(), walls_.end(), coordinates);
	if (it != walls_.end()) {
		walls_.erase(it);
	}
}

void Dijkstra::clearCollisions()
{
	walls_.clear();
}

Dijkstra::Node::Node(sf::Vector2i coordinates, Node *parent)
{
	parent_ = parent;
	coordinates_ = coordinates;
	g_cost_ = 0;
}

Dijkstra::uint Dijkstra::Node::getScore()
{
	return g_cost_;
}

Dijkstra::Node* Dijkstra::findNodeOnList(NodeSet& nodes, sf::Vector2i coordinates)
{
	for (auto node : nodes) {
		if (node->coordinates_ == coordinates) {
			return node;
		}
	}
	return nullptr;
}

void Dijkstra::releaseNodes(NodeSet& nodes)
{
	for (auto it = nodes.begin(); it != nodes.end();) {
		delete *it;
		it = nodes.erase(it);
	}
}

void Dijkstra::setWorldSize(sf::Vector2i world_size)
{
	world_size_ = world_size;
}

void Dijkstra::setCollisionMap()
{
	Map* map = Map::GetMap();

	clearCollisions();

	for (auto x = 0; x < map->GetWidth(); ++x)
		for (auto y = 0; y < map->GetHeight(); ++y)
			if (map->GetTile(x, y)->GetType() == TileType::Wall)
				addCollision({ x, y });
}

void Dijkstra::setDiagonalMovement()
{
	directions_ = (Gui::Get8Directions() ? 8 : 4);

	direction_ = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

sf::Vector2i Dijkstra::ftoi(sf::Vector2f vector)
{
	return { (int)vector.x, (int)vector.y };
}

sf::Vector2f Dijkstra::itof(sf::Vector2i vector)
{
	return { (float)vector.x, (float)vector.y };
}