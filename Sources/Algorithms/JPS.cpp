//#include "AStar.h"
//
//#include <algorithm>
//#include <fstream>
//
//#include "../Map/Map.h"
//#include "../Map/Tile.h"
//#include "../Gui/Gui.h"
//#include "../Utilities/MemoryUsage.h"
//
//
//void JPS::FindPath()
//{
//	Map* map = Map::GetMap();
//
//	Gui::SetRunning(true);
//	sf::Clock clock;
//	Gui::SetMemoryBaseline(GetVirtualMemoryUsage());
//
//	setWorldSize({ map->GetWidth(), map->GetHeight() });
//	setDiagonalMovement();
//	setHeuristic(&Heuristic::manhattan);
//	setCollisionMap();
//
//	Node *current = nullptr;
//	NodeSet openSet, closedSet;
//
//	clock.restart();
//
//	openSet.insert(new Node(ftoi(map->GetStart())));
//
//	while (!openSet.empty())
//	{
//		current = *openSet.begin();
//		for (auto node : openSet)
//		{
//			if (node->getScore() <= current->getScore())
//			{
//				current = node;
//			}
//		}
//
//		if (current->coordinates_ == ftoi(map->GetEnd()))
//		{
//			break;
//		}
//
//		closedSet.insert(current);
//		openSet.erase(std::find(openSet.begin(), openSet.end(), current));
//
//		for (uint i = 0; i < directions_; ++i)
//		{
//			/*sf::Vector2i newCoordinates(current->coordinates_ + direction_[i]);
//			if (detectCollision(newCoordinates) || findNodeOnList(closedSet, newCoordinates))
//			{
//				continue;
//			}
//
//			uint totalCost = current->G_ + ((i < 4) ? 1 : 14);*/
//
//			Node *successor = nullptr;
//
//
//			if (successor == nullptr)
//			{
//				successor = new Node(newCoordinates, current);
//				successor->G_ = totalCost;
//				successor->H_ = heuristic_(successor->coordinates_, ftoi(map->GetEnd()));
//				map->GetTile(itof(successor->coordinates_))->SetType(TileType::Checked);
//				openSet.insert(successor);
//			}
//			else if (totalCost < successor->G_)
//			{
//				successor->parent_ = current;
//				successor->G_ = totalCost;
//			}
//		}
//	}
//
//	CoordinateList path;
//	while (current != nullptr) {
//		path.push_back(current->coordinates_);
//		map->GetTile(itof(current->coordinates_))->SetType(TileType::Path);
//		current = current->parent_;
//	}
//
//	Gui::SetPathLength(path.size());
//
//	map->GetTile(map->GetStart())->SetType(TileType::Start);
//	map->GetTile(map->GetEnd())->SetType(TileType::End);
//
//	Gui::SetRunTime(clock.getElapsedTime());
//	Gui::SetRunning(false);
//
//	releaseNodes(openSet);
//	releaseNodes(closedSet);
//
//}
//
//void JPS::addCollision(sf::Vector2i coordinates)
//{
//	walls_.push_back(coordinates);
//}
//
//bool JPS::detectCollision(sf::Vector2i coordinates)
//{
//	if (coordinates.x < 0 || coordinates.x >= world_size_.x ||
//		coordinates.y < 0 || coordinates.y >= world_size_.y ||
//		std::find(walls_.begin(), walls_.end(), coordinates) != walls_.end()) {
//		return true;
//	}
//	return false;
//}
//
//void JPS::removeCollision(sf::Vector2i coordinates)
//{
//	auto it = std::find(walls_.begin(), walls_.end(), coordinates);
//	if (it != walls_.end()) {
//		walls_.erase(it);
//	}
//}
//
//void JPS::clearCollisions()
//{
//	walls_.clear();
//}
//
//JPS::Node::Node(sf::Vector2i coordinates, Node *parent)
//{
//	parent_ = parent;
//	coordinates_ = coordinates;
//	G_ = H_ = 0;
//}
//
//JPS::uint JPS::Node::getScore()
//{
//	return G_ + H_;
//}
//
//JPS::Node* JPS::findNodeOnList(NodeSet& nodes, sf::Vector2i coordinates)
//{
//	for (auto node : nodes) {
//		if (node->coordinates_ == coordinates) {
//			return node;
//		}
//	}
//	return nullptr;
//}
//
//void JPS::releaseNodes(NodeSet& nodes)
//{
//	for (auto it = nodes.begin(); it != nodes.end();) {
//		delete *it;
//		it = nodes.erase(it);
//	}
//}
//
//void JPS::setWorldSize(sf::Vector2i world_size)
//{
//	world_size_ = world_size;
//}
//
//void JPS::setCollisionMap()
//{
//	Map* map = Map::GetMap();
//
//	clearCollisions();
//
//	for (auto x = 0; x < map->GetWidth(); ++x)
//		for (auto y = 0; y < map->GetHeight(); ++y)
//			if (map->GetTile(x, y)->GetType() == TileType::Wall)
//				addCollision({ x, y });
//}
//
//void JPS::setDiagonalMovement()
//{
//	directions_ = (Gui::Get8Directions() ? 8 : 4);
//
//	direction_ = {
//		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
//		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
//	};
//}
//
//void JPS::setHeuristic(HeuristicFunction heuristic)
//{
//	heuristic_ = heuristic;
//}
//
//sf::Vector2i JPS::ftoi(sf::Vector2f vector)
//{
//	return { (int)vector.x, (int)vector.y };
//}
//
//sf::Vector2f JPS::itof(sf::Vector2i vector)
//{
//	return { (float)vector.x, (float)vector.y };
//}
//
//sf::Vector2i Heuristic::getDelta(sf::Vector2i source, sf::Vector2i target)
//{
//	return{ abs(source.x - target.x),  abs(source.y - target.y) };
//}
//
//Heuristic::uint Heuristic::manhattan(sf::Vector2i source, sf::Vector2i target)
//{
//	auto delta = std::move(getDelta(source, target));
//	return static_cast<uint>(10 * (delta.x + delta.y));
//}
//
//Heuristic::uint Heuristic::euclidean(sf::Vector2i source, sf::Vector2i target)
//{
//	auto delta = std::move(getDelta(source, target));
//	return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
//}
//
//Heuristic::uint Heuristic::octagonal(sf::Vector2i source, sf::Vector2i target)
//{
//	auto delta = std::move(getDelta(source, target));
//	return 10 * (delta.x + delta.y) + (-6) * min(delta.x, delta.y);
//}