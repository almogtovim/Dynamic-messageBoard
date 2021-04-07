//
// Created by tovim on 04/04/2021.
//

#ifndef MESSAGEBOARD_B_MASTER_BOARD_HPP
#define MESSAGEBOARD_B_MASTER_BOARD_HPP

#include <iostream>
#include <sstream>

typedef unsigned int pos;
using String = std::string;
class Point{
    pos x_, y_;
public:
    Point(pos a, pos b);
    Point();
    pos getX();
    void setX(pos x);
    pos getY();
    void setY(pos y);
    String toString();
};


#include "Direction.hpp"

class Poster{
    Point start;
    Point end;
    ariel::Direction dir_;
    String message_;
public:
    Poster();
    String toString();
    Poster(Point pStart, ariel::Direction dir, String text);
    Point getStart();
    Point getEnd();
    ariel::Direction getDir();
    String getMessage();
    void setMessage(String str);
    bool include(Point a);
    char getCharAt(pos num);
};


#include <iostream>
#include <stack>
#include <sstream>
#include <vector>
using String = std::string;

typedef unsigned int pos;
const pos GROWTH_FACTOR = 2;
using Stack = std::stack<Poster>;

namespace ariel {
    class Board {
        pos rRange_;
        pos dRange_;
        std::vector<std::vector<char>> board;
        Stack lastPosts;

        void writeVboard(Poster p);
        void allocHori(pos size);
        void allocVerti(pos size);

    public:

        Board();
        String read(pos row, pos col, ariel::Direction direct, pos length);
        void printVboard();
        void post(pos row, pos col, ariel::Direction direct, String message);
        void show();

    };
}


#endif //MESSAGEBOARD_B_MASTER_BOARD_HPP
