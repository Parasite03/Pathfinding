#include "LeeAlgorithm(ver.2).h"

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"
#include <algorithm>

void SecondLeeAlgorithm::FindPath()
{
	Map* map = Map::GetMap();

	setWorldSize({ map->GetWidth(), map->GetHeight() });
	setDiagonalMovement();
	setCollisionMap();

	uint current_distance = 0;

	Node *current = nullptr;
	NodeSet openSet, closedSet;
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

		for (auto i = 0; i < directions_; ++i)
		{
			sf::Vector2i new_coordinates(current->coordinates_ + direction_[i]);
			if (detectCollision(new_coordinates) || findNodeOnList(closedSet, new_coordinates))
			{
				continue;
			}

			map->GetTile(itof(new_coordinates))->SetType(TileType::Checked);

			Node *successor = findNodeOnList(openSet, new_coordinates);
			if (successor == nullptr)
			{
				successor = new Node(new_coordinates, current);
				successor->G_ = current_distance + 1;
				openSet.insert(successor);
			}
		}
		++current_distance;
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

}

void SecondLeeAlgorithm::addCollision(sf::Vector2i coordinates)
{
	walls_.push_back(coordinates);
}

bool SecondLeeAlgorithm::detectCollision(sf::Vector2i coordinates)
{
	if (coordinates.x < 0 || coordinates.x >= world_size_.x ||
		coordinates.y < 0 || coordinates.y >= world_size_.y ||
		std::find(walls_.begin(), walls_.end(), coordinates) != walls_.end()) {
		return true;
	}
	return false;
}

void SecondLeeAlgorithm::removeCollision(sf::Vector2i coordinates)
{
	auto it = std::find(walls_.begin(), walls_.end(), coordinates);
	if (it != walls_.end()) {
		walls_.erase(it);
	}
}

void SecondLeeAlgorithm::clearCollisions()
{
	walls_.clear();
}

SecondLeeAlgorithm::Node::Node(sf::Vector2i coordinates, Node *parent)
{
	parent_ = parent;
	coordinates_ = coordinates;
	G_ = 0;
}

SecondLeeAlgorithm::uint SecondLeeAlgorithm::Node::getScore()
{
	return G_;
}

SecondLeeAlgorithm::Node* SecondLeeAlgorithm::findNodeOnList(NodeSet& nodes, sf::Vector2i coordinates)
{
	for (auto node : nodes) {
		if (node->coordinates_ == coordinates) {
			return node;
		}
	}
	return nullptr;
}

void SecondLeeAlgorithm::releaseNodes(NodeSet& nodes)
{
	for (auto it = nodes.begin(); it != nodes.end();) {
		delete *it;
		it = nodes.erase(it);
	}
}

void SecondLeeAlgorithm::setWorldSize(sf::Vector2i world_size)
{
	world_size_ = world_size;
}

void SecondLeeAlgorithm::setCollisionMap()
{
	Map* map = Map::GetMap();

	for (auto x = 0; x < map->GetWidth(); ++x)
		for (auto y = 0; y < map->GetHeight(); ++y)
			if (map->GetTile(x, y)->GetType() == TileType::Wall)
				addCollision({ x, y });
}

void SecondLeeAlgorithm::setDiagonalMovement()
{
	directions_ = (Gui::Get8Directions() ? 8 : 4);

	direction_ = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

sf::Vector2i SecondLeeAlgorithm::ftoi(sf::Vector2f vector)
{
	return { (int)vector.x, (int)vector.y };
}

sf::Vector2f SecondLeeAlgorithm::itof(sf::Vector2i vector)
{
	return { (float)vector.x, (float)vector.y };
}