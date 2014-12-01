#include "connect4.hpp"
#include <sstream>

using namespace std;

namespace game
{
  static vector<vector<uint64_t>> create_hash_values()
  {
    default_random_engine generator;
    uniform_int_distribution<uint64_t> distribution;
    vector<vector<uint64_t>> res(7, vector<uint64_t>(6, 0));
    for (int i = 0; i < 7; ++i) 
      {
	for (int j = 0; j < 6; ++j)
	  {
	    res[i][j] = distribution(generator);
	  }
      }
    return res;
  }

  vector<vector<uint64_t>> connect4::cross_hash_values = create_hash_values();
  vector<vector<uint64_t>> connect4::circle_hash_values = create_hash_values();

  connect4::connect4()
  {
  }

  void connect4::save_state()
  {
    saved_state = current_state;
  }

  void connect4::restore_state()
  {
    current_state = saved_state;
  }

  shared_ptr<game> connect4::copy() const
  {
    return shared_ptr<game>(new connect4(*this));
  }

  bool connect4::end_of_game() const
  {
    return current_state.first_player_win || current_state.second_player_win || current_state.total_moves == 42;
  }

  uint8_t connect4::current_player() const
  {
    return current_state.depth & 1 ? CIRCLE : CROSS; 
  }

  uint8_t connect4::current_player_representation() const
  {
    return current_state.depth & 1 ? CIRCLE_REPRESENTATION : CROSS_REPRESENTATION; 
  }

  uint8_t connect4::player_representation_to_player(uint8_t player) const
  {
    return player == CIRCLE_REPRESENTATION ? CIRCLE : (player == CROSS_REPRESENTATION ? CROSS : -1); 
  }

  int connect4::value(uint8_t player) const
  {
    if (player == CROSS)
      {
	return current_state.first_player_win ? 1 : (current_state.second_player_win ? -1 : 0);
      }
    else if (player == CIRCLE)
      {
	return current_state.second_player_win ? 1 : (current_state.first_player_win ? -1 : 0);
      }
    return 0;
  }

  uint16_t connect4::number_of_moves() const
  {
    return current_state.nb_moves;
  }

  uint8_t connect4::get(uint8_t i, uint8_t j) const
  {
    return (current_state.board[i] >> (j << 1)) & 3;
  }

  bool connect4::vertical(uint8_t position, uint8_t free, uint8_t player) const
  {
    return free >= 3 && get(position, free - 1) == player && get(position, free - 2) == player && get(position, free - 3) == player;
  }

  bool connect4::horizontal(uint8_t position, uint8_t free, uint8_t player) const
  {
    uint8_t sum = 0;
    if (position >= 1 && get(position - 1, free) == player)
      {
	++sum;
	if (position >= 2 && get(position - 2, free) == player)
	  {
	    ++sum;
	    if (position >= 3 && get(position - 3, free) == player) ++sum;
	  }
      }
    if (position <= 5 && get(position + 1, free) == player)
      {
	++sum;
	if (position <= 4 && get(position + 2, free) == player)
	  {
	    ++sum;
	    if (position <= 3 && get(position + 3, free) == player) ++sum;
	  }
      }
    return sum >= 3;
  }

  bool connect4::diagonal(uint8_t position, uint8_t free, uint8_t player) const
  {
    uint8_t sum = 0;
    if (position >= 1 && free <= 4 && get(position - 1, free + 1) == player)
      {
	++sum;
	if (position >= 2 && free <= 3 && get(position - 2, free + 2) == player)
	  {
	    ++sum;
	    if (position >= 3 && free <= 2 && get(position - 3, free + 3) == player) ++sum;
	  }
      }
    if (position <= 5 && free >= 1 && get(position + 1, free - 1) == player)
      {
	++sum;
	if (position <= 4 && free >= 2 && get(position + 2, free - 2) == player)
	  {
	    ++sum;
	    if (position <= 3 && free >= 3 && get(position + 3, free - 3) == player) ++sum;
	  }
      }
    return sum >= 3;
  }

  bool connect4::other_diagonal(uint8_t position, uint8_t free, uint8_t player) const
  {
    uint8_t sum = 0;
    if (position >= 1 && free >= 1 && get(position - 1, free - 1) == player)
      {
	++sum;
	if (position >= 2 && free >= 2 && get(position - 2, free - 2) == player)
	  {
	    ++sum;
	    if (position >= 3 && free >= 3 && get(position - 3, free - 3) == player) ++sum;
	  }
      }
    if (position <= 5 && free <= 4 && get(position + 1, free + 1) == player)
      {
	++sum;
	if (position <= 4 && free <= 3 && get(position + 2, free + 2) == player)
	  {
	    ++sum;
	    if (position <= 3 && free <= 2 && get(position + 3, free + 3) == player) ++sum;
	  }
      }
    return sum >= 3;
  }

  void connect4::update_win(uint8_t position, uint8_t free)
  {
    ++current_state.total_moves;
    uint8_t player = current_player_representation();
    bool win = 
      vertical(position, free, player)
      ||
      horizontal(position, free, player)
      ||
      diagonal(position, free, player)
      ||
      other_diagonal(position, free, player);
    if (win) 
      {
	if (player == CROSS_REPRESENTATION) current_state.first_player_win = true;
	else current_state.second_player_win = true;
      }
  }

  void connect4::update_moves(uint16_t move)
  {
    --current_state.nb_moves;
    uint32_t prefix = current_state.moves >> ((move + 1) * 3);
    uint8_t shift = 32 - move * 3;
    current_state.moves = (uint32_t)((uint64_t)current_state.moves << shift) >> shift;
    current_state.moves |= prefix << (move * 3);
  }

  void connect4::play(uint16_t m)
  {    
    uint8_t position = ((current_state.moves >> (m * 3)) & 7);
    uint8_t p = position * 3;
    uint8_t f = (current_state.free >> p) & 7;
    current_state.hash_value ^= current_player() == CIRCLE ? circle_hash_values[position][f] : cross_hash_values[position][f];
    current_state.board[position] |= current_player_representation() << (f << 1);
    update_win(position, f);
    ++f;
    current_state.free = (current_state.free & ~(((uint32_t)7) << p)) | (f << p);
    if (f == 6)
      {
	update_moves(m);
      }
    ++current_state.depth;
  }

  string connect4::player_to_string(uint8_t player) const
  {
    return player == CROSS ? "X" : (player == CIRCLE ? "O" : " ");
  }

  string connect4::move_to_string(uint16_t m) const
  {
    uint8_t position = ((current_state.moves >> (m * 3)) & 7);
    return std::to_string(position);
  }

  string connect4::to_string() const
  {
    stringbuf buffer;
    ostream os(&buffer);
    for (int y = 5; y >= 0; --y) 
      {
	for (int k = 0; k < 7; ++k) os << "+-";
	os << "+" << endl;
	for (int x = 0; x < 7; ++x)
	  {
	    os << "|" << player_to_string(player_representation_to_player(get(x, y)));
	  }
	os << "|" << endl;
      }
    for (int k = 0; k < 7; ++k) os << "+-";
    os << "+" << endl;
    for (int k = 0; k < 7; ++k) os << " " << k;
    os << endl;
    return buffer.str();
  }

  void connect4::playout(mt19937& engine, int max_depth)
  {
    while (!end_of_game())
      {
	uniform_int_distribution<uint16_t> distribution(0, number_of_moves() - 1);
	uint16_t move = distribution(engine);
	play(move);
      }
  }

  std::uint64_t connect4::hash() const
  {
    return current_state.hash_value;
  }

  ostream& operator<<(ostream& os, const connect4& c4)
  {
    os << c4.to_string() << endl;
    return os;
  }
}
