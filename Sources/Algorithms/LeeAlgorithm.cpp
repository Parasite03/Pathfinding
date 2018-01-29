#include "LeeAlgorithm.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"
#include <algorithm>

void LeeAlgorithm::FindPath()
{
	Map* map = Map::GetMap();

	Gui::SetRunning(true);
	sf::Clock clock;

	setWorldSize({ map->GetWidth(), map->GetHeight() });
	setDiagonalMovement();
	setCollisionMap();
	
	uint current_distance = 1;
	bool open_tiles = false;

	Node *current = nullptr;
	NodeSet openSet, closedSet;
	openSet.insert(new Node(ftoi(map->GetStart()), current_distance));

	clock.restart();

	while (!openSet.empty())
	{
		current = *openSet.begin();
		for (auto node : openSet)
		{
			if (node->getScore() == current_distance)
			{
				current = node;
				open_tiles = true;
			}
		}

		if (!open_tiles)
			current_distance++;

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

			Node *successor = findNodeOnList(openSet, newCoordinates);
			if (successor == nullptr)
			{
				successor = new Node(newCoordinates, current_distance + 1, current);
				map->GetTile(itof(successor->coordinates_))->SetType(TileType::Checked);
				openSet.insert(successor);
			}
		}
	}

	CoordinateList path;
	while (current != nullptr) {
		path.push_back(current->coordinates_);
		map->GetTile(itof(current->coordinates_))->SetType(TileType::Path);
		current = current->parent_;
	}

	map->GetTile(map->GetStart())->SetType(TileType::Start);
	map->GetTile(map->GetEnd())->SetType(TileType::End);

	releaseNodes(openSet);
	releaseNodes(closedSet);
	Gui::SetRunTime(clock.getElapsedTime());
	Gui::SetRunning(false);
}

void LeeAlgorithm::addCollision(sf::Vector2i coordinates)
{
	walls_.push_back(coordinates);
}

bool LeeAlgorithm::detectCollision(sf::Vector2i coordinates)
{
	if (coordinates.x < 0 || coordinates.x >= world_size_.x ||
		coordinates.y < 0 || coordinates.y >= world_size_.y ||
		std::find(walls_.begin(), walls_.end(), coordinates) != walls_.end()) {
		return true;
	}
	return false;
}

void LeeAlgorithm::removeCollision(sf::Vector2i coordinates)
{
	auto it = std::find(walls_.begin(), walls_.end(), coordinates);
	if (it != walls_.end()) {
		walls_.erase(it);
	}
}

void LeeAlgorithm::clearCollisions()
{
	walls_.clear();
}

LeeAlgorithm::Node::Node(sf::Vector2i coordinates, Node *parent)
{
	parent_ = parent;
	coordinates_ = coordinates;
	g_cost_ = 0;
}

LeeAlgorithm::Node::Node(sf::Vector2i coordinates, uint g_cost, Node *parent)
{
	parent_ = parent;
	coordinates_ = coordinates;
	g_cost_ = g_cost;
}

LeeAlgorithm::uint LeeAlgorithm::Node::getScore()
{
	return g_cost_;
}

LeeAlgorithm::Node* LeeAlgorithm::findNodeOnList(NodeSet& nodes, sf::Vector2i coordinates)
{
	for (auto node : nodes) {
		if (node->coordinates_ == coordinates) {
			return node;
		}
	}
	return nullptr;
}

void LeeAlgorithm::releaseNodes(NodeSet& nodes)
{
	for (auto it = nodes.begin(); it != nodes.end();) {
		delete *it;
		it = nodes.erase(it);
	}
}

void LeeAlgorithm::setWorldSize(sf::Vector2i world_size)
{
	world_size_ = world_size;
}

void LeeAlgorithm::setCollisionMap()
{
	Map* map = Map::GetMap();

	for (auto x = 0; x < map->GetWidth(); ++x)
		for (auto y = 0; y < map->GetHeight(); ++y)
			if (map->GetTile(x, y)->GetType() == TileType::Wall)
				addCollision({ x, y });
}

void LeeAlgorithm::setDiagonalMovement()
{
	directions_ = (Gui::Get8Directions() ? 8 : 4);

	direction_ = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

sf::Vector2i LeeAlgorithm::ftoi(sf::Vector2f vector)
{
	return { (int)vector.x, (int)vector.y };
}

sf::Vector2f LeeAlgorithm::itof(sf::Vector2i vector)
{
	return { (float)vector.x, (float)vector.y };
}