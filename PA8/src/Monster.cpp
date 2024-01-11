#include "Monster.h"
#include <cmath>

// write your code here
Monster::Monster(int x, int y): MapUnit(x, y) {;}

Monster::~Monster() {;}

bool Monster::is_active() const {return active;}

void Monster::set_active() {if (is_valid()) active = true;}

void Monster::recover_hp(int hp) {
    cur_hp += hp;
    if (cur_hp > max_hp) cur_hp = max_hp;
}

UnitType Monster::get_unit_type() const {return MONSTER;}

bool Monster::is_blocked() const {
    if (is_valid()) return true;
    return false;
}

int Monster::attacked_by(int atk_) {
    if (!is_valid()) return 0;
    else {
        int damage = atk_ - def;
        if (damage < 0) return 0;
        else {
            cur_hp -= damage;
            if (cur_hp <= 0) {
                invalidate();
                active = false;
                return 1;
            }
            return 0;
        }
    }
}

string Monster::get_display_str() const {
    if (!is_valid()) return SYM_EMPTY;
    else {
        if (!is_discovered()) return SYM_DANGER;
        else return get_monster_str();
    }
}

void Monster::follow(const Player &p, MapUnit *map[][MAP_SIZE]) {
    int player_x{0}, player_y{0};
    p.get_position(player_x, player_y);
    int horizontal_dist = std::abs(x - player_x), vertical_dist = std::abs(y - player_y);
    if (vertical_dist + horizontal_dist == 1) return;
    if (horizontal_dist > 0) {
        if (x < player_x && !map[x + 1][y]->is_blocked()) {
            delete map[x + 1][y];
            map[x + 1][y] = this;
            map[x][y] = new EmptyLand(x, y);
            x++;
            return;
        }
        else if (x > player_x && !map[x - 1][y]->is_blocked()) {
            delete map[x - 1][y];
            map[x - 1][y] = this;
            map[x][y] = new EmptyLand(x, y);
            x--;
            return;
        }
    }
    if (vertical_dist > 0) {
        if (y < player_y && !map[x][y + 1]->is_blocked()) {
            delete map[x][y + 1];
            map[x][y + 1] = this;
            map[x][y] = new EmptyLand(x, y);
            y++;
            return;
        }
        else if (y > player_y && !map[x][y - 1]->is_blocked()) {
            delete map[x][y - 1];
            map[x][y - 1] = this;
            map[x][y] = new EmptyLand(x, y);
            y--;
            return;
        }
    }
    return;
    
}