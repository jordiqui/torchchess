```cpp
#pragma once
#include "nnue.hpp"
#include "transformer.hpp"
class HybridEvaluator {
public:
    HybridEvaluator(const std::string& nnue_path, const std::string& transformer_path);
    float evaluate(const Board& board);
private:
    NNUE nnue_;
    TransformerEvaluator transformer_;
    bool needs_deep_eval(const Board& board, float nnue_score);
};
