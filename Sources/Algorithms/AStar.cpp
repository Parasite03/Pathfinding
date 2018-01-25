#include "AStar.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"
#include <algorithm>
#include "../Utilities/MemoryUsage.h"

void AStar::FindPath()
{
	Map* map = Map::GetMap();

	Gui::SetRunning(true);
	sf::Clock clock;
	Gui::SetMemoryBaseline(GetVirtualMemoryUsage());

	setWorldSize({ map->GetWidth(), map->GetHeight() });
	setDiagonalMovement();
	setHeuristic(&Heuristic::manhattan);
	setCollisionMap();

	Node *current = nullptr;
	NodeSet openSet, closedSet;
	openSet.insert(new Node(ftoi(map->GetStart())));

	clock.restart();

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

			uint totalCost = current->G_ + ((i < 4) ? 10 : 14);

			Node *successor = findNodeOnList(openSet, newCoordinates);
			if (successor == nullptr) 
			{
				successor = new Node(newCoordinates, current);
				successor->G_ = totalCost;
				successor->H_ = heuristic_(successor->coordinates_, ftoi(map->GetEnd()));
				map->GetTile(itof(successor->coordinates_))->SetType(TileType::Checked);
				openSet.insert(successor);
			}
			else if (totalCost < successor->G_) 
			{
				successor->parent_ = current;
				successor->G_ = totalCost;
			}
			Gui::SetMemory(GetVirtualMemoryUsage());
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

void AStar::addCollision(sf::Vector2i coordinates)
{
	walls_.push_back(coordinates);
}

bool AStar::detectCollision(sf::Vector2i coordinates)
{
	if (coordinates.x < 0 || coordinates.x >= world_size_.x ||
		coordinates.y < 0 || coordinates.y >= world_size_.y ||
		std::find(walls_.begin(), walls_.end(), coordinates) != walls_.end()) {
		return true;
	}
	return false;
}

void AStar::removeCollision(sf::Vector2i coordinates)
{
	auto it = std::find(walls_.begin(), walls_.end(), coordinates);
	if (it != walls_.end()) {
		walls_.erase(it);
	}
}

void AStar::clearCollisions()
{
	walls_.clear();
}

AStar::Node::Node(sf::Vector2i coordinates, Node *parent)
{
	parent_ = parent;
	coordinates_ = coordinates;
	G_ = H_ = 0;
}

AStar::uint AStar::Node::getScore()
{
	return G_ + H_;
}

AStar::Node* AStar::findNodeOnList(NodeSet& nodes, sf::Vector2i coordinates)
{
	for (auto node : nodes) {
		if (node->coordinates_ == coordinates) {
			return node;
		}
	}
	return nullptr;
}

void AStar::releaseNodes(NodeSet& nodes)
{
	for (auto it = nodes.begin(); it != nodes.end();) {
		delete *it;
		it = nodes.erase(it);
	}
}

void AStar::setWorldSize(sf::Vector2i world_size)
{
	world_size_ = world_size;
}

void AStar::setCollisionMap()
{
	Map* map = Map::GetMap();

	for (auto x = 0; x < map->GetWidth(); ++x)
		for (auto y = 0; y < map->GetHeight(); ++y)
			if (map->GetTile(x, y)->GetType() == TileType::Wall)
				addCollision({ x, y });
}

void AStar::setDiagonalMovement()
{
	directions_ = (Gui::Get8Directions() ? 8 : 4);

	direction_ = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

void AStar::setHeuristic(HeuristicFunction heuristic)
{
	heuristic_ = heuristic;
}

sf::Vector2i AStar::ftoi(sf::Vector2f vector)
{
	return { (int)vector.x, (int)vector.y };
}

sf::Vector2f AStar::itof(sf::Vector2i vector)
{
	return { (float)vector.x, (float)vector.y };
}

sf::Vector2i Heuristic::getDelta(sf::Vector2i source, sf::Vector2i target)
{
	return{ abs(source.x - target.x),  abs(source.y - target.y) };
}

Heuristic::uint Heuristic::manhattan(sf::Vector2i source, sf::Vector2i target)
{
	auto delta = std::move(getDelta(source, target));
	return static_cast<uint>(10 * (delta.x + delta.y));
}

Heuristic::uint Heuristic::euclidean(sf::Vector2i source, sf::Vector2i target)
{
	auto delta = std::move(getDelta(source, target));
	return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

Heuristic::uint Heuristic::octagonal(sf::Vector2i source, sf::Vector2i target)
{
	auto delta = std::move(getDelta(source, target));
	return 10 * (delta.x + delta.y) + (-6) * min(delta.x, delta.y);
}