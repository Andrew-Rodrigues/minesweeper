#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "GameBoard.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>

sf::Texture LoadTextures(std::string s);
std::map<std::string, sf::Texture> Textures();


int main() {
    std:: map<std:: string, sf::Texture> textures;


    GameBoard mineField;

    textures = Textures();

    sf::RenderWindow window(sf::VideoMode(800, 600), "MINE SWEEPER", sf::Style::Default);

    sf::Event event = {};

    window.setVerticalSyncEnabled(true);

    mineField.SetMines();
    mineField.AdjacentTiles();
    mineField.SurroundingBombs();


    while (window.isOpen()) {


        while (window.pollEvent(event)) {

            sf::Vector2i mouse = sf::Mouse::getPosition(window);

            switch (event.type) {

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right) {


                        if (mouse.y < 512) {
                            /*** FLAGGED ***/
                            if (mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state != Tile::State::Flagged &&
                                mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state != Tile::State::Revealed &&
                                 mineField.mode != GameBoard::Mode::Win && mineField.mode != GameBoard::Mode::Lose)  {

                                mineField.TileFlagged(mouse.x/32.0f, mouse.y/32.0f, mineField);


                                std::cout << "RIGHT CLICK" << " x index: " << mouse.x / 32.0f << " y index: "
                                          << mouse.y / 32.0f << std::endl;
                                std::cout << "Number of Flags: " << mineField.numFlagged << std::endl;

                            }
                            /*** UNDO FLAGGED ***/
                            else if (mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state == Tile::State::Flagged &&
                                     mineField.mode != GameBoard::Mode::Win && mineField.mode != GameBoard::Mode::Lose) {

                                mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state = Tile::State::Hidden;
                                mineField.numFlagged++;

                                std::cout << "RIGHT CLICK" << " x index: " << mouse.x / 32.0f << " y index: "
                                          << mouse.y / 32.0f << std::endl;
                                std::cout << "Number of Flags: " << mineField.numFlagged << std::endl;
                            }
                        }

                    }

                    if (event.mouseButton.button == sf::Mouse::Left) {

                        /*** REVEAL TILE ***/
                        if (mouse.y < 512) {
                            if (mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state != Tile::State::Flagged &&
                                mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state != Tile::State::Revealed && mineField.mode != GameBoard::Mode::Lose && mineField.mode != GameBoard::Mode::Win) {

                                /*** EMPTY TILE ***/
                                if(mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].adjBomb == 0 && mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state != Tile::State::Flagged &&
                                   mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state != Tile::State::Revealed && mineField.mode != GameBoard::Mode::Lose && mineField.mode != GameBoard::Mode::Win){
                                    mineField.RecursiveTileReveal(mouse.x / 32.0f, mouse.y / 32.0f);
                                }
                                else {

                                    mineField.gameBoard[mouse.x / 32.0f][mouse.y / 32.0f].state = Tile::State::Revealed;

                                    std::cout << "LEFT CLICK" << " x index: " << mouse.x / 32.0f << " y index: "
                                              << mouse.y / 32.0f
                                              << " " << std::endl;
                                }

                            }

                            if(mineField.gameBoard[mouse.x/32.0f][mouse.y/32.0f].bomb && mineField.mode != GameBoard::Mode::Lose && mineField.mode != GameBoard::Mode::Win){
                                mineField.mode = GameBoard::Mode ::Lose;
                            }

                        }

                        /*** RESTART BUTTON ***/
                        if (mouse.y > 512 && mouse.y < 576 && mouse.x > 368 && mouse.x < 432 ) { // restart button
                            mineField.restart = true;
                        }

                        /*** Debug BUTTON ***/
                        if (mouse.y > 512 && mouse.y < 576 && mouse.x > 496 && mouse.x < 560 && mineField.mode != GameBoard::Mode::Lose && mineField.mode != GameBoard::Mode::Win) { // debug button
                            if(mineField.mode != GameBoard::Mode::Debug) {
                                mineField.mode = GameBoard::Mode::Debug;
                            }
                            else{
                                mineField.mode = GameBoard::Mode ::Play;
                            }
                        }

                        /*** TEST 1 BUTTON ***/
                        if(mouse.y > 512 && mouse.y < 576 && mouse.x >560 && mouse.x < 624){
                            mineField.mode = GameBoard::Mode ::Test1;
                            std::cout << "TEST 1" << std::endl;
                        }

                        /*** TEST 2 BUTTON ***/
                        if(mouse.y > 512 && mouse.y < 576 && mouse.x >624 && mouse.x < 688){
                            mineField.mode = GameBoard::Mode ::Test2;
                            std::cout << "TEST 2" << std::endl;
                        }
                    }


                    break;

                default:
                    break;

            }


            window.clear();


            /*** RESTARTS GAME BOARD ***/
            if(mineField.restart){
                mineField.RestartGameBoard();
                for (int i = 0; i < mineField.width; i++) {
                    for (int j = 0; j < mineField.height; j++) {
                        mineField.gameBoard[i][j].contents.setTexture(textures["revealed"]);
                        mineField.gameBoard[i][j].contents.setPosition(i*32,j*32);
                    }
                }
            }


            /*** TEST 1 ***/
            if(mineField.mode == GameBoard::Mode::Test1) {
                mineField.Test1();

                for (int i = 0; i < mineField.width; i++) {
                    for (int j = 0; j < mineField.height; j++) {
                        mineField.gameBoard[i][j].contents.setTexture(textures["revealed"]);
                        mineField.gameBoard[i][j].contents.setPosition(i*32,j*32);
                    }

                   mineField.mode = GameBoard::Mode::Play;

                }
            }

            /*** TEST 2 ***/
            if(mineField.mode == GameBoard::Mode::Test2) {
                mineField.Test2();
                for (int i = 0; i < mineField.width; i++) {
                    for (int j = 0; j < mineField.height; j++) {
                        mineField.gameBoard[i][j].contents.setTexture(textures["revealed"]);
                        mineField.gameBoard[i][j].contents.setPosition(i*32,j*32);
                    }
                   mineField.mode = GameBoard::Mode::Play;
                }
            }

            /*** LOSE: REVEAL MINES ***/
            if(mineField.mode == GameBoard::Mode::Lose) {
                for (int i = 0; i < mineField.width; i++) {
                    for (int j = 0; j < mineField.height; j++) {
                        if(mineField.gameBoard[i][j].bomb) {
                            mineField.gameBoard[i][j].state = Tile::State::Revealed;
                        }
                    }
                }
            }

            /*** WIN: PLACE FLAGS ***/
            if(mineField.mode == GameBoard::Mode::Win){
                for(int i = 0; i < mineField.width; i++){
                    for(int j = 0; j < mineField.height; j++){
                        if(mineField.gameBoard[i][j].bomb){
                            mineField.gameBoard[i][j].state = Tile::State ::Flagged;
                            mineField.gameBoard[i][j].flag.setPosition(i*32,j*32);
                        }
                    }
                }
            }


            if (mineField.Win()) { // Checks to see if the game is won
                mineField.mode = GameBoard::Mode::Win;
            }


                for (int i = 0; i < 25; i++) {
                    for (int j = 0; j < 16; j++) {

                        /*** TESTING ENVIORMENT ***/
                         /*mineField.gameBoard[i][j].sprite.setTexture(textures["hidden"]);
                         window.draw(mineField.gameBoard[i][j].sprite);*/
                        /*** TESTING ENVIORMENT ***/


                        /*** PRINTS NUMBERS ***/
                        if (mineField.gameBoard[i][j].adjBomb == 1) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_1"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 2) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_2"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 3) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_3"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 4) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_4"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 5) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_5"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                           window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 6) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_6"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 7) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_7"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }
                        if (mineField.gameBoard[i][j].adjBomb == 8) {
                            mineField.gameBoard[i][j].contents.setTexture(textures["number_8"]);
                            mineField.gameBoard[i][j].contents.setPosition(i * 32, j * 32);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }


                        /*** DEBUG ***/
                        if (mineField.mode == GameBoard::Mode::Debug) { //DEBUG
                            mineField.gameBoard[i][j].sprite.setTexture(textures["hidden"]); //POPULATES GAMEBOARD WITH MINES ON THE OUTSIDE
                            window.draw(mineField.gameBoard[i][j].sprite);
                        }

                        /*** BOMBS ***/
                        if (mineField.gameBoard[i][j].bomb) { // Prints Bomb
                            mineField.gameBoard[i][j].contents.setTexture(textures["mine"]);
                            window.draw(mineField.gameBoard[i][j].contents);
                        }

                        /*** PLAY ***/
                        if (mineField.mode != GameBoard::Mode::Debug) { //Any OTHER MODE OTHER THAN DEBUG
                            mineField.gameBoard[i][j].sprite.setTexture(textures["hidden"]);
                            window.draw(mineField.gameBoard[i][j].sprite);

                        }

                        /*** REVEALES ***/
                        if (mineField.gameBoard[i][j].state == Tile::State::Revealed) {

                            mineField.gameBoard[i][j].sprite.setTexture(textures["revealed"]);
                            window.draw(mineField.gameBoard[i][j].sprite);


                            if (mineField.gameBoard[i][j].bomb) { // DRAWS BOMB IF BOMB
                                window.draw(mineField.gameBoard[i][j].contents);
                                mineField.mode = GameBoard::Mode::Lose;
                            }

                            if (!mineField.gameBoard[i][j].bomb) { // DRAWS CONTENTS IF NOT BOMB
                                window.draw(mineField.gameBoard[i][j].contents);
                            }

                        }

                        /*** FLAG ***/
                        if (mineField.gameBoard[i][j].state == Tile::State::Flagged) { // DRAWS FLAG IF FLAG
                            mineField.gameBoard[i][j].flag.setTexture(textures["flag"]);
                            window.draw(mineField.gameBoard[i][j].flag);
                        }

                    }
                }

                if (mineField.mode != GameBoard::Mode::Lose && mineField.mode != GameBoard::Mode::Win) {
                    sf::Sprite restart;
                    restart.setTexture(textures["face_happy"]);
                    restart.setPosition(368, 512);
                    window.draw(restart);
                } else if (mineField.mode == GameBoard::Mode::Lose) {
                    sf::Sprite restart;
                    restart.setTexture(textures["face_lose"]);
                    restart.setPosition(368, 512);
                    window.draw(restart);
                } else if (mineField.mode == GameBoard::Mode::Win) {
                    sf::Sprite restart;
                    restart.setTexture(textures["face_win"]);
                    restart.setPosition(368, 512);
                    window.draw(restart);
                }

                sf::Sprite deBug;
                deBug.setTexture(textures["debug"]);
                deBug.setPosition(496, 512);
                window.draw(deBug);

                sf::Sprite test1;
                test1.setTexture(textures["test_1"]);
                test1.setPosition(560, 512);
                window.draw(test1);

                sf::Sprite test2;
                test2.setTexture(textures["test_2"]);
                test2.setPosition(624, 512);
                window.draw(test2);

                sf::Sprite hundreds;
                sf::Sprite tens;
                sf::Sprite ones;

                mineField.DrawNum(window, textures);

                window.display();
        }

    }
    return 0;
}


sf::Texture LoadTextures(std::string s) {
    sf::Texture t;
    if(t.loadFromFile(s)) {
    }
    else{
        std::cout << "ERROR LOADING FILE" << std::endl;
    }
    return t;
}

std::map<std::string, sf::Texture> Textures() {
    std::map<std::string, sf::Texture> textures;

    textures["debug"] = LoadTextures("images/debug.png");
    textures["digits"] = LoadTextures("images/digits.png");
    textures["face_happy"] = LoadTextures("images/face_happy.png");
    textures["face_lose"] = LoadTextures("images/face_lose.png");
    textures["face_win"] = LoadTextures("images/face_win.png");
    textures["flag"] = LoadTextures("images/flag.png");
    textures["mine"] = LoadTextures("images/mine.png");
    textures["number_1"] = LoadTextures("images/number_1.png");
    textures["number_2"] = LoadTextures("images/number_2.png");
    textures["number_3"] = LoadTextures("images/number_3.png");
    textures["number_4"] = LoadTextures("images/number_4.png");
    textures["number_5"] = LoadTextures("images/number_5.png");
    textures["number_6"] = LoadTextures("images/number_6.png");
    textures["number_7"] = LoadTextures("images/number_7.png");
    textures["number_8"] = LoadTextures("images/number_8.png");
    textures["test_1"] = LoadTextures("images/test_1.png");
    textures["test_2"] = LoadTextures("images/test_2.png");
    textures["hidden"] = LoadTextures("images/tile_hidden.png");
    textures["revealed"] = LoadTextures("images/tile_revealed.png");

    return textures;
}


