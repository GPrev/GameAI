#include "connect4.hpp"
#include "test_connect4.hpp"
#include <iostream>
#include <map>

using namespace std;

namespace game
{
  test_connect4::test_connect4()
  {    
    playout();
    play();
  }

  void test_connect4::playout()
  {
    mt19937 mt;
    connect4 c4;
    cout << "playout" << endl;
    for (int i = 0; i < 100; ++i) 
      {
	uint8_t player = c4.current_player();
	c4.save_state();
	c4.playout(mt);
	cout << "value: " << c4.value(player) << endl << c4 << endl;
	c4.restore_state();
	string wait;
	getline(cin, wait);
      }
  }

  void test_connect4::play()
  {
    connect4 c4;
    int player = 0;
    cout << "play one game" << endl;
    while (!c4.end_of_game()) 
      {
	cout << c4 << endl;
	cout << c4.player_to_string(player) << " move: ";
	map<string, int> m;
	for (int i = 0; i < c4.number_of_moves(); ++i) 
	  {
	    m[c4.move_to_string(i)] = i;
	  }
	string move;
	cin >> move;
	c4.play(m[move]);
	player = 1 - player;
      }
    cout << c4 << endl;
    if (c4.value(0) == 1) cout << c4.player_to_string(0) << " won";
    else if (c4.value(1) == 1) cout << c4.player_to_string(1) << " won";
    else cout << "draw";
    cout << endl;
  }
}
