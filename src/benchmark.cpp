/*
  Sudsakorn, a UCI makruk playing engine derived from Brainlearn-Stockfish
  Copyright (C) 2004-2024 The Sudsakorn developers (see AUTHORS file)

  Sudsakorn is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Sudsakorn is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "benchmark.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "position.h"

namespace {

// clang-format off
const std::vector<std::string> Defaults = {
    "rnsmksnr/8/pppppppp/8/8/PPPPPPPP/8/RNSKMSNR w 0 1",
    "3s1k2/m4n2/1s1n1p2/p2p1Pp1/Pp1P2P1/1P1SMS1r/7N/3K2NR b 0 1",
    "r1sm1r2/3k1s1R/1pp2p2/P1nnPP2/7p/PS3N2/3NSM1P/2RK4 w 0 1",
    "3m4/4s2k/2R1p3/2S2pM1/p2NnP2/4P3/4K3/1r6 b 12 45",
    "3r3r/2snm1k1/5pp1/1Pp5/p1S1PP1p/P1S3PP/K4M2/3R3R b 1 25",
    "6r1/2mnks2/pps1pn1p/2pp1p2/1PNP1P2/P1PKPS1P/2S1N3/R3M3 w 0 16",
    "8/8/5k2/7p/8/6RR/3K4/8 w 0 1 moves h3h5" // draw by counting rules
};
// clang-format on

}  // namespace

namespace Brainlearn {

// Builds a list of UCI commands to be run by bench. There
// are five parameters: TT size in MB, number of search threads that
// should be used, the limit value spent for each position, a file name
// where to look for positions in FEN format, and the type of the limit:
// depth, perft, nodes and movetime (in milliseconds). Examples:
//
// bench                            : search default positions up to depth 13
// bench 64 1 15                    : search default positions up to depth 15 (TT = 64MB)
// bench 64 1 100000 default nodes  : search default positions for 100K nodes each
// bench 64 4 5000 current movetime : search current position with 4 threads for 5 sec
// bench 16 1 5 blah perft          : run a perft 5 on positions in file "blah"
std::vector<std::string> setup_bench(const Position& current, std::istream& is) {

    std::vector<std::string> fens, list;
    std::string              go, token;

    // Assign default values to missing arguments
    std::string ttSize    = (is >> token) ? token : "16";
    std::string threads   = (is >> token) ? token : "1";
    std::string limit     = (is >> token) ? token : "13";
    std::string fenFile   = (is >> token) ? token : "default";
    std::string limitType = (is >> token) ? token : "depth";

    go = limitType == "eval" ? "eval" : "go " + limitType + " " + limit;

    if (fenFile == "default")
        fens = Defaults;

    else if (fenFile == "current")
        fens.push_back(current.fen());

    else
    {
        std::string   fen;
        std::ifstream file(fenFile);

        if (!file.is_open())
        {
            std::cerr << "Unable to open file " << fenFile << std::endl;
            exit(EXIT_FAILURE);
        }

        while (getline(file, fen))
            if (!fen.empty())
                fens.push_back(fen);

        file.close();
    }

    list.emplace_back("setoption name Threads value " + threads);
    list.emplace_back("setoption name Hash value " + ttSize);
    list.emplace_back("ucinewgame");

    for (const std::string& fen : fens)
        if (fen.find("setoption") != std::string::npos)
            list.emplace_back(fen);
        else
        {
            list.emplace_back("position fen " + fen);
            list.emplace_back(go);
        }

    return list;
}

}  // namespace Brainlearn