#include "Path.h"
#include "Shared.h"

void Path::realize_path() {
	const int desert = 997;
	const int forest = desert-2;
	const int mountain = desert-1;
	bool pause = 0;
	bool fight_event = false;
	while ((obj_t->getPosition() != sf::Vector2f(path.front()) )&& !pause) {
		sf::Vector2i temp_pos = current;
		int fight = std::rand() % 1001;
		char c = map->get_position(temp_pos).terrain;
		switch (c) {
		case 'f':
			if (fight > forest)fight_event = 1;
			break;
		case 'd':
			if (fight > desert)fight_event = 1;
			break;
		case'm':
			if (fight > mountain)fight_event = 1;
			break;
		default:
			std::cout << "Error with map!" << std::endl;
			window->close();
			std::cin.ignore();
			exit(-1);
		}
		if (fight_event){
			char temp = std::rand() % 5;
			if (temp < 3|| map->get_position(temp_pos).boss=='n') {
				pause = 1;
				clear_path();
				Battle battle(window, team, c, 'n');
				battle.init();
				break;
			}
			else {
				pause = 1;
				clear_path();
				string boss=("");
				switch (map->get_position(temp_pos).boss) {
				case 'o':
					boss = " orc?";
					break;
				case 's':
					boss = " spider?";
					break;
				case 'g':
					boss = " ghost?";
					break;
				case 'w':
					boss = " werewolf?";
					break;
				}
				Text question("Do you want fight with strong" + boss, window, team->get_ratio(), sf::Vector2u(window->getSize().x*0.2, window->getSize().x*0.2));
				Button yes(window, team->get_ratio(), "Yes", sf::Vector2u(window->getSize().x*0.2, window->getSize().x*0.25));
				Button no(window, team->get_ratio(), "No", sf::Vector2u(window->getSize().x*0.25, window->getSize().x*0.25));
				bool clicked = false;
				bool fight = false;
				while (!clicked) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						if (yes.is_clicked(sf::Mouse::getPosition())) {
							clicked = 1;
							fight = true;
						}
						else if (no.is_clicked(sf::Mouse::getPosition())) {
							clicked = 1;
						}
					}
					if (yes.is_target(sf::Mouse::getPosition()))yes.set_yellow_background();
					else yes.set_white_background();
					if (no.is_target(sf::Mouse::getPosition())) no.set_yellow_background();
					else no.set_white_background();
					window->clear();
					window->draw(*background);
					window->draw(*obj_d);
					question.draw();
					yes.draw();
					no.draw();
					window->display();
				}
				if (fight) {
					Battle battle(window, team, c, map->get_position(temp_pos).boss);
					battle.init();
				}
				else break;
			}
		}
		else {
			if (obj_t->getPosition().x > path.front().x) {
				temp_pos.x--;
			}
			else if (obj_t->getPosition().x < path.front().x) {
				temp_pos.x++;
			}
			else {}
			if (obj_t->getPosition().y < path.front().y) {
				temp_pos.y++;
			}
			else if (obj_t->getPosition().y > path.front().y) {
				temp_pos.y--;
			}
			if (map->get_position(temp_pos).access) {
				obj_t->setPosition(sf::Vector2f(temp_pos));
				current = temp_pos;
				window->clear();
				window->draw(*background);
				window->draw(*obj_d);
				window->display();
			}
			else {
				pause = 1;
				clear_path();
				break;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				pause = 1;
				clear_path();
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))window->close();
			//in game 
			//wait(15);
			//in test
			wait(2);
		}
	}
	while (!path.empty() && !pause) {
		sf::Vector2i temp = path.front();
		int fight = std::rand() % 1001;
		char c = map->get_position(temp).terrain;
		switch (c) {
		case 'f':
			if (fight > forest)fight_event = 1;
			break;
		case 'd':
			if (fight > desert)fight_event = 1;
			break;
		case'm':
			if (fight > mountain)fight_event = 1;
			break;
		default:
			std::cout << "Error with map!" << std::endl;
		}
		if (fight_event) {
			char tempp = std::rand() % 5;
			if (tempp < 3 || map->get_position(temp).boss == 'n') {
				pause = 1;
				clear_path();
				Battle battle(window, team, c, 'n');
				battle.init();
				break;
			}
			else {
				pause = 1;
				clear_path();
				string boss = ("");
				switch (map->get_position(temp).boss) {
				case 'o':
					boss = " orc?";
					break;
				case 's':
					boss = " spider?";
					break;
				case 'g':
					boss = " ghost?";
					break;
				case 'w':
					boss = " werewolf?";
					break;
				}
				Text question("Do you want fight with strong" + boss, window, team->get_ratio(), sf::Vector2u(window->getSize().x*0.2, window->getSize().x*0.2));
				Button yes(window, team->get_ratio(), "Yes", sf::Vector2u(window->getSize().x*0.2, window->getSize().x*0.25));
				Button no(window, team->get_ratio(), "No", sf::Vector2u(window->getSize().x*0.25, window->getSize().x*0.25));
				bool clicked = false;
				bool fight = false;
				while (!clicked) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
						if (yes.is_clicked(sf::Mouse::getPosition())) {
							clicked = 1;
							fight = true;
						}
						else if (no.is_clicked(sf::Mouse::getPosition())) {
							clicked = 1;
						}
					}
					if (yes.is_target(sf::Mouse::getPosition()))yes.set_yellow_background();
					else yes.set_white_background();
					if (no.is_target(sf::Mouse::getPosition())) no.set_yellow_background();
					else no.set_white_background();
					window->clear();
					window->draw(*background);
					window->draw(*obj_d);
					question.draw();
					yes.draw();
					no.draw();
					window->display();
				}
				if (fight) {
					Battle battle(window, team, c, map->get_position(temp).boss);
					battle.init();
				}
				else break;
			}
		}
		else if (map->get_position(temp).access) {
			obj_t->setPosition(sf::Vector2f(path.front()));
			current = path.front();
			window->clear();
			window->draw(*background);
			window->draw(*obj_d);
			window->display();
			path.pop();
		}
		else {
			pause = 1;
			clear_path();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			pause = 1;
			clear_path();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))window->close();
		//in game
		//wait(15);
		//in test
		wait(2);
	}
}
void Path::save_pos(){
	std::ofstream str;
	str.open("save/team.bin",std::ios::out|std::ios::binary);
	str.write((char*)&current.x, sizeof(current.x));
	str.write((char*)&current.y, sizeof(current.y));
	str.close();
}
void Path::load_pos(){
	std::ifstream str;
	str.open("save/team.bin", std::ios::in | std::ios::binary);
	str.read((char*)&current.x, sizeof(current.x));
	str.read((char*)&current.y, sizeof(current.y));
	str.close();
	window->clear();
	obj_t->setPosition(sf::Vector2f(current));
	window->draw(*background);
	window->draw(*obj_d);
	window->display();
}
