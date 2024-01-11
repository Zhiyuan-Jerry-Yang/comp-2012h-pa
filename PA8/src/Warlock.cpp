#include "Warlock.h"

Warlock::Warlock(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 15;
    atk = 5, def = 1;
}

//write your code here

Warlock::~Warlock() {;}

string Warlock::get_monster_str() const {
    string w_hp = to_string(cur_hp);
    if (cur_hp < 10) w_hp = "0" + w_hp;
    return ("W" + w_hp);
}

void Warlock::action(Player &p, MapUnit *map[][MAP_SIZE]) {
    int player_x{0}, player_y{0};
    p.get_position(player_x, player_y);
    int dist = std::abs(x - player_x) + std::abs(y - player_y);
    if (dist <= 1) {
        p.attacked_by(atk);
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) continue;
                if (!map[x + i][y + j]->is_blocked() && (player_x != x + i || player_y != y + j)) {
                    map[x + i][y + j] = new Zombie(x + i, y + j);
                }
            }
        }
    }
}