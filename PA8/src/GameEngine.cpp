#include "GameEngine.h"

using namespace std;

// Please do not change the following already implemented code

void GameEngine::print_active_monsters()
{
    int i = 0;
    cout << "Active Monsters:" << endl;
    MonsterNode *cur = head;
    while (cur != nullptr)
    {
        cout << cur->data->get_display_str();
        cout << "@(" << cur->data->get_x();
        cout << "," << cur->data->get_y() << "), ";
        cur = cur->next;
        i++;
        if (i == 4)
        {
            i = 0;
            cout << endl;
        }
    }
}

bool GameEngine::player_win() const
{
    int px, py;
    player->get_position(px, py);
    if (px == MAP_SIZE - 1 && py == MAP_SIZE - 1)
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if (map[i][j]->get_unit_type() == UnitType::MONSTER && map[i][j]->is_valid())
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
        return false;
}

GameEngine::GameEngine()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (i > 8 && i < 12 && j > 2 && j < 6)
                map[i][j] = new Wall(i, j);
            else if (i > 14 && i < 18 && j > 2 && j < 6)
                map[i][j] = new Grass(i, j);
            else if (i > 2 && i < 6 && j == 9)
                map[i][j] = new Gem(i, j, GemType::RUBY);
            else if (i > 2 && i < 6 && j == 10)
                map[i][j] = new Gem(i, j, GemType::EMERALD);
            else if (i > 2 && i < 6 && j == 11)
                map[i][j] = new Gem(i, j, GemType::SAPPHIRE);
            else if (i > 8 && i < 12 && j > 8 && j < 12)
                map[i][j] = new Book(i, j);
            else if (i > 14 && i < 18 && j > 8 && j < 12)
                map[i][j] = new Medicine(i, j);
            else if (i > 2 && i < 6 && j > 14 && j < 18)
                map[i][j] = new Zombie(i, j);
            else if (i > 8 && i < 12 && j > 14 && j < 18)
                map[i][j] = new Warlock(i, j);
            else if (i > 14 && i < 18 && j > 14 && j < 18)
                map[i][j] = new ShadowPriest(i, j);
            else
                map[i][j] = new EmptyLand(i, j);
        }
    }
}

char GameEngine::input()
{
    char c;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    return c;
}

void GameEngine::run()
{
    string name;
    cout << "Please enter your name:" << endl;
    cin >> name;
    cout << "Please choose your role:" << endl;
    cout << "1 Warrior" << endl;
    cout << "2 Archer" << endl;
    cout << "3 Mage" << endl;

    int x = 0, y = 0;
    char role = input();
    switch (role)
    {
    case '1':
        create_player(x, y, name, Role::WARRIOR);
        break;
    case '2':
        create_player(x, y, name, Role::ARCHER);
        break;
    case '3':
        create_player(x, y, name, Role::MAGE);
        break;
    default:
        exit(0);
        break;
    }
    ui.refresh(this->map, *player);

    while (true)
    {
        switch (input())
        {
        case 'w':
            this->player_move(Direction::UP);
            break;
        case 'a':
            this->player_move(Direction::LEFT);
            break;
        case 's':
            this->player_move(Direction::DOWN);
            break;
        case 'd':
            this->player_move(Direction::RIGHT);
            break;
        case 'h':
            this->player_attack();
            break;
        case 'j':
            this->player_skill();
            break;
        default:
            break;
        }
        if (player_win())
        {
            cout << endl;
            cout << "You win." << endl;
            break;
        }
        player_discover();
        activate_monsters();
        monster_follow();
        monster_act();
        ui.refresh(this->map, *player);
        print_active_monsters();
        if (!player->is_alive())
        {
            cout << endl;
            cout << "You lose." << endl;
            break;
        }
    }
}


// write your code here
GameEngine::~GameEngine() {
    delete player;

    //map unit deletion
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[j][i]->get_unit_type() == MONSTER) delete map[j][i];
        }
    }
    
    //linked list deletion
    if (head != nullptr) {
        MonsterNode* workingptr2 = head; MonsterNode* workingptr1 = head->next;
        if (workingptr1 == nullptr) delete workingptr2;
        else {
            while (workingptr1 != nullptr) {
                delete workingptr2;
                workingptr2 = workingptr1;
                workingptr1 = workingptr1->next;
            }
        }
        head = nullptr;
    }
}

void GameEngine::create_player(int x, int y, const string &name, Role role) {
    switch (role)
    {
    case ARCHER:
        player = new Archer(x, y, name);
        break;
    case MAGE:
        player = new Mage(x, y, name);
        break;
    case WARRIOR:
        player = new Warrior(x, y, name);
        break;
    }
}

void GameEngine::activate_monster(Monster *monster) {
    if (monster->is_valid() && !monster->is_active()) {
        monster->set_active();
        MonsterNode* nodeptr = new MonsterNode;
        nodeptr->data = monster;
        nodeptr->next = head;
        head = nodeptr;
    }
}

void GameEngine::activate_monsters() {
    int player_x{0}, player_y{0};
    player->get_position(player_x, player_y);
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i == 0 && j == 0) continue;
            if (player_x + i >= 0 && player_y + j >= 0 && player_x + i < MAP_SIZE && player_y + j < MAP_SIZE) {
                if (map[player_x + i][player_y + j]->get_unit_type() == MONSTER) {
                    activate_monster(dynamic_cast<Monster*> (map[player_x + i][player_y + j]));
                }
            }
        }
    }
}

void GameEngine::deactivate_monster(Monster const *const monster) {
    MonsterNode* workingptr1 = head; MonsterNode* workingptr2 = head;
    while (workingptr1 != nullptr) {
        if (workingptr2 == head && workingptr2->data == monster) {
            head = workingptr1->next;
            workingptr1 = workingptr1->next;
            delete workingptr2;
            workingptr2 = workingptr1;
            if (workingptr1 != nullptr) workingptr1 = workingptr1->next;
        }
        else if (workingptr1->data == monster) {
            workingptr2->next = workingptr1->next;
            delete workingptr1;
            workingptr1 = workingptr2->next;
        }
        else {
            workingptr2 = workingptr1;
            workingptr1 = workingptr1->next;
        }
    }
}

void GameEngine::player_move(Direction d) {
    int player_x{0}, player_y{0};
    player->get_position(player_x, player_y);
    switch (d)
    {
        case UP:
            if (player_y + 1 < MAP_SIZE && !map[player_x][player_y + 1]->is_blocked()) {
                if (map[player_x][player_y + 1]->get_unit_type() == ITEM) map[player_x][player_y + 1]->triggered_by(*player);
                player->move(d, 1);
            }
            else player->move(d, 0);
            break;
        case DOWN:
            if (player_y - 1 >= 0 && !map[player_x][player_y - 1]->is_blocked()) {
                if (map[player_x][player_y - 1]->get_unit_type() == ITEM) map[player_x][player_y - 1]->triggered_by(*player);
                player->move(d, 1);
            }
            else player->move(d, 0);
            break;
        case LEFT:
            if (player_x - 1 >= 0 && !map[player_x - 1][player_y]->is_blocked()) {
                if (map[player_x - 1][player_y]->get_unit_type() == ITEM) map[player_x - 1][player_y]->triggered_by(*player);
                player->move(d, 1);
            }
            else player->move(d, 0);
            break;
        case RIGHT:
            if (player_x + 1 < MAP_SIZE && !map[player_x + 1][player_y]->is_blocked()) {
                if (map[player_x + 1][player_y]->get_unit_type() == ITEM) map[player_x + 1][player_y]->triggered_by(*player);
                player->move(d, 1);
            }
            else player->move(d, 0);
            break;
        }
}

void GameEngine::player_discover() {
    int player_x{0}, player_y{0};
    player->get_position(player_x, player_y);
    for (int i = -2; i < 3; i++) {
        for (int j = -2; j < 3; j++) {
            if (i == 0 && j == 0) continue;
            if (player_x + i >= 0 && player_y + j >= 0 && player_x + i < MAP_SIZE && player_y + j < MAP_SIZE) {
                map[player_x + i][player_y + j]->set_discovered();
            }
        }
    }
}

void GameEngine::player_attack() {
    int player_atk{0}, player_def{0}, player_x{0}, player_y{0};
    player->get_position(player_x, player_y);
    player->get_atk_def(player_atk, player_def);
    int range = player->get_range();

    switch (player->get_direction())
    {
        case UP:
            for (int j = 1; j <= range; j++) {
                if (player_y + j >= MAP_SIZE) break;
                int defeated = map[player_x][player_y + j]->attacked_by(player_atk);
                if (map[player_x][player_y + j]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x][player_y + j]);
                    if (defeated) {
                        deactivate_monster(dynamic_cast<Monster*> (map[player_x][player_y + j]));
                        player->gain_exp(1);
                    }
                    else if (!dynamic_cast<Monster*> (map[player_x][player_y + j])->is_active()) {
                        activate_monster(dynamic_cast<Monster*> (map[player_x][player_y + j]));
                    }
                }
            }
            break;
        case DOWN:
            for (int j = 1; j <= range; j++) {
                if (player_y - j < 0) break;
                int defeated = map[player_x][player_y - j]->attacked_by(player_atk);
                if (map[player_x][player_y - j]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x][player_y - j]);
                    if (defeated) {
                        deactivate_monster(dynamic_cast<Monster*> (map[player_x][player_y - j]));
                        player->gain_exp(1);
                    }
                    else if (!dynamic_cast<Monster*> (map[player_x][player_y - j])->is_active()) {
                        activate_monster(dynamic_cast<Monster*> (map[player_x][player_y - j]));
                    }
                }
            }
            break;
        case LEFT:
            for (int i = 1; i <= range; i++) {
                if (player_x - i < 0) break;
                int defeated = map[player_x - i][player_y]->attacked_by(player_atk);
                if (map[player_x - i][player_y]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x - i][player_y]);
                    if (defeated) {
                        deactivate_monster(dynamic_cast<Monster*> (map[player_x - i][player_y]));
                        player->gain_exp(1);
                    }
                    else if (!dynamic_cast<Monster*> (map[player_x - i][player_y])->is_active()) {
                        activate_monster(dynamic_cast<Monster*> (map[player_x - i][player_y]));
                    }
                }
            }
            break;
        case RIGHT:
            for (int i = 1; i <= range; i++) {
                if (player_x + i >= MAP_SIZE) break;
                int defeated = map[player_x + i][player_y]->attacked_by(player_atk);
                if (map[player_x + i][player_y]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x + i][player_y]);
                    if (defeated) {
                        deactivate_monster(dynamic_cast<Monster*> (map[player_x + i][player_y]));
                        player->gain_exp(1);
                    }
                    else if (!dynamic_cast<Monster*> (map[player_x + i][player_y])->is_active()) {
                        activate_monster(dynamic_cast<Monster*> (map[player_x + i][player_y]));
                    }
                }
            }
            break;
    }
}

void GameEngine::player_skill() {
    int player_atk{0}, range{0}, player_x{0}, player_y{0};
    if (player->skill(player_atk, range) == 1) return;
    player->get_position(player_x, player_y);

    switch (player->get_direction())
    {
        case UP:
            for (int j = 1; j <= range; j++) {
                int defeated = map[player_x][player_y + j]->attacked_by(player_atk);
                if (map[player_x][player_y + j]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x][player_y + j]);
                    if (defeated) {
                        deactivate_monster(monsterptr);
                        player->gain_exp(1);
                    }
                    else if (!monsterptr->is_active()) {
                        activate_monster(monsterptr);
                    }
                }
            }
            break;
        case DOWN:
            for (int j = 1; j <= range; j++) {
                int defeated = map[player_x][player_y - j]->attacked_by(player_atk);
                if (map[player_x][player_y - j]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x][player_y - j]);
                    if (defeated) {
                        deactivate_monster(monsterptr);
                        player->gain_exp(1);
                    }
                    else if (!monsterptr->is_active()) {
                        activate_monster(monsterptr);
                    }
                }
            }
            break;
        case LEFT:
            for (int i = 1; i <= range; i++) {
                int defeated = map[player_x - i][player_y]->attacked_by(player_atk);
                if (map[player_x - i][player_y]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x - i][player_y]);
                    if (defeated) {
                        deactivate_monster(monsterptr);
                        player->gain_exp(1);
                    }
                    else if (!monsterptr->is_active()) {
                        activate_monster(monsterptr);
                    }
                }
            }
            break;
        case RIGHT:
            for (int i = 1; i <= range; i++) {
                int defeated = map[player_x + i][player_y]->attacked_by(player_atk);
                if (map[player_x + i][player_y]->get_unit_type() == MONSTER) {
                    Monster* monsterptr = dynamic_cast<Monster*> (map[player_x + i][player_y]);
                    if (defeated) {
                        deactivate_monster(monsterptr);
                        player->gain_exp(1);
                    }
                    else if (!monsterptr->is_active()) {
                        activate_monster(monsterptr);
                    }
                }
            }
            break;
    }
}

void GameEngine::monster_follow() {
    MonsterNode* nodeptr = head;
    while (nodeptr != nullptr) {
        nodeptr->data->follow(*player, map);
        nodeptr = nodeptr->next;
    }
}

void GameEngine::monster_act() {
    MonsterNode* nodeptr = head;
    while (nodeptr != nullptr) {
        nodeptr->data->action(*player, map);
        nodeptr = nodeptr->next;
    }
}
