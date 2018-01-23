#pragma once

#include "BaseAlgorithm.h"
#include <vector>
#include <functional>
#include <set>

class AStar : public BaseAlgorithm
{
private:
	using uint = unsigned int;
	using HeuristicFunction = std::function<uint(sf::Vector2i, sf::Vector2i)>;
	using CoordinateList = std::vector<sf::Vector2i>;

	struct Node
	{
		uint G_, H_;
		sf::Vector2i coordinates_;
		Node *parent_;

		Node(sf::Vector2i coord, Node *parent = nullptr);
		uint getScore();
	};

	using NodeSet = std::set<Node*>;

	void FindPath() override;
	
	void addCollision(sf::Vector2i coordinates);
	bool detectCollision(sf::Vector2i coordinates);
	void removeCollision(sf::Vector2i coordinates);
	void clearCollisions();
	
	Node* findNodeOnList(NodeSet& nodes, sf::Vector2i coordinates);
	void releaseNodes(NodeSet& nodes);

	void setWorldSize(sf::Vector2i worldSize);
	void setCollisionMap();
	void setDiagonalMovement();
	void setHeuristic(HeuristicFunction heuristic);
	
	sf::Vector2i ftoi(sf::Vector2f vector);
	sf::Vector2f itof(sf::Vector2i vector);

private:
	HeuristicFunction heuristic_;
	CoordinateList direction_, walls_;
	sf::Vector2i world_size_;
	uint directions_;

};

class Heuristic
{
	using uint = unsigned int;

	static sf::Vector2i getDelta(sf::Vector2i source, sf::Vector2i target_);

public:
	static uint manhattan(sf::Vector2i source, sf::Vector2i target);
	static uint euclidean(sf::Vector2i source, sf::Vector2i target);
	static uint octagonal(sf::Vector2i source, sf::Vector2i target);
};