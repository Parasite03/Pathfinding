#pragma once

#include "BaseAlgorithm.h"
#include <functional>
#include <set>

class SecondLeeAlgorithm : public BaseAlgorithm
{
public:
	using uint = unsigned int;
	using CoordinateList = std::vector<sf::Vector2i>;

	struct Node
	{
		uint G_;
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

	sf::Vector2i ftoi(sf::Vector2f vector);
	sf::Vector2f itof(sf::Vector2i vector);

private:
	CoordinateList direction_, walls_;
	sf::Vector2i world_size_;
	uint directions_;

};