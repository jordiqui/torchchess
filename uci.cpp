```cpp
#include "uci.hpp"
#include "../board/board.hpp"
#include "../search/alpha_beta.hpp"
#include "../nn/wrapper.hpp"
UCI::UCI() : board_(), search_() {
    evaluator_ = std::make_unique<HybridEvaluator>("../networks/nnue.bin", "../networks/transformer.pt");
}
void UCI::loop() {
    std::string line;
    while (std::getline(std::cin, line)) {
        // Parse UCI commands: position, go, quit, etc.
        if (line == "uci") {
            std::cout << "id name TorchChess" << std::endl;
            std::cout << "id author Jordi" << std::endl;
            // ... other options
            std::cout << "uciok" << std::endl;
        } else if (line.substr(0, 8) == "position") {
            // ... set up position
        } else if (line.substr(0, 2) == "go") {
            // Start search
            SearchResult result = search_.start(board_, *evaluator_);
            std::cout << "bestmove " << result.best_move << std::endl;
        } // ... other commands
    }
}
