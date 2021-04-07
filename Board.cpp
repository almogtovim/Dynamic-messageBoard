//
// Created by tovim on 04/04/2021.
//

#include "Board.hpp"
const ariel::Direction HORI = ariel::Direction::Horizontal;
const ariel::Direction VER = ariel::Direction::Vertical;


/* POINT CLASS */
Point::Point(pos a, pos b){
    x_ = a;
    y_ = b;
}
Point::Point(){
    x_ = 0;
    y_ = 0;
}
pos Point::getX(){
    return x_;
}
void Point::setX(pos x){
    x_ = x;
}
pos Point::getY(){
    return y_;
}
void Point::setY(pos y){
    y_ = y;
}
String Point::toString(){
    std::stringstream mySS;
    mySS << " ( " << x_ << "," << y_ << " ) " << std:: endl;
    return mySS.str();
}

/* POSTER CLASS */
Poster::Poster(){
    start = Point();
    end = Point();
    message_ = "";
}

/*    Poster(Poster &x){                     COPY CONSTRUCTOR
        start = x.getStart();
        end = x.getEnd();
        dir_ = x.getDir();
        message_ = x.getMessage();
    } */

String Poster::toString(){
    std::stringstream mySS;
    String dirs;
    if (dir_ == HORI){
        dirs = "Hortizontal";
    } else {
        dirs = "Vertical";
    }
    mySS << "Poster start point: " << start.toString() << "Poster end point: " << end.toString() << "Poster dir: " << dirs << "\n"<< "Poster text: " << message_ << std::endl;
    return mySS.str();
}
Poster::Poster(Point pStart, ariel::Direction dir, String text){
    start = pStart;
    dir_ = dir;
    message_ = text;
    pos length = (pos)text.length();
    switch (dir) {
        case (VER):
            end =  Point(start.getX()+length,start.getY());
            break;
        case (HORI):
            end =  Point(start.getX(),start.getY()+length);
            break;
    }
}
Point Poster::getStart(){
    return start;
}
Point Poster::getEnd(){
    return end;
}
ariel::Direction Poster::getDir(){
    return dir_;
}
String Poster::getMessage(){
    return message_;
}
void Poster::setMessage(String str){
    message_ = std::move(str);
}
bool Poster::include(Point a){
    switch (dir_) {
        case (HORI):
            return (a.getX() >= start.getX() && a.getX() <= end.getX() && a.getY() == end.getY());
            break;
        case (VER):
            return (a.getX() == start.getX() && a.getY() >= start.getY() && a.getY() <= end.getY());
            break;
    }
}
char Poster::getCharAt(pos num) {
    return message_.at(num);
}

/* BOARD CLASS */
using vBoard = std::vector<std::vector<char>>;

void ariel::Board::writeVboard(Poster p) {
    pos row = p.getStart().getX();
    pos col = p.getStart().getY();
    int length = p.getMessage().length();
    switch (p.getDir()) {
        case (HORI):
            for (pos k = 0; k < length; ++k) {
                board[row][col + k] = p.getCharAt(k);
            }
            break;
        case (VER):
            for (pos k = 0; k < length; ++k) {
                board[row + k][col] = p.getCharAt(k);
            }
            break;
    }
}
ariel::Board::Board() {
    rRange_ = 2;
    dRange_ = 2;
    std::vector<char> tmp;
    tmp.push_back('_');
    tmp.push_back('_');
    board.push_back(tmp);
    board.push_back(tmp);
}

String ariel::Board::read(pos row, pos col, ariel::Direction direct, pos length) {
    String str(length ,'_');
    Point startp = Point(row, col);
    Poster toRead = Poster(startp, direct, str);
    if((startp.getX() >= dRange_) || (startp.getY() >= rRange_)) {
        return str;
    }
    if(toRead.getEnd().getX() > dRange_){
        length = dRange_ - toRead.getStart().getX() ;
    }
    if(toRead.getEnd().getY() > rRange_){
        length = rRange_ - toRead.getStart().getY();
    }

    switch (direct) {
        case (HORI):
            for (pos k = 0; k < length; ++k) {
                str.at(k) = board[row][col + k];
            }
            break;
        case (VER):
            for (pos k = 0; k < length; ++k) {
                str.at(k) = board[row+ k][col ];
            }
            break;
    }

    return str;
}

void ariel::Board::printVboard() {
    for (pos i = 0; i < dRange_; ++i) {
        for (pos j = 0; j < rRange_; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
//    std::cout << "dRange: " << dRange_<< "rRange: " << rRange_ << std::endl;
//    std::cout << "colSize: " << board.size()<< "  " << "rowSize: " << board[0].size()<< std::endl;
}
void ariel::Board::allocHori(pos size){
try {
for (pos i = 0; i < dRange_ ; ++i) {
board[i].resize(size, '_');
}
rRange_ = size;
}
catch (...) {
std::cout << "Allocation faild" << std::endl;
}
}
void ariel::Board::allocVerti(pos size){
try {
for (pos i = dRange_ - 1; i < size-1; ++i) {
std::vector<char> tmp;
tmp.resize(board[0].size(), '_');
board.push_back(tmp);
}
//                board.resize(newSize);
dRange_ = size;
} catch (...) {
std::cout << "Allocation faild" << std::endl;
}
}
void ariel::Board::post(pos row, pos col, ariel::Direction direct, String message) {
    Point newPoint = Point(row, col);
    if (message.length() > 0) {
        Poster newPost = Poster(newPoint, direct, message);
        lastPosts.push(newPost);
        if (newPost.getEnd().getX() >= dRange_) {
            pos newSize = newPost.getEnd().getX() * (GROWTH_FACTOR);
            allocVerti(newSize);
        }
        if (newPost.getEnd().getY() >= rRange_) {
            pos newSize = newPost.getEnd().getY() * (GROWTH_FACTOR);
            allocHori(newSize);
        }
        writeVboard(newPost);
    }
}

void ariel::Board::show(){
    printVboard();
    std::cout << "LAST POSTERS ARE : " <<std::endl;
    for (int i = 0; i < 9; ++i) {
        std::cout << lastPosts.top().toString() << std::endl;
        lastPosts.pop();
    }
}


