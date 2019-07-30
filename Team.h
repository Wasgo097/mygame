#pragma once
#include "Archer.h"
#include "Fighter.h"
#include "Mage_warrior.h"
#include "Tank.h"
#include "Wizzard.h"
class Team {
	std::pair < sf::Sprite *, std::shared_ptr<Archer>> archer_full;
	std::pair < sf::Sprite *, std::shared_ptr<Fighter>> fighter_full;
	std::pair < sf::Sprite *, std::shared_ptr<Mage_warrior>> m_warrior_full;
	std::pair < sf::Sprite *, std::shared_ptr<Tank>> tank_full;
	std::pair < sf::Sprite *, std::shared_ptr<Wizzard>> wizzard_full;
	std::shared_ptr<Archer> archer;
	std::shared_ptr<Fighter> fighter;
	std::shared_ptr<Mage_warrior> m_warrior;
	std::shared_ptr<Tank> tank;
	std::shared_ptr<Wizzard> wizzard;
	/*std::vector<std::shared_ptr<Party_member>> team;
	std::vector<sf::Sprite*> sprite_team;*/
	std::vector<std::pair < sf::Sprite *, std::shared_ptr<Party_member>>> team_full;
	sf::Sprite archer_sprite;
	sf::Sprite fighter_sprite;
	sf::Sprite m_warrior_sprite;
	sf::Sprite tank_sprite;
	sf::Sprite wizzard_sprite;
	sf::Texture archer_texture;
	sf::Texture fighter_texture;
	sf::Texture m_warrior_texture;
	sf::Texture tank_texture;
	sf::Texture wizzard_texture;
	sf::Vector2f ratio;
public:
	Team(const sf::Vector2f & ratio, Quality q = Quality::weak) {
		archer = std::make_shared<Archer>(rand_bow(q), rand_helmet(q), rand_armor(q), rand_shield(q));
		fighter = std::make_shared<Fighter>(rand_sword(q), rand_helmet(q), rand_armor(q), rand_shield(q));
		m_warrior = std::make_shared<Mage_warrior>(rand_sword(q), rand_helmet(q), rand_armor(q), rand_shield(q));
		tank = std::make_shared<Tank>(rand_sword(q), rand_helmet(q), rand_armor(q), rand_shield(q));
		wizzard = std::make_shared<Wizzard>(rand_staff(q), rand_helmet(q), rand_armor(q), rand_shield(q));
		/*team.push_back(archer);
		team.push_back(fighter);
		team.push_back(m_warrior);
		team.push_back(tank);
		team.push_back(wizzard);*/
		if (!archer_texture.loadFromFile("Hero/Archer.png")) {
			std::cout << "Error :" << "Hero/Archer.png" << " not found!" << std::endl;
			std::cin.ignore(1);
			exit(0);
		}
		archer_sprite.setTexture(archer_texture);
		team_full.push_back(std::make_pair(&archer_sprite, archer));
		if (!fighter_texture.loadFromFile("Hero/Fighter.png")) {
			std::cout << "Error :" << "Hero/Fighter.png" << " not found!" << std::endl;
			std::cin.ignore(1);
			exit(0);
		}
		fighter_sprite.setTexture(fighter_texture);
		team_full.push_back(std::make_pair(&fighter_sprite, fighter));
		if (!m_warrior_texture.loadFromFile("Hero/Mage warrior.png")) {
			std::cout << "Error :" << "Hero/Mage warrior.png" << " not found!" << std::endl;
			std::cin.ignore(1);
			exit(0);
		}
		m_warrior_sprite.setTexture(m_warrior_texture);
		team_full.push_back(std::make_pair(&m_warrior_sprite,m_warrior));
		if (!tank_texture.loadFromFile("Hero/Tank.png")) {
			std::cout << "Error :" << "Hero/Tank.png" << " not found!" << std::endl;
			std::cin.ignore(1);
			exit(0);
		}
		tank_sprite.setTexture(tank_texture);
		team_full.push_back(std::make_pair(&tank_sprite, tank));
		if (!wizzard_texture.loadFromFile("Hero/Wizzard.png")) {
			std::cout << "Error :" << "Hero/Wizard.png" << " not found!" << std::endl;
			std::cin.ignore(1);
			exit(0);
		}
		wizzard_sprite.setTexture(wizzard_texture);
		team_full.push_back(std::make_pair(&wizzard_sprite, wizzard));
		/*sprite_team.push_back(&archer_sprite);
		sprite_team.push_back(&fighter_sprite);
		sprite_team.push_back(&m_warrior_sprite);
		sprite_team.push_back(&tank_sprite);
		sprite_team.push_back(&wizzard_sprite);*/
		for (auto& c : team_full) {
			c.first->setScale(ratio.x, ratio.y);
		}
		this->ratio = ratio;
	}
	/*auto get_team() { return& team; }
	auto get_sprite_team() {return &sprite_team;}*/
	auto get_team() { return &team_full; }
	auto get_archer() { return team_full[0]; }
	auto get_fighter() { return team_full[1]; }
	auto get_m_warrior() { return team_full[2]; }
	auto get_tank() { return team_full[3]; }
	auto get_wizzard() { return team_full[4]; }
	auto get_ratio() { return ratio; }
	void save_to_file()const;
	void load_from_file();
};