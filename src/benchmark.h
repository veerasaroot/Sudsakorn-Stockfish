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

#ifndef BENCHMARK_H_INCLUDED
#define BENCHMARK_H_INCLUDED

#include <iosfwd>
#include <string>
#include <vector>

namespace Brainlearn {

class Position;

std::vector<std::string> setup_bench(const Position&, std::istream&);

}  // namespace Brainlearn

#endif  // #ifndef BENCHMARK_H_INCLUDED
