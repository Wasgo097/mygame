#include "Shared.h"
#include "Path.h"
#include "Map.h"
//#include "m_Helmet.h"
//#include "m_Armor.h"
//#include "m_Shield.h"
//#include "m_Bow.h"
//#include "m_Fangs.h"
//#include "m_Sword.h"
//#include "Staff.h"
//#include "Archer.h"
//#include "Fighter.h"
//#include "Mage_warrior.h"
//#include "Tank.h"
//#include "Wizzard.h"
//#include "eArcher.h"
//#include "eFighter.h"
//#include "eMage_warrior.h"
//#include "eTank.h"
//#include "eWizzard.h"
#include "Button.h"
#include "Button_Sprite.h"
#include "Text.h"
#include "Team.h"
//#include "e_Team.h"

//struct AI_result {
//	Being * being;
//	Being * target;
//	uint8_t skill;
//	AI_result(Being * bei, Being* tar, uint8_t skil) :being(bei), target(tar), skill(skil) {}
//};
//AI_result treatment_tactic(tactic * prio) {
//	*prio = 0;
//	return AI_result(nullptr, nullptr, 0);
//}
//AI_result debuff_tactic(tactic * prio) {
//	*prio = 7;
//	return AI_result(nullptr, nullptr, 0);
//}
//AI_result buff_tactic(tactic * prio) {
//	*prio = 2;
//	return AI_result(nullptr, nullptr, 0);
//}
//AI_result dmg_tactic(tactic * prio) {
//	*prio = 4;
//	return AI_result(nullptr, nullptr, 0);
//}
int main(){
	srand(time(NULL));
	//0 = game 1 = test
	int test = 0;
	if (test == 1) {
		/*std::vector<std::pair<Effect, unsigned short>> effect;
		effect.push_back(std::make_pair(Effect::bleeding, 2));
		effect.push_back(std::make_pair(Effect::stunning,1));
		effect.push_back(std::make_pair(Effect::toxic, 0));
		effect.push_back(std::make_pair(Effect::buff_dex ,0));
		effect.push_back(std::make_pair(Effect::buff_str, 2));
		effect.push_back(std::make_pair(Effect::buff_str, 3));
		effect.push_back(std::make_pair(Effect::buff_str, 0));
		effect.push_back(std::make_pair(Effect::buff_str, 0));
		int null_buff = 0;
		for (int i = effect.size() - 1; i >= 0; i--) {
			if (effect[i].second < 1)null_buff++;
			else break;
		}
		for (size_t i = 0; i < effect.size()-null_buff; i++) {
			if (effect[i].second == 0&&effect[effect.size() - 1 - null_buff].second>0) {
				std::swap(effect[i], effect[effect.size() - 1 - null_buff]);
				null_buff++;
			}
		}
		for (int i = 0; i < null_buff; i++)effect.pop_back();
		for (const auto&x : effect) {
			std::cout << x.second << std::endl;
		}*/
		/*tactic all_tactic[4]{ 0,0,0,1 };
		size_t max_index = -1;
		AI_result treatment_result = treatment_tactic(&all_tactic[0]);
		AI_result debuff_result = debuff_tactic(&all_tactic[1]);
		AI_result buff_result = buff_tactic(&all_tactic[2]);
		AI_result dmg_result = dmg_tactic(&all_tactic[3]);
		for (int i = 0, max_value = -128; i < 4; i++) {
			if (all_tactic[i] > max_value) {
				max_value = all_tactic[i];
				max_index = i;
			}
		}
		std::cout << "Max vaule = " << (int)all_tactic[max_index] << " on " << max_index+1 << " position";*/
	}
	if (test == 0) {
		string map("Map/main_map2.bmp");
		string amap("Map/access_map2.bmp");
		string tmap("Map/terrain_map2.bmp");
		string bmap("Map/monster_map2.bmp");
		string map_access("Map/access.txt");
		string map_boss("Map/boss.txt");
		string map_terrain("Map/terrain.txt");
		bitmap_image amage(amap);
		if (!amage) {
			printf("Error - Failed to open: main map!\n");
			std::cin.ignore();
			exit(0);
		}
		bitmap_image tmage(tmap);
		if (!tmage) {
			printf("Error - Failed to open: terrain map!\n");
			std::cin.ignore();
			exit(0);
		}
		bitmap_image bmage(bmap);
		if (!bmage) {
			printf("Error - Failed to open: boss map!\n");
			std::cin.ignore();
			exit(0);
		}
		unsigned int x, y;
		/*x = 1920;
		y = 1080;*/
		x = 1280;
		y = 768;
		std::cout << "Type your resolution\n" << std::endl;
		//std::cout << "X:"; std::cin >> x;
		//std::cout << "Y:"; std::cin >> y;
		const size_t height = y;
		const size_t width = x;
		sf::RenderWindow window(sf::VideoMode(width,height), "Opus Magnum", sf::Style::Fullscreen);
		//window.close();
		sf::Vector2f ratio;
		//background config
		sf::Texture backgroud_map_texture;
		sf::Sprite background;
		if (!backgroud_map_texture.loadFromFile(map)) {
			std::cout << "Error :" << map << " not found!" << std::endl;
			std::cin.ignore(1);
			return 0;
		}
		else {
			sf::Vector2u TextureSize = backgroud_map_texture.getSize();
			sf::Vector2u WindowSize = window.getSize();
			ratio.x = (float)WindowSize.x / TextureSize.x;
			//std::cout << (float)WindowSize.x;
			ratio.y = (float)WindowSize.y / TextureSize.y;
			//std::cout << (float)WindowSize.y;
			background.setTexture(backgroud_map_texture);
			background.setScale(ratio.x, ratio.y);
		}
		//load game/ new game inic
		bool game_type = false;
		sf::Texture main_menu_texture;
		sf::Sprite main_menu;
		if (!main_menu_texture.loadFromFile("Map/menu.jpg")) {
			std::cout << "Error :" << "Map/menu.jpg" << " not found!" << std::endl;
			std::cin.ignore(1);
			return 0;
		}
		main_menu.setTexture(main_menu_texture);
		main_menu.setScale(ratio.x, ratio.y);
		window.draw(main_menu);
		window.display();
		Button_Sprite* newg = new Button_Sprite("Main_button/ng-um.png", "Main_button/ng-m.png", &window, ratio, sf::Vector2u(0.4*width, 0.85*height));
		Button_Sprite * loadg = new Button_Sprite("Main_button/lg-um.png", "Main_button/lg-m.png", &window, ratio, sf::Vector2u(0.4*width, 0.65*height));
		//save maps to files
		bool create = false;
		std::fstream control_maps;
		control_maps.open(map_access, std::ios::in);
		if (!control_maps.good())create = 1;
		control_maps.close();
		control_maps.open(map_terrain, std::ios::in);
		if (!control_maps.good())create = 1;
		control_maps.close();
		control_maps.open(map_boss, std::ios::in);
		if (!control_maps.good())create = 1;
		control_maps.close();
		bool** map_access_bool = nullptr;
		char** map_terrain_char = nullptr;
		char** map_boss_char = nullptr;
		if (create) {
			map_access_bool = access_save_to_file(ratio, amage, height, width, map_access);
			map_terrain_char = terrain_save_to_file(ratio, tmage, height, width, map_terrain);
			map_boss_char = boss_save_to_file(ratio, bmage, height, width, map_boss);
		}
		//load maps from files
		bool** map_access2_bool = access_load_from_file(ratio, map_access, height, width);
		char** map_terrain2_char = terrain_load_from_file(ratio, map_terrain, height, width);
		char** map_boss2_char = boss_load_from_file(ratio, map_boss, height, width);
		//control save and load map
		if (create) {
			if (control(map_access_bool, map_access2_bool, width, height))std::cout << "Access all right";
			else std::cout << "Access dont right";
			std::cout << std::endl;
			if (control(map_terrain_char, map_terrain2_char, width, height))std::cout << "Terrain all right";
			else std::cout << "Terrain dont right";
			std::cout << std::endl;
			if (control(map_boss_char, map_boss2_char, width, height))std::cout << "Boss all right";
			else std::cout << "Boss dont right";
			std::cout << std::endl;
		}
		//team mapmaker config
		sf::Texture map_maker_texture;
		if (!map_maker_texture.loadFromFile("Ico/map_marker.png")) {
			window.close();
			std::cout << "Error :" << "Ico/map_marker.png" << " not found!" << std::endl;
			std::cin.ignore(1);
			return 0;
		}
		sf::Sprite map_maker(map_maker_texture);
		map_maker.setPosition(100, 100);
		map_maker.setOrigin(map_maker_texture.getSize().x / 2, map_maker_texture.getSize().y - map_maker_texture.getSize().y*0.1);
		//map config
		Map maps(map_access2_bool, map_boss2_char, map_terrain2_char, width, height);
		//team config
		std::shared_ptr<Team> team(new Team(ratio));
		//team patch on map config
		Path path(&window, map_maker, map_maker, background, &maps, team);
		//load/new
		while (window.isOpen() && !game_type) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					window.close();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (loadg->is_clicked(sf::Mouse::getPosition())) {
						team->load_from_file();
						path.load_pos();
						game_type = true;
					}
					else if (newg->is_clicked(sf::Mouse::getPosition())) {
						game_type = true;
					}
					else continue;
				}
				if (loadg->is_target(sf::Mouse::getPosition()))loadg->set_target();
				else loadg->set_free();
				if (newg->is_target(sf::Mouse::getPosition())) newg->set_target();
				else newg->set_free();
				window.clear();
				window.draw(main_menu);
				loadg->draw();
				newg->draw();
				window.display();
			}
		}
		delete newg;
		delete loadg;
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::A))window.close();
				//save	
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) {
					team->save_to_file();
					path.save_pos();
				}
				//load game
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) {
					team->load_from_file();
					path.load_pos();
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						path.add_new_point(sf::Mouse::getPosition());
						wait(1);
					}
					path.realize_path();
					window.clear();
					window.draw(background);
					window.draw(map_maker);
					window.display();
				}
				window.clear();
				window.draw(background);
				window.draw(map_maker);
				window.display();
			}
		}
		if (create) {
			clear_map(map_access_bool, height);
			clear_map(map_terrain_char, height);
			clear_map(map_boss_char, height);
		}
	}
	std::cin.ignore();
	return 0;
}