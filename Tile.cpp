//
// Created by Andrew Rodrigues on 11/21/18.
//

#include "Tile.h"
#include "GameBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>
#include <vector>

Tile::Tile() {
    bomb = false;
    state = State :: Hidden;
    adjBomb = 0;
}

void Tile::Clear() {
    adjTiles.clear();
}

void Tile::TileReveal() {



    if (state != Tile::State::Revealed && state != Tile::State::Flagged && !bomb) {

        state = Tile::State::Revealed;


        for (auto &adjTile : adjTiles) {
            if (adjTile->adjBomb == 0) {
                adjTile->TileReveal();
            }
            if(adjTile -> adjBomb > 0 && adjTile->state != Tile::State::Flagged){
                adjTile->state = Tile::State ::Revealed;

            }
        }
    }
}




