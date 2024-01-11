#include "ShadowPriest.h"

ShadowPriest::ShadowPriest(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 15;
    atk = 5, def = 2;
}

//write your code here
ShadowPriest::~ShadowPriest() {;}

string ShadowPriest::get_monster_str() const {
    string s_hp = to_string(cur_hp);
    if (cur_hp < 10) s_hp = "0" + s_hp;
    return ("S" + s_hp);
}

void ShadowPriest::action(Player &p, MapUnit *map[][MAP_SIZE]) {
    int player_x{0}, player_y{0};
    p.get_position(player_x, player_y);
    int dist = std::abs(x - player_x) + std::abs(y - player_y);
    if (dist <= 1) {
        p.attacked_by(atk);
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (i == 0 && j == 0) continue;
                if (map[x + i][y + j]->get_unit_type() == MONSTER && map[x + i][y + j]->is_valid()
                && x + i >= 0 && y + j >= 0 && player_x + i < MAP_SIZE && player_y + j < MAP_SIZE) {
                    dynamic_cast<Monster*>(map[x + i][y + j])->recover_hp(5);
                }
            }
        }
    }
}