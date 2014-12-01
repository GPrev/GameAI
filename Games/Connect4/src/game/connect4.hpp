#ifndef __CONNECT4_HPP__
#define __CONNECT4_HPP__

#include "game.hpp"
#include <random>
#include <array>
#include <vector>
#include <iostream>
#include <memory>

namespace game
{
  class connect4 : public game
  {
  public:
    connect4();
    connect4(const connect4& c4) = default;
    connect4& operator=(const connect4& c4) = default;
    bool end_of_game() const;
    int value(std::uint8_t player) const;
    uint8_t current_player() const;
    std::uint16_t number_of_moves() const;
    void play(std::uint16_t m);
    std::string player_to_string(std::uint8_t player) const;
    std::string move_to_string(std::uint16_t m) const;
    std::string to_string() const;
    void playout(std::mt19937& engine, int max_depth = -1);
    void save_state();
    void restore_state();
    std::shared_ptr<game> copy() const;
    std::uint64_t hash() const;

  private:
    inline void update_win(uint8_t position, uint8_t free);
    inline void update_moves(uint16_t move);
    inline uint8_t get(uint8_t i, uint8_t j) const;
    inline bool vertical(uint8_t position, uint8_t free, uint8_t player) const;
    inline bool horizontal(uint8_t position, uint8_t free, uint8_t player) const;
    inline bool diagonal(uint8_t position, uint8_t free, uint8_t player) const;
    inline bool other_diagonal(uint8_t position, uint8_t free, uint8_t player) const;
    inline uint8_t current_player_representation() const;
    inline uint8_t player_representation_to_player(uint8_t player) const;

    const uint8_t CROSS = 0;
    const uint8_t CIRCLE = 1;
    const uint8_t CROSS_REPRESENTATION = 1;
    const uint8_t CIRCLE_REPRESENTATION = 2;

    struct state
    {
      bool first_player_win = false;
      bool second_player_win = false;
      uint32_t depth = 0;
      uint8_t total_moves = 0;
      std::array<uint16_t, 7> board{};
      std::uint16_t nb_moves = 7;
      std::uint32_t moves = 0x1AC688;
      std::uint32_t free = 0;
      uint64_t hash_value = 0;
    };

    state current_state;
    state saved_state;

    static std::vector<std::vector<uint64_t>> cross_hash_values;
    static std::vector<std::vector<uint64_t>> circle_hash_values;
  };
  std::ostream& operator<<(std::ostream& os, const connect4& c4);
}

#endif
