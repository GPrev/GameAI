#ifndef __MONTE_CARLO_HPP__
#define __MONTE_CARLO_HPP__

#include "game.hpp"
#include <random>
#include <chrono>
#include <vector>

namespace monte_carlo
{
  class monte_carlo
  {
    uint32_t batch_size;
    std::chrono::milliseconds milliseconds;
    std::vector<std::mt19937> generators;

  public:
    monte_carlo(uint32_t batch_size, uint32_t milliseconds);
    uint16_t select_move(const game::game& game);
  };
}

#endif
