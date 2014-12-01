#ifndef __TEST_MONTE_CARLO_HPP__
#define __TEST_MONTE_CARLO_HPP__

#include "connect4.hpp"

namespace monte_carlo
{
  class test_monte_carlo
  {
    void play();
    void select_move(game::connect4& c4);
  public:
    test_monte_carlo();
  };
}
#endif
