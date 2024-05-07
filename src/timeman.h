/*
  Brainlearn, a UCI chess playing engine derived from Stockfish
  Copyright (C) 2004-2024 Andrea Manzo, K.Kiniama and Brainlearn developers (see AUTHORS file)

  Brainlearn is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Brainlearn is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TIMEMAN_H_INCLUDED
#define TIMEMAN_H_INCLUDED

#include <cstddef>
#include <cstdint>

#include "misc.h"
#include "types.h"

namespace Brainlearn {
class OptionsMap;

namespace Search {
struct LimitsType;
}

// The TimeManagement class computes the optimal time to think depending on
// the maximum available time, the game move number, and other parameters.
class TimeManagement {
   public:
    void init(Search::LimitsType& limits, Color us, int ply, const OptionsMap& options);

    TimePoint optimum() const;
    TimePoint maximum() const;
    TimePoint elapsed(std::size_t nodes) const;

    void clear();
    void advance_nodes_time(std::int64_t nodes);

   private:
    TimePoint startTime;
    TimePoint optimumTime;
    TimePoint maximumTime;

    std::int64_t availableNodes = 0;      // When in 'nodes as time' mode
    bool         useNodesTime   = false;  // True if we are in 'nodes as time' mode
};

}  // namespace Brainlearn

#endif  // #ifndef TIMEMAN_H_INCLUDED
