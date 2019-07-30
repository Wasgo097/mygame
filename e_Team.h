#pragma once
#include "base_e_Team.h"
class e_Team:public base_e_Team{
	sf::Texture texture[5];
public:
	e_Team(const sf::Vector2f& ratio, Quality q) {
		int texture_index = 0;
		int fig = 0;
		int wiz = 0;
		int m_war = 0;
		int tan = 0;
		int arc = 0;
		this->ratio = ratio;
		while (e_team_full.size()<5) {
			int j = std::rand() % 5;
			if (j == 0 && fig<2) {
				fig++;
				//e_team.push_back(rand_eFighter(q));
				string path_texture = "Enemy/fight" + std::to_string(std::rand() % 3 + 1) + ".png";
				if (!texture[texture_index].loadFromFile(path_texture)) {
					std::cout << "Error with enemies team generation";
					exit(-1);
				}
				sf::Sprite sprite;
				sprite.setTexture(texture[texture_index]);
				//sprite_e_team.push_back(sprite);
				e_team_full.push_back(std::make_pair(sprite, rand_eFighter(q)));
				texture_index++;
			}
			else if (j == 1 && wiz < 2) {
				wiz++;
				//e_team.push_back(rand_eWizzard(q));
				string path_texture = "Enemy/wizz" + std::to_string(std::rand() % 3 + 1) + ".png";
				if (!texture[texture_index].loadFromFile(path_texture)) {
					std::cout << "Error with enemies team generation";
					exit(-1);
				}
				sf::Sprite sprite;
				sprite.setTexture(texture[texture_index]);
				e_team_full.push_back(std::make_pair(sprite, rand_eWizzard(q)));
				//sprite_e_team.push_back(sprite);
				texture_index++;
			}
			else if (j == 2 && m_war<2) {
				m_war++;
				//e_team.push_back(rand_eMage_warrior(q));
				string path_texture = "Enemy/m_warr" + std::to_string(std::rand() % 3 + 1) + ".png";
				if (!texture[texture_index].loadFromFile(path_texture)) {
					std::cout << "Error with enemies team generation";
					exit(-1);
				}
				sf::Sprite sprite;
				sprite.setTexture(texture[texture_index]);
				//sprite_e_team.push_back(sprite);
				e_team_full.push_back(std::make_pair(sprite, rand_eMage_warrior(q)));
				texture_index++;
			}
			else if (j == 3 && tan<2) {
				tan++;
				//e_team.push_back(rand_eTank(q));
				string path_texture = "Enemy/tank" + std::to_string(std::rand() % 3 + 1) + ".png";
				if (!texture[texture_index].loadFromFile(path_texture)) {
					std::cout << "Error with enemies team generation";
					exit(-1);
				}
				sf::Sprite sprite;
				sprite.setTexture(texture[texture_index]);
				//sprite_e_team.push_back(sprite);
				e_team_full.push_back(std::make_pair(sprite, rand_eTank(q)));
				texture_index++;
			}
			else if (j == 4 && arc<2) {
				arc++;
				//e_team.push_back(rand_eArcher(q));
				string path_texture = "Enemy/arch" + std::to_string(std::rand() % 3 + 1) + ".png";
				if (!texture[texture_index].loadFromFile(path_texture)) {
					std::cout << "Error with enemies team generation";
					exit(-1);
				}
				sf::Sprite sprite;
				sprite.setTexture(texture[texture_index]);
				//sprite_e_team.push_back(sprite);
				e_team_full.push_back(std::make_pair(sprite, rand_eArcher(q)));
				texture_index++;
			}
			else continue;
		}
		for (auto c : e_team_full) {
			c.first.setScale(ratio.x, ratio.y);
		}
	}
	~e_Team(){}
};
