```cpp
#pragma once
#include <torch/script.h>
#include "board.hpp"
class TransformerEvaluator {
public:
    TransformerEvaluator();
    bool load(const std::string& model_path);
    float evaluate(const Board& board);
private:
    torch::jit::Module model_;
};
