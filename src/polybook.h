/*
  SF-PG-011125, a Stockfish-based UCI chess engine with Polyglot (.bin) book support and ChatGPT-inspired ideas
  Authors: Jorge Ruiz, Codex ChatGPT, and the Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <cstdint>

#include "bitboard.h"
#include "position.h"
#include "ucioption.h"

namespace Stockfish {

struct PolyHash {
    std::uint64_t key;
    std::uint16_t move;
    std::uint16_t weight;
    std::uint32_t learn;
};

class PolyBook {
   public:
    PolyBook();
    ~PolyBook();

    static void     init(const OptionsMap&);
    void            init(const std::string& bookfile);
    Stockfish::Move probe(Stockfish::Position& pos, bool bestBookMove, int width = 10);

   private:
    Stockfish::Key  polyglot_key(const Stockfish::Position& pos);
    Stockfish::Move pg_move_to_sf_move(const Stockfish::Position& pos, unsigned short pg_move);

    int find_first_key(std::uint64_t key);
    int get_key_data();

    bool check_draw(Stockfish::Position& pos, Stockfish::Move m);

    int       keycount;
    PolyHash* polyhash;
    bool      enabled;

    int index_first;
    int index_best;
    int index_rand;
    int index_count;
    int index_weight_count;
};

extern PolyBook polybook[6];

}  // namespace Stockfish

