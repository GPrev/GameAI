#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <string>
#include <cstdint>
#include <random>
#include <memory>

namespace game
{
  struct game 
  {
    virtual bool end_of_game() const = 0;
    virtual int value(std::uint8_t player) const = 0;
    virtual uint8_t current_player() const = 0;
    virtual std::uint16_t number_of_moves() const = 0;
    virtual void play(std::uint16_t m) = 0;
    virtual std::string player_to_string(std::uint8_t player) const = 0;
    virtual std::string move_to_string(std::uint16_t m) const = 0;
    virtual std::string to_string() const = 0;
    virtual void playout(std::mt19937& engine, int max_depth = -1) = 0;
    virtual void save_state() = 0;
    virtual void restore_state() = 0;
    virtual std::shared_ptr<game> copy() const = 0;
    virtual std::uint64_t hash() const = 0;
    virtual ~game() {}
  };
}

#endif
