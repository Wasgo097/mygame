#pragma once
#include "base_e_Team.h"
class boss_e_Team :public base_e_Team {
	sf::Texture texture[3];
public:
	boss_e_Team(const sf::Vector2f& ratio, Quality q, char fight_type) {
		//int texture_index = 0;
		//int fig = 0;
		//int wiz = 0;
		//int m_war = 0;
		//int tan = 0;
		//int arc = 0;
		//this->ratio = ratio;
		//while (e_team_full.size() < 3) {
		//	int j = std::rand() % 5;
		//	if (j == 0 && fig < 2) {
		//		fig++;
		//		//e_team.push_back(rand_eFighter(q));
		//		string path_texture = "Enemy/fight" + std::to_string(std::rand() % 3 + 1) + ".png";
		//		if (!texture[texture_index].loadFromFile(path_texture)) {
		//			std::cout << "Error with enemies team generation";
		//			exit(-1);
		//		}
		//		sf::Sprite sprite;
		//		sprite.setTexture(texture[texture_index]);
		//		//sprite_e_team.push_back(sprite);
		//		e_team_full.push_back(std::make_pair(sprite, rand_eFighter(q)));
		//		texture_index++;
		//	}
		//	else if (j == 1 && wiz < 2) {
		//		wiz++;
		//		//e_team.push_back(rand_eWizzard(q));
		//		string path_texture = "Enemy/wizz" + std::to_string(std::rand() % 3 + 1) + ".png";
		//		if (!texture[texture_index].loadFromFile(path_texture)) {
		//			std::cout << "Error with enemies team generation";
		//			exit(-1);
		//		}
		//		sf::Sprite sprite;
		//		sprite.setTexture(texture[texture_index]);
		//		e_team_full.push_back(std::make_pair(sprite, rand_eWizzard(q)));
		//		//sprite_e_team.push_back(sprite);
		//		texture_index++;
		//	}
		//	else if (j == 2 && m_war < 2) {
		//		m_war++;
		//		//e_team.push_back(rand_eMage_warrior(q));
		//		string path_texture = "Enemy/m_warr" + std::to_string(std::rand() % 3 + 1) + ".png";
		//		if (!texture[texture_index].loadFromFile(path_texture)) {
		//			std::cout << "Error with enemies team generation";
		//			exit(-1);
		//		}
		//		sf::Sprite sprite;
		//		sprite.setTexture(texture[texture_index]);
		//		//sprite_e_team.push_back(sprite);
		//		e_team_full.push_back(std::make_pair(sprite, rand_eMage_warrior(q)));
		//		texture_index++;
		//	}
		//	else if (j == 3 && tan < 2) {
		//		tan++;
		//		//e_team.push_back(rand_eTank(q));
		//		string path_texture = "Enemy/tank" + std::to_string(std::rand() % 3 + 1) + ".png";
		//		if (!texture[texture_index].loadFromFile(path_texture)) {
		//			std::cout << "Error with enemies team generation";
		//			exit(-1);
		//		}
		//		sf::Sprite sprite;
		//		sprite.setTexture(texture[texture_index]);
		//		//sprite_e_team.push_back(sprite);
		//		e_team_full.push_back(std::make_pair(sprite, rand_eTank(q)));
		//		texture_index++;
		//	}
		//	else if (j == 4 && arc < 2) {
		//		arc++;
		//		//e_team.push_back(rand_eArcher(q));
		//		string path_texture = "Enemy/arch" + std::to_string(std::rand() % 3 + 1) + ".png";
		//		if (!texture[texture_index].loadFromFile(path_texture)) {
		//			std::cout << "Error with enemies team generation";
		//			exit(-1);
		//		}
		//		sf::Sprite sprite;
		//		sprite.setTexture(texture[texture_index]);
		//		//sprite_e_team.push_back(sprite);
		//		e_team_full.push_back(std::make_pair(sprite, rand_eArcher(q)));
		//		texture_index++;
		//	}
		//	else continue;
		//}
		//for (auto c : e_team_full) {
		//	c.first.setScale(ratio.x, ratio.y);
		//}
		string path = "Enemy/boss/";
		if (fight_type == 'w') {
			if (!texture[0].loadFromFile(path + "werewolf_sup1.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite1;
			sprite1.setTexture(texture[0]);
			e_team_full.push_back(std::make_pair(sprite1, rand_wolf(q)));
			if (!texture[1].loadFromFile(path + "werewolf.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite2;
			sprite2.setTexture(texture[1]);
			e_team_full.push_back(std::make_pair(sprite2, rand_werewolf(q)));
			if (!texture[2].loadFromFile(path + "werewolf_sup2.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite3;
			sprite3.setTexture(texture[2]);
			e_team_full.push_back(std::make_pair(sprite3, rand_wolf(q)));
		}
		else if (fight_type == 's') {
			if (!texture[0].loadFromFile(path + "spider_sup1.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite1;
			sprite1.setTexture(texture[0]);
			e_team_full.push_back(std::make_pair(sprite1, rand_eArcher(q)));
			if (!texture[1].loadFromFile(path + "spider.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite2;
			sprite2.setTexture(texture[1]);
			e_team_full.push_back(std::make_pair(sprite2, rand_spider(q)));
			if (!texture[2].loadFromFile(path + "spider_sup2.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite3;
			sprite3.setTexture(texture[2]);
			e_team_full.push_back(std::make_pair(sprite3, rand_eFighter(q)));
		}
		else if (fight_type == 'g') {
			if (!texture[0].loadFromFile(path + "ghost_sup1.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite1;
			sprite1.setTexture(texture[0]);
			e_team_full.push_back(std::make_pair(sprite1, rand_eFighter(q)));
			if (!texture[1].loadFromFile(path + "ghost.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite2;
			sprite2.setTexture(texture[1]);
			e_team_full.push_back(std::make_pair(sprite2, rand_ghost(q)));
			if (!texture[2].loadFromFile(path + "ghost_sup2.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite3;
			sprite3.setTexture(texture[2]);
			e_team_full.push_back(std::make_pair(sprite3, rand_eWizzard(q)));
		}
		else if (fight_type == 'o') {
			if (!texture[0].loadFromFile(path + "orc_sup1.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite1;
			sprite1.setTexture(texture[0]);
			e_team_full.push_back(std::make_pair(sprite1, rand_eFighter(q)));
			if (!texture[1].loadFromFile(path + "orc.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite2;
			sprite2.setTexture(texture[1]);
			e_team_full.push_back(std::make_pair(sprite2, rand_orc(q)));
			if (!texture[2].loadFromFile(path + "orc_sup2.png")) {
				std::cout << "Error with enemies team generation";
				exit(-1);
			}
			sf::Sprite sprite3;
			sprite3.setTexture(texture[2]);
			e_team_full.push_back(std::make_pair(sprite3, rand_eArcher(q)));
		}
		for (auto & c : e_team_full) {
			c.first.setScale(ratio.x, ratio.y);
		}
	}
};