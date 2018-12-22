//
// Created by Andrew Rodrigues on 11/22/18.
//

#ifndef MINESWEEPER_GAMEBORARD_H
#define MINESWEEPER_GAMEBORARD_H

#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>


struct GameBoard {
    enum class Mode{
        Play,  Debug,  Lose, Win , Test1, Test2
    };

    std::vector<std::vector<Tile> > gameBoard;
    const int width = 25;
    const int height = 16;
    bool restart;
    int numBombs;
   // int totalTiles = width * height;
    Mode mode = Mode::Play;
    int numFlagged;

    GameBoard();


    void SetMines();

    void TileFlagged(int, int, GameBoard);


    void AdjacentTiles();
    void SetAdjacentTiles(int, int);


    void SurroundingBombs();
    void FindBombs(int,int);
    void ClearBoard();

    void RestartGameBoard();
    void RecursiveTileReveal(float, float);

    void LoadTest1();
    void Test1();

    void LoadTest2();
    void Test2();

    bool Win();

    void DrawNum(sf::RenderWindow&, std::map<std::string, sf::Texture> &);





};


#endif //MINESWEEPER_GAMEBORARD_H
