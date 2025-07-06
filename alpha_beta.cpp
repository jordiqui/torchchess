SearchResult AlphaBeta::search(Board& board, int depth) {
    // Inicialización de variables de búsqueda
    vector<Move> pv;
    int alpha = -INFINITE_SCORE;
    int beta = INFINITE_SCORE;
    
    // Búsqueda principal con iteración profunda
    for (int current_depth = 1; current_depth <= depth; current_depth++) {
        int score = alphabeta(board, current_depth, alpha, beta, pv);
        
        // Ajuste de ventana aspirativa
        if (score <= alpha || score >= beta) {
            alpha = -INFINITE_SCORE;
            beta = INFINITE_SCORE;
            current_depth--;  // Repetir búsqueda con ventana completa
        } else {
            alpha = score - ASPIRATION_WINDOW;
            beta = score + ASPIRATION_WINDOW;
        }
        
        // Actualizar mejor variante
        if (!pv.empty()) {
            best_pv = pv;
        }
    }
    
    return {best_pv.empty() ? Move() : best_pv[0], best_pv};
}

int AlphaBeta::alphabeta(Board& board, int depth, int alpha, int beta, vector<Move>& pv) {
    // Caso terminal: profundidad máxima alcanzada
    if (depth <= 0) {
        return quiescence_search(board, alpha, beta);
    }
    
    // Verificar tabla de transposición
    TTEntry* entry = transposition_table.get(board.get_hash());
    if (entry && entry->depth >= depth) {
        // ... (usar entrada de transposición si es válida)
    }
    
    // Generar movimientos y ordenar
    vector<Move> moves = move_generator.generate(board);
    move_ordering.order(moves, board, entry);
    
    // Búsqueda en el árbol
    Move best_move;
    for (Move move : moves) {
        board.make_move(move);
        int score = -alphabeta(board, depth - 1, -beta, -alpha, pv);
        board.unmake_move(move);
        
        if (score >= beta) {
            // Corte beta
            transposition_table.store(board.get_hash(), depth, beta, move, UPPER_BOUND);
            return beta;
        }
        
        if (score > alpha) {
            alpha = score;
            best_move = move;
            // Actualizar PV
            pv.clear();
            pv.push_back(move);
            // ... (combinar con PV de búsqueda recursiva)
        }
    }
    
    // Almacenar en tabla de transposición
    transposition_table.store(board.get_hash(), depth, alpha, best_move, EXACT);
    return alpha;
}
