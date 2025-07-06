```cpp
#include "wrapper.hpp"
HybridEvaluator::HybridEvaluator(const std::string& nnue_path, const std::string& transformer_path) {
    if (!nnue_.load(nnue_path)) {
        throw std::runtime_error("Failed to load NNUE");
    }
    if (!transformer_.load(transformer_path)) {
        throw std::runtime_error("Failed to load Transformer");
    }
}
float HybridEvaluator::evaluate(const Board& board) {
    float nnue_score = nnue_.evaluate(board);
    if (needs_deep_eval(board, nnue_score)) {
        float transformer_score = transformer_.evaluate(board);
        // Combine the scores: 70% NNUE, 30% Transformer
        return 0.7 * nnue_score + 0.3 * transformer_score;
    }
    return nnue_score;
}
bool HybridEvaluator::needs_deep_eval(const Board& board, float nnue_score) {
    // Conditions for deep evaluation: 
    //   - High material imbalance
    //   - Endgame phase
    //   - When the position is complex (high move count, king safety issues, etc.)
    // For now, we do deep evaluation 20% of the time randomly (for testing)
    // In practice, we would use a more sophisticated condition.
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(rng) < 0.2; // 20% chance
}
