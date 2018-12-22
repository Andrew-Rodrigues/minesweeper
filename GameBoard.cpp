//
// Created by Andrew Rodrigues on 11/22/18.
//

#include "GameBoard.h"
#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <fstream>

GameBoard::GameBoard() {
    numBombs = 50;
    numFlagged = numBombs;
    //totalTiles = totalTiles - numBombs;
    restart = false;

    for(int i = 0; i < width; i++){
        std::vector<Tile> t;
        for(int j = 0; j < height; j++){
            Tile temp;
            temp.x = i;
            temp.y = j;
            temp.sprite.setPosition(i*32,j*32);
            t.push_back(temp);
        }
        gameBoard.push_back(t);
    }

}

void GameBoard::SetMines() {

    std::random_device rand;
    std:: mt19937 rng(rand());
    std:: uniform_int_distribution<int> x (0, width -1); // random x coordinate
    std:: uniform_int_distribution<int> y (0, height -1); // random y coordinate

    int counter = 0;

        do {
            int xCord = x(rng);
            int yCord = y(rng);

            Tile temp;
            temp = gameBoard[xCord][yCord];

            if (!temp.bomb) {
                gameBoard[xCord][yCord].bomb = true;
                gameBoard[xCord][yCord].contents.setPosition(xCord * 32, yCord * 32);
                counter++;

            }

        } while(numBombs > counter);

}





void GameBoard::TileFlagged(int x, int y, GameBoard board) {
    gameBoard[x][y].flag.setPosition(gameBoard[x][y].sprite.getPosition());
    gameBoard[x][y].state = Tile::State::Flagged;
    numFlagged--;
}

void GameBoard::AdjacentTiles() {

    for(int i = 0; i < width; i ++){
        for(int j = 0; j < height; j++) {

            if(!gameBoard[i][j].bomb && i != 0 && j != 0 && i != width - 1 && j != height - 1){ // Middle of the Game Board
                SetAdjacentTiles(i,j);
            }

            if(!gameBoard[i][j].bomb && i == 0 && j == 0){ // Left Top Corner of Game Board
                Tile *temp;
                Tile *temp2;
                Tile *temp3;

                temp = &gameBoard[i+1][j];
                temp2 = &gameBoard[i][j+1];
                temp3 = &gameBoard[i+1][j+1];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
            }

            if(!gameBoard[i][j].bomb && i == 0 && j < height-1 && j!=0){ // Left side of Game Board
                Tile * temp;
                Tile * temp2;
                Tile * temp3;
                Tile * temp4;
                Tile * temp5;

                temp = &gameBoard[i][j-1];
                temp2 = &gameBoard[i+1][j-1];
                temp3 = &gameBoard[i+1][j];
                temp4 = &gameBoard[i+1][j+1];
                temp5 = &gameBoard[i][j+1];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
                gameBoard[i][j].adjTiles.push_back(temp4);
                gameBoard[i][j].adjTiles.push_back(temp5);

            }

          if(!gameBoard[i][j].bomb && i == 0 && j ==height-1){ //Bottom Left Corner
                Tile *temp;
                Tile *temp2;
                Tile *temp3;

                temp = &gameBoard[i][j-1];
                temp2= &gameBoard[i+1][j];
                temp3 = &gameBoard[i+1][j-1];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);


            }

            if(!gameBoard[i][j].bomb && i < width-1 && j == height-1 && i !=0){ // Bottom Row
                Tile * temp;
                Tile * temp2;
                Tile * temp3;
                Tile * temp4;
                Tile * temp5;

                temp = &gameBoard[i-1][j];
                temp2 = &gameBoard[i-1][j-1];
                temp3 = &gameBoard[i][j-1];
                temp4 = &gameBoard[i+1][j-1];
                temp5 = &gameBoard[i+1][j];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
                gameBoard[i][j].adjTiles.push_back(temp4);
                gameBoard[i][j].adjTiles.push_back(temp5);
            }

            if(!gameBoard[i][j].bomb && i == width-1 && j ==height-1){ //Bottom Right Corner
                Tile *temp;
                Tile *temp2;
                Tile *temp3;

                temp = &gameBoard[i-1][j-1];
                temp2= &gameBoard[i][j-1];
                temp3 = &gameBoard[i-1][j];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
            }

            if(!gameBoard[i][j].bomb && i == width-1  && j < height-1 && j != 0){ // Far Right
                Tile * temp;
                Tile * temp2;
                Tile * temp3;
                Tile * temp4;
                Tile * temp5;

                temp = &gameBoard[i][j-1];
                temp2 = &gameBoard[i-1][j-1];
                temp3 = &gameBoard[i-1][j];
                temp4 = &gameBoard[i-1][j+1];
                temp5 = &gameBoard[i][j+1];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
                gameBoard[i][j].adjTiles.push_back(temp4);
                gameBoard[i][j].adjTiles.push_back(temp5);
            }

            if(!gameBoard[i][j].bomb && i == width-1 && j == 0){ //Top Right Corner
                Tile *temp;
                Tile *temp2;
                Tile *temp3;

                temp = &gameBoard[i-1][j];
                temp2= &gameBoard[i-1][j+1];
                temp3 = &gameBoard[i][j+1];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
            }

            if(!gameBoard[i][j].bomb && i!=0 && j == 0 && i < width-1 ){ // Top Row
                Tile * temp;
                Tile * temp2;
                Tile * temp3;
                Tile * temp4;
                Tile * temp5;

                temp = &gameBoard[i+1][j];
                temp2 = &gameBoard[i+1][j+1];
                temp3 = &gameBoard[i][j+1];
                temp4 = &gameBoard[i-1][j];
                temp5 = &gameBoard[i-1][j+1];

                gameBoard[i][j].adjTiles.push_back(temp);
                gameBoard[i][j].adjTiles.push_back(temp2);
                gameBoard[i][j].adjTiles.push_back(temp3);
                gameBoard[i][j].adjTiles.push_back(temp4);
                gameBoard[i][j].adjTiles.push_back(temp5);
            }

        }
    }

}

void GameBoard::SetAdjacentTiles(int i, int j) {
    Tile *temp;
    Tile *temp2;
    Tile *temp3;
    Tile *temp4;
    Tile *temp5;
    Tile *temp6;
    Tile *temp7;
    Tile *temp8;

    temp = &gameBoard[i-1][j-1];
    temp2 = &gameBoard[i-1][j];
    temp3 = &gameBoard[i-1][j+1];
    temp4 = &gameBoard[i][j-1];
    temp5 = &gameBoard[i][j+1];
    temp6 = &gameBoard[i+1][j-1];
    temp7 = &gameBoard[i+1][j];
    temp8 = &gameBoard[i+1][j+1];

    gameBoard[i][j].adjTiles.push_back(temp);
    gameBoard[i][j].adjTiles.push_back(temp2);
    gameBoard[i][j].adjTiles.push_back(temp3);
    gameBoard[i][j].adjTiles.push_back(temp4);
    gameBoard[i][j].adjTiles.push_back(temp5);
    gameBoard[i][j].adjTiles.push_back(temp6);
    gameBoard[i][j].adjTiles.push_back(temp7);
    gameBoard[i][j].adjTiles.push_back(temp8);

}



void GameBoard::SurroundingBombs() {

    for(int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if(!gameBoard[i][j].bomb && i != 0 && j != 0 && i != width - 1 && j != height - 1) {
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i == 0 && j == 0) {
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i == 0 && j < height-1){
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i == 0 && j ==height-1){
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i < width && j == height-1 && i != 0){
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i == width-1 && j ==height-1){
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i == width-1  && j < height-1 && j != 0){
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i == width-1 && j == 0){
                FindBombs(i,j);
            }
            if(!gameBoard[i][j].bomb && i!=0 && j == 0 && i < width-1 ){
                FindBombs(i,j);
            }

        }
    }
}

void GameBoard::FindBombs(int i, int j) {
        int bombs = 0;
        for (auto &adjTile : gameBoard[i][j].adjTiles) {
            if (adjTile->bomb) {
                bombs++;
            }
        }
        gameBoard[i][j].adjBomb = bombs;
    }

void GameBoard::ClearBoard() {

    for(int i = 0; i < width; i ++){
        for(int j = 0; j < height; j ++){
            gameBoard[i][j].Clear();
            gameBoard[i][j].bomb = false;
            gameBoard[i][j].adjBomb = 0;
            gameBoard[i][j].state = Tile::State ::Hidden;
        }
    }

}

void GameBoard::RestartGameBoard() {
    ClearBoard(); // clears adj vector and sets adjacent bomb to zero and sets Tile state to Hidden and bomb to false

    numBombs = 50;

    SetMines(); // sets random mines
    AdjacentTiles(); // pushes adjacent tiles to vector
    SurroundingBombs(); //  finds surrounding bombs each tile

    numFlagged = numBombs;
    restart = false;
    //totalTiles = height * width - numBombs;

    mode = GameBoard::Mode ::Play;

}

void GameBoard::RecursiveTileReveal(float x, float y) {
    gameBoard[x][y].TileReveal();
}


void GameBoard::LoadTest1() {
    std::ifstream file;
     file.open("boards/testboard.brd");

     if(file.is_open()){
        std::string line;
        int row = 0;
        int counter = 0;
        while(getline(file, line)){
            for(int i = 0; i < 25; i++){
                if(line[i] == '1'){
                    gameBoard[i][row].bomb = true;
                    counter++;
                }
            }
            row++;
        }
        numBombs = counter;
         file.close();

     }else{
         std::cout << "File NOT OPEN" << std:: endl;
     }
}

void GameBoard::LoadTest2() {
    std::ifstream file;
    file.open("boards/testboard2.brd");

    if(file.is_open()){
        std::string line;
        int row = 0;
        int bombCounter = 0;
        while(getline(file, line)){
            for(int i = 0; i < width; i++){
                if(line[i] == '1'){
                    gameBoard[i][row].bomb = true;
                    bombCounter++;
                }
            }
            row++;
        }

        numBombs = bombCounter;
        file.close();

    }else{
        std::cout << "File NOT OPEN" << std:: endl;
    }
}

void GameBoard::Test1() {
    ClearBoard();
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            gameBoard[i][j].adjBomb = 0;
            gameBoard[i][j].state = Tile::State ::Hidden;
        }
    }
    LoadTest1();
    AdjacentTiles();
    SurroundingBombs();
    numFlagged = numBombs;
    //totalTiles = height * width - numBombs;
    restart = false;
}

void GameBoard::Test2() {
    ClearBoard();
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            gameBoard[i][j].adjBomb = 0;
            gameBoard[i][j].state = Tile::State ::Hidden;
        }
    }

    LoadTest2();
    AdjacentTiles();
    SurroundingBombs();

    numFlagged = numBombs;
    //totalTiles = height * width - numBombs;
    restart = false;

}

bool GameBoard::Win() {

    for(int i = 0; i < width; i ++){
        for(int j = 0; j < height; j++){
            if(gameBoard[i][j].state == Tile ::State::Flagged && !gameBoard[i][j].bomb){
                return false;
            }
            if(gameBoard[i][j].state == Tile::State::Hidden && !gameBoard[i][j].bomb){
                return false;
            }
        }
    }

    return true;
}

void GameBoard::DrawNum(sf::RenderWindow & window, std::map<std::string, sf::Texture> & textures) {
    int countDown = numFlagged;
    std::vector<int> digits;


    sf::Sprite ones;
    sf::Sprite tens;
    sf::Sprite hundreds;

    int onesPlace = countDown % 10;
    countDown = countDown / 10;
    digits.push_back(onesPlace);

    int tensPlace = countDown % 10;
    countDown = countDown /10;
    digits.push_back(tensPlace);

    int hundredsPlace = countDown % 10;
    digits.push_back(hundredsPlace);

    if(numFlagged <= 0 || mode == GameBoard::Mode::Win){
        ones.setTexture(textures["digits"]);
        ones.setTextureRect(sf::IntRect(0,0,32,32));
        ones.setPosition(0, 512);
        window.draw(ones);

        tens.setTexture(textures["digits"]);
        tens.setTextureRect(sf::IntRect(0,0,32,32));
        tens.setPosition(32, 512);
        window.draw(tens);

        hundreds.setTexture(textures["digits"]);
        hundreds.setTextureRect(sf::IntRect(0,0,32,32));
        hundreds.setPosition(64, 512);
        window.draw(hundreds);

    }

    else if(numFlagged < 400 && numFlagged > 0){
        int one = digits[0];
        int ten = digits[1];
        int hun = digits[2];

        ones.setTexture(textures["digits"]);
        ones.setTextureRect(sf::IntRect(21*hun,0,21,32));
        ones.setPosition(0, 512);
        window.draw(ones);

        tens.setTexture(textures["digits"]);
        tens.setTextureRect(sf::IntRect(21*ten,0,21,32));
        tens.setPosition(32, 512);
        window.draw(tens);

        hundreds.setTexture(textures["digits"]);
        hundreds.setTextureRect(sf::IntRect(21*one,0,21,32));
        hundreds.setPosition(64, 512);
        window.draw(hundreds);


    }
}


