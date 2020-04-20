#ifndef STATE
#define STATE

#include <iostream>
#include <vector>
#include <utility>
using std::vector;
using std::pair;

class Board {

private:
	vector<vector<int>> puzzles;
	// heuristic function : numbers of cells that are not in the correct place
	int h;
	// path lenght
	int g;
	// the sum of h and g
	int f;

	Board* parent;

	void swapEl(int x, int y, int newX, int newY);

public:
	Board(vector<vector<int>> puzzles);
	Board(const Board& rhs);
	Board* generateChilds(int x, int y,int pos);

	bool operator==(const Board& rhs);
	bool operator<(const Board& rhs);
	void calculateHeuristic(const Board& final);
	void calculatePath(const Board& parent);
	void setParent(Board* parent);
	void calculateF();

	bool canGenerate(int x, int y, int pos);
	pair<int,int> getCoordinates()const;
	int getF() const;
	void printBoard();
	void printPath();
	vector<vector<int>> getPuzzles()const;
};


#endif STATE
