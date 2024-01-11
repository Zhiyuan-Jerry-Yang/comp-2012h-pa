#include "Gem.h"


//write your codes here
Gem::Gem(int x, int y, GemType gem_type): Item(x, y) {gtype = gem_type;}

Gem::~Gem() {;}

void Gem::triggered_by(Player &p) {
    if (MapUnit::is_valid()) {
        if (gtype == RUBY && p.get_role() == WARRIOR) p.charge_mp();
        else if (gtype == EMERALD && p.get_role() == ARCHER) p.charge_mp();
        else if (gtype == SAPPHIRE && p.get_role() == MAGE) p.charge_mp();
        MapUnit::invalidate();
    }
}

string Gem::get_item_str() const {
    switch (gtype) {
        case RUBY:
            return SYM_RUBY;
            break;
        case EMERALD:
            return SYM_EMERALD;
            break;
        case SAPPHIRE:
            return SYM_SAPPHIRE;
            break;
    }
    return "-1";
}