``cpp
#pragma once
#include <vector>
#include <string>
#include "board.hpp"
class NNUE {
public:
    NNUE();
    bool load(const std::string& file_path);
    float evaluate(const Board& board);
private:
    // ... implementation details (similar to Stockfish NNUE)
};
