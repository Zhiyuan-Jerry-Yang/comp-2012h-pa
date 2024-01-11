#include "Zombie.h"

Zombie::Zombie(int x, int y) : Monster(x, y)
{
    cur_hp = max_hp = 20;
    atk = 9, def = 3;
}

//write your code here
Zombie::~Zombie() {;}

string Zombie::get_monster_str() const {
    string z_hp = to_string(cur_hp);
    if (cur_hp < 10) z_hp = "0" + z_hp;
    return ("Z" + z_hp);
}

void Zombie::action(Player &p, MapUnit *map[][MAP_SIZE]) {
    int player_x{0}, player_y{0};
    p.get_position(player_x, player_y);
    int dist = std::abs(x - player_x) + std::abs(y - player_y);
    if (dist <= 1) p.attacked_by(atk);
}