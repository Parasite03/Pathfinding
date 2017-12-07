#pragma once

class LeeAlgorithm
{
public:
	static void FindPath(sf::Vector2f start_position, sf::Vector2f end_position, short number_of_directions);
	static void ShowPath();
	static void ResetPath();

	static void SetStartPosition(const short x, const short y);
	static void SetStartPosition(const sf::Vector2f position);
	static sf::Vector2f GetStartPosition();

	static void SetEndPosition(const short x, const short y);
	static void SetEndPosition(const sf::Vector2f position);
	static sf::Vector2f GetEndPosition();

	static short GetDirectionCount();

private:
	static LeeAlgorithm current_algorithm_;

	short direction_count_;
	int path_length_ = 0;

	sf::Vector2f start_position_;
	sf::Vector2f end_position_;

	std::vector<sf::Vector2f> path_;

	LeeAlgorithm();
	~LeeAlgorithm();
};

