# ifndef QUEENS_H
# define QUEENS_H
# include <cstdlib>


// An abstract chess piece that cannot be instantiated.

class Piece {
protected:
    int _row, _column;

public:
    int row() const {
	return _row;
    }

    int column() const {
	return _column;
    }

    void place(int row, int column) {
	_row = row;
	_column = column;
    }

    virtual bool menaces(const Piece *p) const = 0;
};

//Can move any number of times horizontally or vertically - no diagonal
class Rook : virtual public Piece 
{
public:
	virtual bool menaces(const Piece *p) const 
	{
		int rows = abs(_row - p->row());
		int columns = abs(_column - p->column());
		return (rows == 0 || columns == 0);
	}
};

//Can move any number of times diagonally - no horizontal or vertical
class Bishop : virtual public Piece
{
public:
	virtual bool menaces(const Piece *p) const
	{
		int rows = abs(_row - p->row());
		int columns = abs(_column - p->column());
		return (rows == columns);//check this
	}
};

//Can move 2 spaces horizontally and 1 space vertically or vice versa
class Knight : virtual public Piece
{
public:
	virtual bool menaces(const Piece *p) const
	{
		int rows = abs(_row - p->row());
		int columns = abs(_column - p->column());
		return ((rows == 2 && columns == 1) || (rows == 1 && columns == 2));
	}
};

//Can move as either a rook or a bishop
class Queen : virtual public Rook, virtual public Bishop
{
public:
	virtual bool menaces(const Piece *p) const
	{
		return Rook::menaces(p) || Bishop::menaces(p);
	}
};

//Can move as either a queen or a knight
class Amazon : virtual public Queen, virtual public Knight
{
public:
	virtual bool menaces(const Piece *p) const
	{
		return Queen::menaces(p) || Knight::menaces(p);
	}
};
# endif /* QUEENS_H */
