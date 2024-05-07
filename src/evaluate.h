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

#ifndef EVALUATE_H_INCLUDED
#define EVALUATE_H_INCLUDED

#include <string>
#include <unordered_map>

#include "types.h"

namespace Brainlearn {

class Position;
class OptionsMap;

namespace Eval {

std::string trace(Position& pos);

int   simple_eval(const Position& pos, Color c);
Value evaluate(const Position& pos, int optimism);

// The default net name MUST follow the format nn-[SHA256 first 12 digits].nnue
// for the build process (profile-build and fishtest) to work. Do not change the
// name of the macro, as it is used in the Makefile.
#define EvalFileDefaultNameBig "nn-b1a57edbea57.nnue"
#define EvalFileDefaultNameSmall "nn-baff1ede1f90.nnue"

struct EvalFile {
    // UCI option name
    std::string optionName;
    // Default net name, will use one of the macros above
    std::string defaultName;
    // Selected net name, either via uci option or default
    std::string current;
    // Net description extracted from the net file
    std::string netDescription;
};

namespace NNUE {

enum NetSize : int;

using EvalFiles = std::unordered_map<Eval::NNUE::NetSize, EvalFile>;

EvalFiles load_networks(const std::string&, const OptionsMap&, EvalFiles);
void      verify(const OptionsMap&, const EvalFiles&);

}  // namespace NNUE

}  // namespace Eval

}  // namespace Brainlearn

#endif  // #ifndef EVALUATE_H_INCLUDED
