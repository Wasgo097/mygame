#pragma once
#include "Team.h"
#include "e_Team.h"
#include "boss_e_Team.h"
#include "Text.h"
#include "Button.h"
typedef int8_t tactic;
struct AI_result {
	Being * being;
	Being * target;
	uint8_t skill;
	tactic strength;
	AI_result(Being * bei, Being* tar, uint8_t skil, tactic str) :being(bei), target(tar), skill(skil), strength(str) {}
	AI_result() = default;
};
struct Prize {
	uint8_t archer_action = 0;
	uint8_t m_warrior_action = 0;
	uint8_t tank_action = 0;
	uint8_t wizzard_action = 0;
	uint8_t fighter_action = 0;
};
class Battle {
private:
	sf::RenderWindow * window;
	std::shared_ptr<Team> team;
	std::unique_ptr<base_e_Team> e_team;
	sf::Sprite background;
	sf::Texture texture;
	sf::Vector2f ratio;
	std::list<Text*> team_stats;
	std::list<Text*> eteam_stats;
	std::vector<std::pair<Button*,std::shared_ptr<Party_member>>> team_button;
	std::vector<std::pair<Button*, Enemies*>> enemies_button;
	std::vector<Button *> skill_button;
	std::list<std::shared_ptr<Text>> all_action;
	char terrain;
	bool * team_life=nullptr;
	bool * enemies_life=nullptr;
	Quality prize_quality;
	//all enemies in fight
	const int enemies = 5;
	int team_active=5;
	int enemies_active=5;
	//chech who is alive
	void check();
	void draw_alive();
	void show_actual_stats();
	void update_status();
	void our_round();
	void enemy_round();
public:
	Battle(sf::RenderWindow * win, std::shared_ptr<Team> team, char terrain, char fight_type );
	~Battle();
	void init();
private:
	Prize prize;
	void prizee();
	void AI();
	AI_result treatment_tactic();
	AI_result debuff_tactic();
	AI_result buff_tactic();
	AI_result dmg_tactic();
	AI_result result;
};