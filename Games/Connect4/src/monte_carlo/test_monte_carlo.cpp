#include "monte_carlo.hpp"
#include "test_monte_carlo.hpp"
#include <iostream>
#include <map>

using namespace std;
using namespace game;

namespace monte_carlo
{
  test_monte_carlo::test_monte_carlo()
  {    
    play();
  }

  void test_monte_carlo::select_move(connect4& c4)
  {
    cout << c4.player_to_string(c4.current_player()) << " move: ";
    map<string, int> m;
    for (int i = 0; i < c4.number_of_moves(); ++i) 
      {
	m[c4.move_to_string(i)] = i;
      }
    string move;
    cin >> move;
    c4.play(m[move]);
  }

  void test_monte_carlo::play()
  {
    monte_carlo mc(80000, 2000);
    connect4 c4;
    cout << "play one game" << endl;
    cout << "who's first? (h)uman/(c)omputer ";
    string ans;
    cin >> ans;
    cout << c4 << endl;
    while (!c4.end_of_game()) 
      {       
	if ((ans == "h" && c4.current_player() == 0) || (ans == "c" && c4.current_player() == 1))
	  {
	    select_move(c4);
	  }
	else
	  {
	    uint16_t move = mc.select_move(c4);
	    cout << c4.player_to_string(c4.current_player()) << " move: " << c4.move_to_string(move) << endl;
	    c4.play(move);
	  }
	cout << c4 << endl;
      }
    if (c4.value(0) == 1) cout << c4.player_to_string(0) << " won";
    else if (c4.value(1) == 1) cout << c4.player_to_string(1) << " won";
    else cout << "draw";
    cout << endl;
  }
}
