//
// Created by tovim on 07/04/2021.
//

#include "Board.hpp"
using namespace ariel;

int main(){
    ariel::Board b;
    b.post(0, 0, Direction::Horizontal, "        \\\\|||||//        ");
    b.printVboard();
    b.post(1, 0, Direction::Horizontal, "        ( O   O )        ");
    b.printVboard();

    b.post(2, 0, Direction::Horizontal, "|--ooO-----(_)----------|");
    b.printVboard();

    b.post(3, 0, Direction::Horizontal, "|                       |");
    b.printVboard();

    b.post(4, 0, Direction::Horizontal, "|                       |");
    b.printVboard();
    b.post(5, 0, Direction::Horizontal, "|     Message Board     |");
    b.printVboard();
    b.post(6, 0, Direction::Horizontal, "|                       |");
    b.printVboard();
    b.post(7, 0, Direction::Horizontal, "|                       |");
    b.printVboard();
    b.post(8, 0, Direction::Horizontal, "|------------------Ooo--|");
    b.printVboard();
    b.post(9, 0, Direction::Horizontal, "        |__|  |__|       ");
    b.printVboard();
    b.post(10, 0, Direction::Horizontal, "         ||    ||        ");
    b.printVboard();
    b.post(11, 0, Direction::Horizontal, "        ooO    Ooo       ");
    b.printVboard();

    b.printVboard();

    return 0;
}