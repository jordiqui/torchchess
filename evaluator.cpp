#include "evaluator.h"
#include <torch/script.h>

const float TRANSFORMER_THRESHOLD = 0.25;

HybridEvaluator::HybridEvaluator(const string& nnue_path, 
                                 const string& transformer_path) {
    // Cargar red NNUE (formato Stockfish)
    nnue.load(nnue_path);
    
    // Cargar modelo Transformer con LibTorch
    try {
        transformer = torch::jit::load(transformer_path);
    } catch (const c10::Error& e) {
        cerr << "Error loading transformer model: " << e.what() << endl;
        exit(1);
    }
}

float HybridEvaluator::evaluate(const Board& board) {
    // Evaluación rápida con NNUE
    float nnue_score = nnue.evaluate(board);
    
    // Determinar si se necesita evaluación profunda
    if (abs(nnue_score) < TRANSFORMER_THRESHOLD || 
        board.get_material_imbalance() > 2.0) {
        
        // Convertir posición a tensor
        auto input = board_to_tensor(board);
        
        // Inferencia con Transformer
        auto output = transformer.forward({input}).toTensor();
        float transformer_score = output.item<float>();
        
        // Combinación adaptativa
        float weight = 0.3 + 0.5 * (1.0 - exp(-board.get_phase()));
        return (1.0 - weight) * nnue_score + weight * transformer_score;
    }
    return nnue_score;
}
