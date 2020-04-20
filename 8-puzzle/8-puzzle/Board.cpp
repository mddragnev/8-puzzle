#include "Board.h"

Board::Board(vector<vector<int>> puzzles)
{
	this->puzzles = puzzles;
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->parent = nullptr;
}

Board::Board(const Board & rhs)
{
	this->puzzles = rhs.puzzles;
	this->parent = nullptr;
	this->h = 0;
	this->g = 0;
	this->f = 0;
}

pair<int, int> Board::getCoordinates() const
{
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			if (this->puzzles[i][j] == 0) {
				return pair<int, int>(i, j);
			}
		}
	}
}

bool Board::canGenerate(int x, int y, int pos)
{
	bool flag = false;
	switch (pos) {
	case 0: flag = y - 1 >= 0; break;
	case 1: flag = x - 1 >= 0; break;
	case 2: flag = y + 1 <= 2; break;
	case 3: flag = x + 1 <= 2; break;
	}
	return flag;
}

void Board::swapEl(int x, int y, int newX, int newY)
{
	std::swap(this->puzzles[x][y], this->puzzles[newX][newY]);
}

Board* Board::generateChilds(int x, int y, int pos)
{
	pair<int, int> coord = this->getCoordinates();
	switch (pos) {
	case 0: {
		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x, y - 1);
		return newBoard;
		break;
	}
	case(1): {
		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x - 1, y);
		return newBoard;
		break;
	}
	case(2): {

		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x, y + 1);
		return newBoard;
		break;

	}
	case(3): {
		Board* newBoard = new Board(*this);
		newBoard->swapEl(x, y, x + 1, y);
		return newBoard;
		break;

	}
	}
}

bool Board::operator==(const Board& rhs)
{
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		if (this->puzzles[i] != rhs.puzzles[i]) {
			return false;
		}
	}
	return true;
}

bool Board::operator<(const Board & rhs)
{
	return this->f < rhs.f;
}



void Board::calculateHeuristic(const Board& final)
{
	int sum = 0;
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			if (this->puzzles[i][j] != final.puzzles[i][j]) {
				++sum;
			}
		}
	}
	this->h = sum;
}

void Board::calculatePath(const Board& parent)
{
	this->g = parent.g + 1;
}

void Board::setParent(Board * parent)
{
	this->parent = parent;
}

void Board::calculateF()
{
	this->f = this->g + this->h;
}

int Board::getF() const
{
	return this->f;
}

void Board::printBoard()
{
	for (size_t i = 0; i < this->puzzles.size(); ++i) {
		for (size_t j = 0; j < this->puzzles[i].size(); ++j) {
			std::cout << this->puzzles[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Board::printPath()
{
	if (this->parent == nullptr) {
		this->printBoard();
		std::cout << std::endl;
		return;
	}
	this->parent->printPath();
	this->printBoard();
	std::cout << std::endl;
}

vector<vector<int>> Board::getPuzzles() const
{
	return this->puzzles;
}
