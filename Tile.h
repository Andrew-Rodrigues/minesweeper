//
// Created by Andrew Rodrigues on 11/21/18.
//

#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <unordered_map>

struct Tile {

    enum class State{
        Hidden, Flagged, Revealed
    };

    Tile();

    void Clear();
    void TileReveal();


    int x;
    int y;
    State state;
    int adjBomb;
    bool bomb = false;
    sf:: Sprite sprite; // Hidden or Revealed Tile
    sf:: Sprite flag; // Flag ONLY
    sf:: Sprite contents; // Bomb or Numbers
    std::vector<Tile*> adjTiles;
};


#endif //MINESWEEPER_TILE_H