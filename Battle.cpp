#include "Battle.h"
Battle::Battle(sf::RenderWindow * win, std::shared_ptr<Team> team, char terrain, char fight_type) :enemies(fight_type == 'n' ? 5:3),enemies_active(fight_type == 'n' ? 5 : 3){
	team_life = new bool[5];
	enemies_life = new bool[enemies];
	this->terrain = terrain;
	window = win;
	this->team = team;
	ratio = this->team->get_ratio();
	prize_quality = get_rand_quality();
	string path;
	//n- normal other symbol mean boos s-spider, o-orc, g-ghost, w-werewolf
	if (fight_type == 'n') {
		e_team = std::make_unique<e_Team>(ratio, prize_quality);
		switch (terrain) {
		case 'd':
			path = "Fight/d.jpg";
			break;
		case'm':
			path = "Fight/m.jpg";
			break;
		case'f':
			path = "Fight/f.jpg";
			break;
		default:
			std::cout << "error in map terrain";
			window->close();
			std::cin.ignore();
			exit(-1);
		}
	}
	else {
		if (fight_type == 'w') path = "Fight/boss/greenland.jpg";
		else if (fight_type == 's') path = "Fight/boss/forest.jpg";
		else if (fight_type == 'g') path = "Fight/boss/cementary.jpg";
		else if (fight_type == 'o')path = "Fight/boss/mountain.jpg";
		else {
		std::cout << "error in map terrain";
		window->close();
		std::cin.ignore();
		exit(-1);
		}
		e_team = std::make_unique<boss_e_Team>(ratio, prize_quality, fight_type);
	}
	if (!texture.loadFromFile(path)) {
		window->close();
		std::cout << "Error with fight background";
		std::cin.ignore();
		exit(-1);
	}
	background.setTexture(texture);
	background.setScale(ratio.x, ratio.y);
	int iterator = 0;
	for (auto&x : *this->team->get_team()) {
		string classs = typeid(*x.second).name();
		team_stats.push_back(new Text(classs + " Hp:" + std::to_string(x.second->r_health()) + "/" + std::to_string(x.second->r_m_health()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + iterator * 0.05*window->getSize().y)));
		iterator++;
		team_stats.push_back(new Text("St:" + std::to_string(x.second->r_stamina()) + "/" + std::to_string(x.second->r_m_stamina()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + iterator * 0.05*window->getSize().y)));
		iterator++;
	}
	iterator = 0;
	for (auto &x : *e_team->get_e_team()) {
		string classs = typeid(*x.second).name();
		eteam_stats.push_back(new Text(classs + " Hp:" + std::to_string(x.second->r_health()) + "/" + std::to_string(x.second->r_m_health()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + iterator * 0.05*window->getSize().y)));
		iterator++;
		eteam_stats.push_back(new Text("St:" + std::to_string(x.second->r_stamina()) + "/" + std::to_string(x.second->r_m_stamina()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + iterator * 0.05*window->getSize().y)));
		iterator++;
	}
	//button config
	iterator = 0;
	for (auto x : *team->get_team()) {
		team_button.push_back(std::make_pair(new Button(window, ratio, typeid(*x.second).name(), sf::Vector2u(window->getSize().x*0.05*ratio.x + iterator * 250, window->getSize().y*0.2*ratio.y)), x.second)); iterator++;
	}
	iterator = 0;
	for (auto x : *e_team->get_e_team()) {
		enemies_button.push_back(std::make_pair(new Button(window, ratio, typeid(*x.second).name(), sf::Vector2u(window->getSize().x*0.05*ratio.x + iterator * 250, window->getSize().y*0.4*ratio.y)), x.second)); iterator++;
	}
	iterator = 0;
	for (int i = 1; i < 4; i++) {
		skill_button.push_back(new Button(window, ratio, "Skill " + std::to_string(i), sf::Vector2u(window->getSize().x*0.05*ratio.x + iterator * 250, window->getSize().y*0.2*ratio.y))); iterator++;
	}
}
Battle::~Battle() {
	if (team_life != nullptr)delete[]team_life;
	if (enemies_life != nullptr)delete[]enemies_life;
	for (auto&c : team_stats)if (c != nullptr)delete c;
	for (auto&c : eteam_stats)if (c != nullptr)delete c;
	for (auto&c : team_button)if (c.first != nullptr)delete c.first;
	for (auto&c : skill_button)if (c != nullptr)delete c;
	for (auto &c : enemies_button)if (c.first != nullptr)delete c.first;
}
void Battle::init() {
	window->clear();
	window->draw(background);
	window->display();
	unsigned int size_x, size_y;
	size_x = window->getSize().x;
	size_y = window->getSize().y;
	unsigned int margin_x;
	unsigned int margin_y;
	unsigned int higher_margin_x;
	unsigned int higher_margin_y;
	unsigned int step;
	unsigned int highest_step;
	int first = 0, second = 0, i = 0;
	if (terrain == 'f' || terrain == 'd') {
		margin_x = 0.0625*size_x;
		margin_y = 0.76*size_y;
		higher_margin_x = 0.18*size_x;
		higher_margin_y = 0.83*size_y;
		step = 0.1*size_y;
		highest_step = 0.13*size_y;
		for (auto c : *team->get_team()) {
			c.first->setOrigin(c.first->getTexture()->getSize().x / 2, c.first->getTexture()->getSize().y / 1.05);
			if (i % 2 == 0) {
				c.first->setPosition(margin_x, margin_y + first * step);
				first++;
			}
			else {
				c.first->setPosition(higher_margin_x, higher_margin_y + second * highest_step);
				second++;
			}
			window->draw(*c.first);
			//all_sprites.push_back(std::make_pair(*c, true));
			i++;
		}
		first = 0; second = 0; i = 0;
		margin_x = size_x * 0.9375;
		higher_margin_x = 0.8275*size_x;
		for (auto& c : *e_team->get_e_team()) {
			c.first.setOrigin(c.first.getTexture()->getSize().x / 2, c.first.getTexture()->getSize().y / 1.05);
			if (i % 2 == 0) {
				c.first.setPosition(margin_x, margin_y + first * step);
				first++;
			}
			else {
				c.first.setPosition(higher_margin_x, higher_margin_y + second * highest_step);
				second++;
			}
			window->draw(c.first);
			//all_sprites.push_back(std::make_pair(c, true));
			i++;
		}
	}
	else {
		margin_x = 0.3*size_x;
		margin_y = 0.92*size_y;
		step = 0.06*size_x;
		highest_step = 0.02*size_y;
		for (auto c : *team->get_team()) {
			c.first->setOrigin(c.first->getTexture()->getSize().x / 2, c.first->getTexture()->getSize().y / 1.05);
			c.first->setPosition(margin_x + i * step, margin_y + i * highest_step);
			window->draw(*c.first);
			//all_sprites.push_bac.firstk(std::make_pair(*c, true));
			i++;
		}
		margin_x = 0.66*size_x;
		margin_y = 0.77*size_y;
		i = 0;
		for (auto& c : *e_team->get_e_team()) {
			c.first.setOrigin(c.first.getTexture()->getSize().x / 2, c.first.getTexture()->getSize().y / 1.05);
			c.first.setPosition(margin_x + i * step, margin_y + i * highest_step);
			window->draw(c.first);
			//all_sprites.push_back(std::make_pair(c, true));
			i++;
		}
	}
	window->display();
	bool escape = 0;
	//true==round our team, false==round enemy team
	bool round = true;
	draw_alive();
	while (team_active > 0 && enemies_active > 0 && window->isOpen() && !escape) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))escape = 1;//window->close();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				window->clear();
				window->draw(background);
				draw_alive();
				update_status();
				show_actual_stats();
				window->display();
				update_status();
			}
		}
		window->clear();
		window->draw(background);
		draw_alive();
		window->display();
		if (round) our_round();
		else {
			enemy_round();
			for (auto&x : *team->get_team()) {
				x.second->reduce_hp_by_effect();
				x.second->regenerate();
				x.second->verify_effect();
				x.second->reduce_effect();
				x.second->check_effect();
			}
			for (auto&x : *e_team->get_e_team()) {
				x.second->reduce_hp_by_effect();
				x.second->regenerate();
				x.second->verify_effect();
				x.second->reduce_effect();
				x.second->check_effect();
			}
		}
		check();
		round = !round;
	}
	//win
	if (!round) {
		window->clear();
		window->draw(background);
		Text text("You win!", window, ratio, sf::Vector2u((window->getSize().x*0.5-100)*ratio.x, (window->getSize().y*0.5-100)*ratio.y),50);
		text.draw();
		window->display();
		wait(5000);
		team->get_archer().second->add_exp(prize.archer_action * 20);
		while (team->get_archer().second->posible_promotion()) {
			std::list<Text*> archer_stats;
			std::list<Text*> new_archer_stats;
			archer_stats.push_back(new Text("Strength: "+std::to_string(team->get_archer().second->r_b_strenght()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + archer_stats.size() * 0.05*window->getSize().y)));
			archer_stats.push_back(new Text("Durability: "+std::to_string(team->get_archer().second->r_b_durability()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + archer_stats.size() * 0.05*window->getSize().y)));
			archer_stats.push_back(new Text("Dexterity: "+std::to_string(team->get_archer().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + archer_stats.size() * 0.05*window->getSize().y)));
			archer_stats.push_back(new Text("Inteligence: "+std::to_string(team->get_archer().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + archer_stats.size() * 0.05*window->getSize().y)));
			archer_stats.push_back(new Text("Hp: "+std::to_string(team->get_archer().second->r_m_health()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + archer_stats.size() * 0.05*window->getSize().y)));
			archer_stats.push_back(new Text("Stamina: "+std::to_string(team->get_archer().second->r_m_stamina()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + archer_stats.size() * 0.05*window->getSize().y)));
			team->get_archer().second->lev_up();
			new_archer_stats.push_back(new Text("Strength: " + std::to_string(team->get_archer().second->r_b_strenght()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_archer_stats.size() * 0.05*window->getSize().y)));
			new_archer_stats.push_back(new Text("Durability: " + std::to_string(team->get_archer().second->r_b_durability()),  window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_archer_stats.size() * 0.05*window->getSize().y)));
			new_archer_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_archer().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_archer_stats.size() * 0.05*window->getSize().y)));
			new_archer_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_archer().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_archer_stats.size() * 0.05*window->getSize().y)));
			new_archer_stats.push_back(new Text("Hp: " + std::to_string(team->get_archer().second->r_m_health()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_archer_stats.size() * 0.05*window->getSize().y)));
			new_archer_stats.push_back(new Text("Stamina: " + std::to_string(team->get_archer().second->r_m_stamina()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_archer_stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			Text text("Archer level up!", window, ratio, sf::Vector2u((window->getSize().x*0.5 - 100)*ratio.x, (window->getSize().y*0.5 - 100)*ratio.y), 50);
			text.draw();
			for (auto&x : archer_stats)x->draw();
			for (auto&x : new_archer_stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : archer_stats)delete x;
			for (auto&x : new_archer_stats)delete x;
		}
		team->get_fighter().second->add_exp(prize.fighter_action * 20);
		while (team->get_fighter().second->posible_promotion()) {
			std::list<Text*> fighter_stats;
			std::list<Text*> new_fighter_stats;
			fighter_stats.push_back(new Text("Strength: " + std::to_string(team->get_fighter().second->r_b_strenght()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + fighter_stats.size() * 0.05*window->getSize().y)));
			fighter_stats.push_back(new Text("Durability: " + std::to_string(team->get_fighter().second->r_b_durability()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + fighter_stats.size() * 0.05*window->getSize().y)));
			fighter_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_fighter().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + fighter_stats.size() * 0.05*window->getSize().y)));
			fighter_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_fighter().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + fighter_stats.size() * 0.05*window->getSize().y)));
			fighter_stats.push_back(new Text("Hp: " + std::to_string(team->get_fighter().second->r_m_health()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + fighter_stats.size() * 0.05*window->getSize().y)));
			fighter_stats.push_back(new Text("Stamina: " + std::to_string(team->get_fighter().second->r_m_stamina()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + fighter_stats.size() * 0.05*window->getSize().y)));
			team->get_fighter().second->lev_up();
			new_fighter_stats.push_back(new Text("Strength: " + std::to_string(team->get_fighter().second->r_b_strenght()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_fighter_stats.size() * 0.05*window->getSize().y)));
			new_fighter_stats.push_back(new Text("Durability: " + std::to_string(team->get_fighter().second->r_b_durability()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_fighter_stats.size() * 0.05*window->getSize().y)));
			new_fighter_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_fighter().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_fighter_stats.size() * 0.05*window->getSize().y)));
			new_fighter_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_fighter().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_fighter_stats.size() * 0.05*window->getSize().y)));
			new_fighter_stats.push_back(new Text("Hp: " + std::to_string(team->get_fighter().second->r_m_health()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_fighter_stats.size() * 0.05*window->getSize().y)));
			new_fighter_stats.push_back(new Text("Stamina: " + std::to_string(team->get_fighter().second->r_m_stamina()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_fighter_stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			Text text("Fighter level up!", window, ratio, sf::Vector2u((window->getSize().x*0.5 - 100)*ratio.x, (window->getSize().y*0.5 - 100)*ratio.y), 50);
			text.draw();
			for (auto&x : fighter_stats)x->draw();
			for (auto&x : new_fighter_stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : fighter_stats)delete x;
			for (auto&x : new_fighter_stats)delete x;
		}
		team->get_tank().second->add_exp(prize.tank_action * 20);
		while (team->get_tank().second->posible_promotion()) {
			std::list<Text*> tank_stats;
			std::list<Text*> new_tank_stats;
			tank_stats.push_back(new Text("Strength: " + std::to_string(team->get_tank().second->r_b_strenght()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + tank_stats.size() * 0.05*window->getSize().y)));
			tank_stats.push_back(new Text("Durability: " + std::to_string(team->get_tank().second->r_b_durability()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + tank_stats.size() * 0.05*window->getSize().y)));
			tank_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_tank().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + tank_stats.size() * 0.05*window->getSize().y)));
			tank_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_tank().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + tank_stats.size() * 0.05*window->getSize().y)));
			tank_stats.push_back(new Text("Hp: " + std::to_string(team->get_tank().second->r_m_health()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + tank_stats.size() * 0.05*window->getSize().y)));
			tank_stats.push_back(new Text("Stamina: " + std::to_string(team->get_tank().second->r_m_stamina()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + tank_stats.size() * 0.05*window->getSize().y)));
			team->get_tank().second->lev_up();
			new_tank_stats.push_back(new Text("Strength: " + std::to_string(team->get_tank().second->r_b_strenght()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_tank_stats.size() * 0.05*window->getSize().y)));
			new_tank_stats.push_back(new Text("Durability: " + std::to_string(team->get_tank().second->r_b_durability()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_tank_stats.size() * 0.05*window->getSize().y)));
			new_tank_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_tank().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_tank_stats.size() * 0.05*window->getSize().y)));
			new_tank_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_tank().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_tank_stats.size() * 0.05*window->getSize().y)));
			new_tank_stats.push_back(new Text("Hp: " + std::to_string(team->get_tank().second->r_m_health()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_tank_stats.size() * 0.05*window->getSize().y)));
			new_tank_stats.push_back(new Text("Stamina: " + std::to_string(team->get_tank().second->r_m_stamina()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_tank_stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			Text text("Tank level up!", window, ratio, sf::Vector2u((window->getSize().x*0.5 - 100)*ratio.x, (window->getSize().y*0.5 - 100)*ratio.y), 50);
			text.draw();
			for (auto&x : tank_stats)x->draw();
			for (auto&x : new_tank_stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : tank_stats)delete x;
			for (auto&x : new_tank_stats)delete x;
		}
		team->get_m_warrior().second->add_exp(prize.m_warrior_action * 20);
		while (team->get_m_warrior().second->posible_promotion()) {
			std::list<Text*> m_warrior_stats;
			std::list<Text*> new_m_warrior_stats;
			m_warrior_stats.push_back(new Text("Strength: " + std::to_string(team->get_m_warrior().second->r_b_strenght()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + m_warrior_stats.size() * 0.05*window->getSize().y)));
			m_warrior_stats.push_back(new Text("Durability: " + std::to_string(team->get_m_warrior().second->r_b_durability()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + m_warrior_stats.size() * 0.05*window->getSize().y)));
			m_warrior_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_m_warrior().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + m_warrior_stats.size() * 0.05*window->getSize().y)));
			m_warrior_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_m_warrior().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + m_warrior_stats.size() * 0.05*window->getSize().y)));
			m_warrior_stats.push_back(new Text("Hp: " + std::to_string(team->get_m_warrior().second->r_m_health()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + m_warrior_stats.size() * 0.05*window->getSize().y)));
			m_warrior_stats.push_back(new Text("Stamina: " + std::to_string(team->get_m_warrior().second->r_m_stamina()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + m_warrior_stats.size() * 0.05*window->getSize().y)));
			team->get_m_warrior().second->lev_up();
			new_m_warrior_stats.push_back(new Text("Strength: " + std::to_string(team->get_m_warrior().second->r_b_strenght()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_m_warrior_stats.size() * 0.05*window->getSize().y)));
			new_m_warrior_stats.push_back(new Text("Durability: " + std::to_string(team->get_m_warrior().second->r_b_durability()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_m_warrior_stats.size() * 0.05*window->getSize().y)));
			new_m_warrior_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_m_warrior().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_m_warrior_stats.size() * 0.05*window->getSize().y)));
			new_m_warrior_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_m_warrior().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_m_warrior_stats.size() * 0.05*window->getSize().y)));
			new_m_warrior_stats.push_back(new Text("Hp: " + std::to_string(team->get_m_warrior().second->r_m_health()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_m_warrior_stats.size() * 0.05*window->getSize().y)));
			new_m_warrior_stats.push_back(new Text("Stamina: " + std::to_string(team->get_m_warrior().second->r_m_stamina()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_m_warrior_stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			Text text("Mage Warrior level up!", window, ratio, sf::Vector2u((window->getSize().x*0.5 - 100)*ratio.x, (window->getSize().y*0.5 - 100)*ratio.y), 50);
			text.draw();
			for (auto&x : m_warrior_stats)x->draw();
			for (auto&x : new_m_warrior_stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : m_warrior_stats)delete x;
			for (auto&x : new_m_warrior_stats)delete x;
		}
		team->get_wizzard().second->add_exp(prize.wizzard_action * 20);
		while (team->get_wizzard().second->posible_promotion()) {
			std::list<Text*> wizzard_stats;
			std::list<Text*> new_wizzard_stats;
			wizzard_stats.push_back(new Text("Strength: " + std::to_string(team->get_wizzard().second->r_b_strenght()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + wizzard_stats.size() * 0.05*window->getSize().y)));
			wizzard_stats.push_back(new Text("Durability: " + std::to_string(team->get_wizzard().second->r_b_durability()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + wizzard_stats.size() * 0.05*window->getSize().y)));
			wizzard_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_wizzard().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + wizzard_stats.size() * 0.05*window->getSize().y)));
			wizzard_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_wizzard().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + wizzard_stats.size() * 0.05*window->getSize().y)));
			wizzard_stats.push_back(new Text("Hp: " + std::to_string(team->get_wizzard().second->r_m_health()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + wizzard_stats.size() * 0.05*window->getSize().y)));
			wizzard_stats.push_back(new Text("Stamina: " + std::to_string(team->get_wizzard().second->r_m_stamina()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + wizzard_stats.size() * 0.05*window->getSize().y)));
			team->get_wizzard().second->lev_up();
			new_wizzard_stats.push_back(new Text("Strength: " + std::to_string(team->get_wizzard().second->r_b_strenght()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_wizzard_stats.size() * 0.05*window->getSize().y)));
			new_wizzard_stats.push_back(new Text("Durability: " + std::to_string(team->get_wizzard().second->r_b_durability()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_wizzard_stats.size() * 0.05*window->getSize().y)));
			new_wizzard_stats.push_back(new Text("Dexterity: " + std::to_string(team->get_wizzard().second->r_b_dexterity()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_wizzard_stats.size() * 0.05*window->getSize().y)));
			new_wizzard_stats.push_back(new Text("Inteligence: " + std::to_string(team->get_wizzard().second->r_b_inteligence()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_wizzard_stats.size() * 0.05*window->getSize().y)));
			new_wizzard_stats.push_back(new Text("Hp: " + std::to_string(team->get_wizzard().second->r_m_health()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_wizzard_stats.size() * 0.05*window->getSize().y)));
			new_wizzard_stats.push_back(new Text("Stamina: " + std::to_string(team->get_wizzard().second->r_m_stamina()), window, ratio, sf::Vector2u(0.7*window->getSize().x, 0.03*window->getSize().y + new_wizzard_stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			Text text("Mage Warrior level up!", window, ratio, sf::Vector2u((window->getSize().x*0.5 - 100)*ratio.x, (window->getSize().y*0.5 - 100)*ratio.y), 50);
			text.draw();
			for (auto&x : wizzard_stats)x->draw();
			for (auto&x : new_wizzard_stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : wizzard_stats)delete x;
			for (auto&x : new_wizzard_stats)delete x;
		}
		for (auto&x : *team->get_team()) x.second->full_regenerate();
		prizee();
	}
	//end game
	else {
		sf::Texture losetexture;
		if (losetexture.loadFromFile("Fight/lose.jpg")) {
			sf::Sprite back;
			back.setTexture(losetexture);
			back.setScale(ratio.x, ratio.y);
			window->clear();
			window->draw(back);
			Text text("Game over!", window, ratio, sf::Vector2u((losetexture.getSize().x / 2 - 100)*ratio.x, (losetexture.getSize().y / 2 - 50)*ratio.y),50);
			text.draw();
			window->display();
			for (auto&x : *team->get_team()) x.second->full_regenerate();
			//wait(5000);
			//window->close();
		}
		else {
			window->close();
			std::cout << "error with background loading /n you lose the battle, game over" << std::endl;
			exit(0);
		}
	}
}
void Battle::prizee() {
	short weapon_type = std::rand() % 5;
	short suit_type = std::rand() % 6;
	if (weapon_type == 0) {
		Bow * bow = rand_bow(prize_quality);
		Bow * better_bow = compare_bow(static_cast<Bow*>(team->get_archer().second->r_weapon()), bow);
		if (bow == better_bow) {
			team->get_archer().second->s_weapon(bow);
			std::vector<Text*> stats;
			string weight;
			if (team->get_archer().second->r_weapon()->r_weight() == Weight::light) weight = "light";
			else if (team->get_archer().second->r_weapon()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text("Archer found new bow!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Damage: " + std::to_string(team->get_archer().second->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete bow;
		}
	}
	else if (weapon_type == 1) {
		m_Bow * bow = rand_m_bow(prize_quality);
		Bow * better_bow = compare_bow(static_cast<Bow*>(team->get_archer().second->r_weapon()), bow);
		if (bow ==better_bow) {
			team->get_archer().second->s_weapon(bow);
			std::vector<Text*> stats;
			string weight;
			if (team->get_archer().second->r_weapon()->r_weight() == Weight::light) weight = "light";
			else if (team->get_archer().second->r_weapon()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy"; 
			string effect;
			if (team->get_archer().second->r_weapon()->r_effect() == Effect::bleeding)effect = "bleeding";
			else if (team->get_archer().second->r_weapon()->r_effect() == Effect::toxic)effect = "toxic";
			else effect = "stunning";
			stats.push_back(new Text("Archer found new bow!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Damage: " + std::to_string(team->get_archer().second->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Magic Damage: " + std::to_string(team->get_archer().second->r_weapon()->r_m_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Effect: " + effect, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete bow;
		}
	}
	else if (weapon_type == 2) {
		m_Sword* sword = rand_m_sword(prize_quality);
		Party_member * weakest_sword = nullptr;
		Sword * fighter_sword = static_cast<Sword*>(team->get_fighter().second->r_weapon());
		Sword * tank_sword = static_cast<Sword*>(team->get_tank().second->r_weapon());
		Sword * mage_warrior_sword = static_cast<Sword*>(team->get_m_warrior().second->r_weapon());
		if (fighter_sword == compare_sword_worst(fighter_sword, tank_sword) && fighter_sword == compare_sword_worst(fighter_sword, mage_warrior_sword)) {
			if (sword == compare_sword(sword, fighter_sword)) {
				team->get_fighter().second->s_weapon(sword);
				weakest_sword = team->get_fighter().second.get();
				std::vector<Text*> stats;
				string weight;
				if (weakest_sword->r_weapon()->r_weight() == Weight::light) weight = "light";
				else if (weakest_sword->r_weapon()->r_weight() == Weight::medium)weight = "medium";
				else weight = "heavy";
				string effect;
				if (weakest_sword->r_weapon()->r_effect() == Effect::bleeding)effect = "bleeding";
				else if (weakest_sword->r_weapon()->r_effect() == Effect::toxic)effect = "toxic";
				else effect = "stunning";
				stats.push_back(new Text("Fighter found new sword!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Damage: " + std::to_string(weakest_sword->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Magic Damage: " + std::to_string(weakest_sword->r_weapon()->r_m_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Effect: " + effect, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				window->clear();
				window->draw(background);
				for (auto&x : stats)x->draw();
				window->display();
				wait(5000);
				for (auto&x : stats)delete x;
			}
			//nobody found new weapon
			else {
				Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
				window->clear();
				window->draw(background);
				nb.draw();
				window->display();
				wait(5000);
				delete sword;
			}
		}
		else if (tank_sword == compare_sword_worst(fighter_sword, tank_sword) && tank_sword == compare_sword_worst(tank_sword, mage_warrior_sword)) {
			if (sword == compare_sword(sword, tank_sword)) {
				team->get_tank().second->s_weapon(sword);
				weakest_sword = team->get_tank().second.get();
				std::vector<Text*> stats;
				string weight;
				if (weakest_sword->r_weapon()->r_weight() == Weight::light) weight = "light";
				else if (weakest_sword->r_weapon()->r_weight() == Weight::medium)weight = "medium";
				else weight = "heavy";
				string effect;
				if (weakest_sword->r_weapon()->r_effect() == Effect::bleeding)effect = "bleeding";
				else if (weakest_sword->r_weapon()->r_effect() == Effect::toxic)effect = "toxic";
				else effect = "stunning";
				stats.push_back(new Text("Fighter found new sword!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Damage: " + std::to_string(weakest_sword->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Magic Damage: " + std::to_string(weakest_sword->r_weapon()->r_m_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Effect: " + effect, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				window->clear();
				window->draw(background);
				for (auto&x : stats)x->draw();
				window->display();
				wait(5000);
				for (auto&x : stats)delete x;
			}
			//nobody found new weapon
			else {
				Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
				window->clear();
				window->draw(background);
				nb.draw();
				window->display();
				wait(5000);
				delete sword;
			}
		}
		else if (mage_warrior_sword == compare_sword_worst(mage_warrior_sword, tank_sword) && mage_warrior_sword == compare_sword_worst(mage_warrior_sword, fighter_sword)) {
			if (sword == compare_sword(sword, mage_warrior_sword)) {
				team->get_m_warrior().second->s_weapon(sword);
				weakest_sword = team->get_m_warrior().second.get();
				std::vector<Text*> stats;
				string weight;
				if (weakest_sword->r_weapon()->r_weight() == Weight::light) weight = "light";
				else if (weakest_sword->r_weapon()->r_weight() == Weight::medium)weight = "medium";
				else weight = "heavy";
				string effect;
				if (weakest_sword->r_weapon()->r_effect() == Effect::bleeding)effect = "bleeding";
				else if (weakest_sword->r_weapon()->r_effect() == Effect::toxic)effect = "toxic";
				else effect = "stunning";
				stats.push_back(new Text("Mage warrior found new sword!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Damage: " + std::to_string(weakest_sword->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Magic Damage: " + std::to_string(weakest_sword->r_weapon()->r_m_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				stats.push_back(new Text("Effect: " + effect, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
				window->clear();
				window->draw(background);
				for (auto&x : stats)x->draw();
				window->display();
				wait(5000);
				for (auto&x : stats)delete x;
			}
			//nobody found new weapon
			else {
				Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
				window->clear();
				window->draw(background);
				nb.draw();
				window->display();
				wait(5000);
				delete sword;
			}
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete sword;
		}
	}
	else if (weapon_type == 3) {
		Staff * staff = rand_staff(prize_quality);
		Staff * better_staff = comapre_staff(staff, static_cast<Staff*>(team->get_wizzard().second->r_weapon()));
		if (staff == better_staff) {
			team->get_wizzard().second->s_weapon(staff);
			std::vector<Text*> stats;
			string weight;
			if (team->get_wizzard().second->r_weapon()->r_weight() == Weight::light) weight = "light";
			else if (team->get_wizzard().second->r_weapon()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			string effect;
			if (team->get_wizzard().second->r_weapon()->r_effect() == Effect::bleeding)effect = "bleeding";
			else if (team->get_wizzard().second->r_weapon()->r_effect() == Effect::toxic)effect = "toxic";
			else effect = "stunning";
			stats.push_back(new Text("Wizzard found new staff!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Damage: " + std::to_string(team->get_wizzard().second->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Magic Damage: " + std::to_string(team->get_wizzard().second->r_weapon()->r_m_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Effect: " + effect, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete staff;
		}
	}
	else {
	m_Sword* sword = rand_m_sword(prize_quality);
	Party_member * weakest_sword = nullptr;
	Sword * fighter_sword = static_cast<Sword*>(team->get_fighter().second->r_weapon());
	Sword * tank_sword = static_cast<Sword*>(team->get_tank().second->r_weapon());
	Sword * mage_warrior_sword = static_cast<Sword*>(team->get_m_warrior().second->r_weapon());
	if (fighter_sword == compare_sword_worst(fighter_sword, tank_sword) && fighter_sword == compare_sword_worst(fighter_sword, mage_warrior_sword)) {
		if (sword == compare_sword(sword, fighter_sword)) {
			team->get_fighter().second->s_weapon(sword);
			weakest_sword = team->get_fighter().second.get();
			std::vector<Text*> stats;
			string weight;
			if (weakest_sword->r_weapon()->r_weight() == Weight::light) weight = "light";
			else if (weakest_sword->r_weapon()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text("Fighter found new sword!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Damage: " + std::to_string(weakest_sword->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete sword;
		}
	}
	else if (tank_sword == compare_sword_worst(fighter_sword, tank_sword) && tank_sword == compare_sword_worst(tank_sword, mage_warrior_sword)) {
		if (sword == compare_sword(sword, tank_sword)) {
			team->get_tank().second->s_weapon(sword);
			weakest_sword = team->get_tank().second.get();
			std::vector<Text*> stats;
			string weight;
			if (weakest_sword->r_weapon()->r_weight() == Weight::light) weight = "light";
			else if (weakest_sword->r_weapon()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text("Fighter found new sword!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Damage: " + std::to_string(weakest_sword->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete sword;
		}
	}
	else if (mage_warrior_sword == compare_sword_worst(mage_warrior_sword, tank_sword) && mage_warrior_sword == compare_sword_worst(mage_warrior_sword, fighter_sword)) {
		if (sword == compare_sword(sword, mage_warrior_sword)) {
			team->get_m_warrior().second->s_weapon(sword);
			weakest_sword = team->get_m_warrior().second.get();
			std::vector<Text*> stats;
			string weight;
			if (weakest_sword->r_weapon()->r_weight() == Weight::light) weight = "light";
			else if (weakest_sword->r_weapon()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text("Mage warrior found new sword!", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Damage: " + std::to_string(weakest_sword->r_weapon()->r_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		//nobody found new weapon
		else {
			Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete sword;
		}
	}
	//nobody found new weapon
	else {
		Text nb("Nobody found new weapon :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
		window->clear();
		window->draw(background);
		nb.draw();
		window->display();
		wait(5000);
		delete sword;
	}
	}
	if(suit_type==0){
		Armor * armor = rand_armor(prize_quality);
		Party_member* worst_armor = nullptr;
		int quality[5];
		int iterator = 0;
		int min = INT_MAX;
		for (auto&x : *team->get_team()) {
			quality[iterator] = x.second->r_armor()->get_quality();
			if (quality[iterator] < min) {
				min = quality[iterator];
				worst_armor = x.second.get();
			}
			iterator++;
		}
		if (armor == compare_armor(armor, worst_armor->r_armor())) {
			worst_armor->s_armor(armor);
			std::vector<Text*> stats;
			string temp = " found new armor!";
			string weight;
			if (worst_armor->r_armor()->r_weight() == Weight::light) weight = "light";
			else if (worst_armor->r_armor()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text(typeid(*worst_armor).name()+temp, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Defence: " + std::to_string(worst_armor->r_armor()->r_res_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		else {
			Text nb("Nobody found new armor :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete armor;
		}
	}
	else if(suit_type==1){
		Helmet * armor = rand_helmet(prize_quality);
		Party_member* worst_armor = nullptr;
		int quality[5];
		int iterator = 0;
		int min = INT_MAX;
		for (auto&x : *team->get_team()) {
			quality[iterator] = x.second->r_helmet()->get_quality();
			if (quality[iterator] < min) {
				min = quality[iterator];
				worst_armor = x.second.get();
			}
			iterator++;
		}
		if (armor == compare_helmet(armor, worst_armor->r_helmet())) {
			worst_armor->s_helmet(armor);
			std::vector<Text*> stats;
			string temp = " found new helmet!";
			string weight;
			if (worst_armor->r_helmet()->r_weight() == Weight::light) weight = "light";
			else if (worst_armor->r_helmet()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text(typeid(*worst_armor).name() + temp, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Defence: " + std::to_string(worst_armor->r_helmet()->r_res_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		else {
			Text nb("Nobody found new helmet:C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete armor;
		}
	}
	else if(suit_type==2){
		m_Armor * armor = rand_m_armor(prize_quality);
		Party_member* worst_armor = nullptr;
		int quality[5];
		int iterator = 0;
		int min = INT_MAX;
		for (auto&x : *team->get_team()) {
			quality[iterator] = x.second->r_armor()->get_quality();
			if (quality[iterator] < min) {
				min = quality[iterator];
				worst_armor = x.second.get();
			}
			iterator++;
		}
		if (armor == compare_armor(armor, worst_armor->r_armor())) {
			worst_armor->s_armor(armor);
			std::vector<Text*> stats;
			string temp = " found new armor!";
			string weight;
			if (worst_armor->r_armor()->r_weight() == Weight::light) weight = "light";
			else if (worst_armor->r_armor()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text(typeid(*worst_armor).name() + temp, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Defence: " + std::to_string(worst_armor->r_armor()->r_res_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Toxic defence: " + std::to_string(worst_armor->r_armor()->r_r_m_damage(Effect::toxic)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Stunning defence: " + std::to_string(worst_armor->r_armor()->r_r_m_damage(Effect::stunning)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Bleeding defence: " + std::to_string(worst_armor->r_armor()->r_r_m_damage(Effect::bleeding)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		else {
			Text nb("Nobody found new armor :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete armor;
		}
	}
	else if(suit_type==3){
		m_Helmet * armor = rand_m_helmet(prize_quality);
		Party_member* worst_armor = nullptr;
		int quality[5];
		int iterator = 0;
		int min = INT_MAX;
		for (auto&x : *team->get_team()) {
			quality[iterator] = x.second->r_helmet()->get_quality();
			if (quality[iterator] < min) {
				min = quality[iterator];
				worst_armor = x.second.get();
			}
			iterator++;
		}
		if (armor == compare_helmet(armor, worst_armor->r_helmet())) {
			worst_armor->s_helmet(armor);
			std::vector<Text*> stats;
			string temp = " found new helmet!";
			string weight;
			if (worst_armor->r_helmet()->r_weight() == Weight::light) weight = "light";
			else if (worst_armor->r_helmet()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text(typeid(*worst_armor).name() + temp, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Defence: " + std::to_string(worst_armor->r_helmet()->r_res_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Toxic defence: " + std::to_string(worst_armor->r_helmet()->r_r_m_damage(Effect::toxic)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Stunning defence: " + std::to_string(worst_armor->r_helmet()->r_r_m_damage(Effect::stunning)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Bleeding defence: " + std::to_string(worst_armor->r_helmet()->r_r_m_damage(Effect::bleeding)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		else {
			Text nb("Nobody found new helmet:C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete armor;
		}
	}
	else if(suit_type==4){
		m_Shield * armor = rand_m_shield(prize_quality);
		Party_member* worst_armor = nullptr;
		int quality[5];
		int iterator = 0;
		int min = INT_MAX;
		for (auto&x : *team->get_team()) {
			quality[iterator] = x.second->r_shield()->get_quality();
			if (quality[iterator] < min) {
				min = quality[iterator];
				worst_armor = x.second.get();
			}
			iterator++;
		}
		if (armor == compare_shield(armor, worst_armor->r_shield())) {
			worst_armor->s_shield(armor);
			std::vector<Text*> stats;
			string temp = " found new shield!";
			string weight;
			if (worst_armor->r_shield()->r_weight() == Weight::light) weight = "light";
			else if (worst_armor->r_shield()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text(typeid(*worst_armor).name() + temp, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Defence: " + std::to_string(worst_armor->r_shield()->r_res_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Toxic defence: " + std::to_string(worst_armor->r_shield()->r_r_m_damage(Effect::toxic)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Stunning defence: " + std::to_string(worst_armor->r_shield()->r_r_m_damage(Effect::stunning)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Bleeding defence: " + std::to_string(worst_armor->r_shield()->r_r_m_damage(Effect::bleeding)), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		else {
			Text nb("Nobody found new shield :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete armor;
		}
	}
	else {
		Shield * armor = rand_shield(prize_quality);
		Party_member* worst_armor = nullptr;
		int quality[5];
		int iterator = 0;
		int min = INT_MAX;
		for (auto&x : *team->get_team()) {
			quality[iterator] = x.second->r_shield()->get_quality();
			if (quality[iterator] < min) {
				min = quality[iterator];
				worst_armor = x.second.get();
			}
			iterator++;
		}
		if (armor == compare_shield(armor, worst_armor->r_shield())) {
			worst_armor->s_shield(armor);
			std::vector<Text*> stats;
			string temp = " found new shield!";
			string weight;
			if (worst_armor->r_shield()->r_weight() == Weight::light) weight = "light";
			else if (worst_armor->r_shield()->r_weight() == Weight::medium)weight = "medium";
			else weight = "heavy";
			stats.push_back(new Text(typeid(*worst_armor).name() + temp, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Defence: " + std::to_string(worst_armor->r_shield()->r_res_damage()), window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			stats.push_back(new Text("Weight: " + weight, window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y + stats.size() * 0.05*window->getSize().y)));
			window->clear();
			window->draw(background);
			for (auto&x : stats)x->draw();
			window->display();
			wait(5000);
			for (auto&x : stats)delete x;
		}
		else {
			Text nb("Nobody found new shield :C ", window, ratio, sf::Vector2u(0.05*window->getSize().x, 0.03*window->getSize().y *window->getSize().y));
			window->clear();
			window->draw(background);
			nb.draw();
			window->display();
			wait(5000);
			delete armor;
		}
	}
}
void Battle::AI() {
	tactic all_tactic[4]{ 0,0,0,1 };
	AI_result all_result[4];
	all_result[0] = treatment_tactic();
	all_result[1] = debuff_tactic();
	all_result[2] = buff_tactic();
	all_result[3] = dmg_tactic();
	for (int i = 0, max_value = -128; i < 4; i++) {
		if (all_result[i].strength > max_value) {
			max_value = all_result[i].strength;
			//max_index = i;
			result = all_result[i];
		}
	}
}
AI_result Battle::treatment_tactic() {
	bool is_wizzard = false;
	Being* wizzard = nullptr;
	Being* target = nullptr;
	double * health = new double[enemies];
	int iterator = 0;
	double min = 1.1;
	size_t index = -1;
	for (auto &x : *e_team->get_e_team()) {
		if (x.second->iam_alive()) {
			health[iterator] = (double)(x.second->r_health()) / (double)(x.second->r_m_health());
			if (health[iterator] < min) {
				index = iterator;
				min = health[iterator];
				target = x.second;
			}
		}
		else health[iterator] = 1.1;
		if (is_type<eWizzard>(x.second) && x.second->iam_alive()&&!x.second->iam_stuned() && x.second->r_stamina() > 45) {
			is_wizzard = true;
			if (wizzard == nullptr)wizzard = x.second;
			else if (x.second->r_lv() > wizzard->r_lv() ) wizzard = x.second;
		}
		iterator++;
	}
	if (is_wizzard&&target != nullptr) {
		/*for (int i = 0; i < enemies; i++) {
		if (health[i] < min&&health[i]>0.0) {
		min = health[i];
		index = i;
		target = e_team->get_e_team()->operator[](i).second;
		}
		}*/
		/*if (target == nullptr&&health[index] < 0.7) {
		target = e_team->get_e_team()->operator[](index).second;
		delete[]health;
		if (wizzard->r_stamina() > second_wizzard->r_stamina()&&wizzard->r_stamina()>=45) return AI_result(wizzard, target, 2, 2);
		else if(wizzard->r_stamina() < second_wizzard->r_stamina() && second_wizzard->r_stamina() >= 45) return AI_result(second_wizzard, target, 2, 2);
		else return AI_result(nullptr, nullptr, 1, -128);
		}
		else {
		delete[]health;
		if (wizzard->r_stamina() > second_wizzard->r_stamina() && wizzard->r_stamina() >= 45) return AI_result(wizzard, target, 2, (1.0/min)+5);
		else if(wizzard->r_stamina() < second_wizzard->r_stamina() && second_wizzard->r_stamina() >= 45) return AI_result(second_wizzard, target, 2, (1.0 / min) + 5);
		else return AI_result(nullptr, nullptr, 1, -128);
		}*/
		if (health[index] < 0.3) {
			delete[]health;
			return AI_result(wizzard, target, 2, (1.0 / min - 0.1) + 5);
		}
		else if (health[index] < 0.6) {
			delete[]health;
			return AI_result(wizzard, target, 2, (1.0 / min - 0.1) + 2);
		}
		else {
			delete[]health;
			return AI_result(nullptr, nullptr, 1, -128);
		}
	}
	else {
		delete[]health;
		return AI_result(nullptr, nullptr, 1, -128);
	}
}
AI_result Battle::debuff_tactic() {
	bool is_wizzard = false;
	Being * wizzard = nullptr;
	bool is_mage_warrior = false;
	Being * mage_warrior = nullptr;
	bool is_archer = false;
	Being * archer = nullptr;
	bool is_fighter = false;
	Being * fighter = nullptr;
	bool is_ghost = false;
	Being * ghost = nullptr;
	bool is_spider = false;
	Being* spider = nullptr;
	bool is_wolf = false;
	Being* wolf = nullptr;
	bool is_werewolf = false;
	Being* werewolf = nullptr;
	Being * target = nullptr;
	for (auto &x : *e_team->get_e_team()) {
		if (is_type<eWizzard>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			if (wizzard == nullptr) { wizzard = x.second; is_wizzard = true; }
			else if (x.second->r_lv() > wizzard->r_lv() && x.second->r_stamina() > 40)wizzard = x.second;
		}
		else if (is_type<eMage_warrior>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			if (mage_warrior == nullptr) { mage_warrior = x.second; is_mage_warrior = true;}
			else if (x.second->r_lv() > mage_warrior->r_lv() && x.second->r_stamina() > 40)mage_warrior = x.second;
		}
		else if (is_type<eFighter>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_fighter = true;
			if (fighter == nullptr)fighter = x.second;
			else if (x.second->r_lv() > fighter->r_lv() && x.second->r_stamina() > 40)fighter = x.second;
		}
		else if (is_type<eArcher>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_archer = true;
			if (archer == nullptr)archer = x.second;
			else if (x.second->r_lv() > archer->r_lv() && x.second->r_stamina() > 35)archer = x.second;
		}
		else if(is_type<Ghost>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()){ghost = x.second; is_ghost = true; }
		else if(is_type<Spider>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()){ spider = x.second; is_spider = true; }
		else if(is_type<Wolf>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()){
			if (wolf == nullptr) { wolf = x.second; is_wolf = true; }
			else if (x.second->r_lv() > wolf->r_lv() && x.second->r_stamina() > 40)wolf = x.second;
		}
		else if(is_type<Werewolf>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()){ werewolf = x.second; is_werewolf = true; }
	}
	if (is_wizzard&&wizzard->r_stamina() >= 40) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_full_weakened() && x.second->iam_alive()) {
				target = x.second.get();
				return AI_result(wizzard, target, 3, 6);
			}
		}
	}
	else if (is_werewolf&&werewolf->r_stamina() >= 40) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_stuned() && x.second->iam_alive())return AI_result(werewolf, x.second.get(), 2, 7);
		}
	}
	else if (is_ghost&&ghost->r_stamina() >= 40) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_bleeding() && x.second->iam_alive())return AI_result(ghost, x.second.get(), 2, 5);
			if (!x.second->iam_stuned() && x.second->iam_alive())return AI_result(ghost, x.second.get(), 3, 8);
		}
	}
	else if (is_spider&&spider->r_stamina() >= 40) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_poisoned() && x.second->iam_alive())return AI_result(spider, x.second.get(), 2, 6);
		}
	}
	else if (is_mage_warrior&&mage_warrior->r_stamina() >= 40) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_bleeding() && x.second->iam_alive()) {
				target = x.second.get();
				return AI_result(mage_warrior, target, 3, 6);
			}
		}
	}
	else if (is_archer&&archer->r_stamina() >= 40) {
		size_t not_stuned = -1;
		size_t iterator = 0;
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_stuned() && x.second->iam_alive())not_stuned = iterator;
			if (!x.second->iam_poisoned() && x.second->iam_alive()) {
				target = x.second.get();
				return AI_result(archer, target, 1, 5);
			}
			iterator++;
		}
		if (not_stuned >= 0)return AI_result(archer, team->get_team()->operator[](not_stuned).second.get(), 3, 5
		);
	}
	else if (is_fighter&&fighter->r_stamina() >= 35) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_stuned() && x.second->iam_alive())return AI_result(fighter, x.second.get(), 2, 5);
		}
	}
	else if (is_wolf&&wolf->r_stamina() >=40) {
		for (auto &x : *team->get_team()) {
			if (!x.second->iam_bleeding() && x.second->iam_alive())return AI_result(wolf, x.second.get(), 2, 6);
		}
	}
	else return AI_result(nullptr, nullptr, 1, -128);
}
AI_result Battle::buff_tactic() {
	bool is_tank = false;
	bool is_fighter = false;
	bool is_orc = false;
	bool is_spider = false;
	bool is_werewolf = false;
	bool is_wolf = false;
	Being * target = nullptr;
	Being * fighter = nullptr;
	Being * tank = nullptr;
	Being *orc = nullptr;
	Being*spider = nullptr;
	Being * werewolf = nullptr;
	Being * wolf = nullptr;
	bool remove_debuff = false;
	size_t index_debuff_enemies = -1;
	size_t iterator = 0;
	for (auto &x : *e_team->get_e_team()) {
		if (x.second->iam_weakened() && x.second->iam_alive() && !x.second->iam_stuned()) {
			index_debuff_enemies = iterator;
			remove_debuff = true;
		}
		if (is_type<eFighter>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_fighter = true;
			if (fighter == nullptr)fighter = x.second;
			else { if (x.second->r_stamina() > fighter->r_stamina())fighter = x.second; }
		}
		else if (is_type<Tank>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_tank = true;
			if (tank == nullptr)tank = x.second;
			else { if (x.second->r_stamina() > tank->r_stamina())tank = x.second; }
		}
		else if (is_type<Orc>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_orc = true;
			orc = x.second;
		}
		else if (is_type<Spider>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_spider = true;
			spider=x.second;
		}
		else if (is_type<Werewolf>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_werewolf = true;
			werewolf = x.second;
		}
		else if (is_type<Wolf>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_wolf = true;
			if (tank == nullptr)wolf = x.second;
			else { if (x.second->r_stamina() > wolf->r_stamina())wolf = x.second; }
		}
		iterator++;
	}
	if (remove_debuff&&is_tank&&tank->r_stamina() >= 40) {
		return AI_result(tank, e_team->get_e_team()->operator[](index_debuff_enemies).second, 3, 2);
	}
	else if (remove_debuff&&is_tank&&tank->r_stamina() >= 40 && target->r_health()<0.4*target->r_m_health()) {
		return AI_result(tank, e_team->get_e_team()->operator[](index_debuff_enemies).second, 3, 5);
	}
	else if (is_fighter&&fighter->r_stamina() >= 40 && fighter->not_boosted()) {
		return AI_result(fighter, fighter, 3, 4);
	}
	else if (is_tank&&tank->r_stamina()>=45) {
		if (is_fighter&&fighter->not_boosted())return AI_result(tank, fighter, 2, 3);
		for (auto&x : *e_team->get_e_team()) {
			if (is_type<eArcher>(x.second) && x.second->iam_alive()) {
				//is_archer = true;
				if (target == nullptr && !x.second->is_full_boosted()) target = x.second;
				else if ((x.second->r_health() > 0.3*x.second->r_m_health() && x.second->r_health()>target->r_health()) && x.second->r_stamina() > 60)target = x.second;
			}
			if (is_type<eMage_warrior>(x.second) && x.second->iam_alive()) {
				//is_mage_warrior = true;
				if (target == nullptr && !x.second->is_full_boosted()) target = x.second;
				else if ((x.second->r_health() > 0.3*x.second->r_m_health() && x.second->r_health() > target->r_health()) && x.second->r_stamina() > 60)target = x.second;
			}
			if (is_type<eWizzard>(x.second) && x.second->iam_alive()) {
				return AI_result(tank, x.second, 2, 6);
			}
		}
		if (target != nullptr)return AI_result(tank, target, 2, 5);
	}
	else if (is_orc&&orc->r_stamina()>=45) {
		if (is_fighter&&fighter->not_boosted())return AI_result(orc, fighter, 3, 5);
		for (auto&x : *e_team->get_e_team()) {
			if (is_type<eArcher>(x.second) && x.second->iam_alive()&&x.second->not_boosted()) {
				//is_archer = true;
				return AI_result(orc, x.second, 3, 4);
			}
		}
	}
	else if (is_orc&&orc->r_stamina()>40&&orc->not_boosted()) {
		return AI_result(orc, orc, 1, 7);
	}
	else if (is_werewolf&&werewolf->r_stamina()>40&&werewolf->not_boosted()) {
		return AI_result(werewolf, werewolf, 3, 7);
	}
	else if (is_spider&&spider->r_stamina()>40&&spider->not_boosted()) {
		return AI_result(spider,spider, 1, 7);
	}
	else if (is_wolf&&wolf->r_stamina()>40&&wolf->not_boosted()) {
		return AI_result(wolf,wolf, 3,6);
	}
	else return AI_result(nullptr, nullptr, 1, -128);
}
AI_result Battle::dmg_tactic() {
	AI_result result;
	Being * archer = nullptr;
	bool is_archer = false;
	Being * mage_warrior = nullptr;
	bool is_mage = false;
	Being * tank = nullptr;
	bool is_tank = false;
	Being * fighter = nullptr;
	bool is_fighter = false;
	Being * wizzard = nullptr;
	bool is_wizzard = false;
	Being * werewolf = nullptr;
	bool is_werewolf = false;
	Being * ghost = nullptr;
	bool is_ghost = false;
	Being * orc = nullptr;
	bool is_orc = false;
	Being * spider = nullptr;
	bool is_spider = false;
	Being * wolf = nullptr;
	bool is_wolf = false;
	result.target = nullptr;
	for (auto &x : *e_team->get_e_team()) {
		if (is_type<eArcher>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_archer = true;
			if (archer == nullptr)archer = x.second;
			else if ((x.second->r_lv() > archer->r_lv() && x.second->r_stamina() > 35) || x.second->r_stamina() > archer->r_stamina()) tank = x.second;
		}
		else if (is_type<eTank>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_tank = true;
			if (tank == nullptr)tank = x.second;
			else if ((x.second->r_lv() > tank->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > tank->r_stamina()) tank = x.second;
		}
		else if (is_type<eFighter>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_fighter = true;
			if (fighter == nullptr)fighter = x.second;
			else if ((x.second->r_lv() > fighter->r_lv() && x.second->r_stamina() > 35) || x.second->r_stamina() > fighter->r_stamina()) fighter = x.second;
		}
		else if (is_type<eWizzard>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_wizzard = true;
			if (wizzard == nullptr)wizzard = x.second;
			else if ((x.second->r_lv() > wizzard->r_lv() && x.second->r_stamina() > 35) || x.second->r_stamina() > wizzard->r_stamina()) wizzard = x.second;
		}
		else if (is_type<eMage_warrior>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_mage = true;
			if (mage_warrior == nullptr)mage_warrior = x.second;
			else if ((x.second->r_lv() > mage_warrior->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > mage_warrior->r_stamina()) mage_warrior = x.second;
		}
		else if (is_type<Ghost>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_ghost = true;
			if (ghost == nullptr)ghost = x.second;
			else if ((x.second->r_lv() > ghost->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > ghost->r_stamina()) ghost = x.second;
		}
		else if (is_type<Orc>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_orc = true;
			if (orc == nullptr)orc = x.second;
			else if ((x.second->r_lv() > orc->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > orc->r_stamina()) orc = x.second;
		}
		else if (is_type<Spider>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_spider = true;
			if (spider == nullptr)spider = x.second;
			else if ((x.second->r_lv() > spider->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > spider->r_stamina()) spider = x.second;
		}
		else if (is_type<Werewolf>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_werewolf = true;
			if (werewolf == nullptr)werewolf = x.second;
			else if ((x.second->r_lv() > werewolf->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > werewolf->r_stamina()) werewolf = x.second;
		}
		else if (is_type<Wolf>(x.second) && x.second->iam_alive() && !x.second->iam_stuned()) {
			is_wolf = true;
			if (wolf == nullptr)wolf = x.second;
			else if ((x.second->r_lv() > wolf->r_lv() && x.second->r_stamina() > 30) || x.second->r_stamina() > wolf->r_stamina()) wolf = x.second;
		}
	}
	for (auto&x : *team->get_team()) {
		if (x.second->r_health() < 0.35*x.second->r_m_health() && x.second->iam_alive()) {
			if (is_archer&&archer->r_stamina() >= 35) {
				result.being = archer;
				result.target = x.second.get();
				result.skill = 2;
				result.strength = 7;
				return result;
			}
			else if (is_mage&&mage_warrior->r_stamina() >= 30) {
				result.being = mage_warrior;
				result.target = x.second.get();
				result.skill = 1;
				result.strength = 7;
				return result;
			}
			else if (is_fighter&&fighter->r_stamina() >= 35) {
				result.being = fighter;
				result.target = x.second.get();
				result.skill = 2;
				result.strength = 7;
				return result;
			}
			else if (is_fighter&&fighter->r_stamina() >= 30) {
				result.being = fighter;
				result.target = x.second.get();
				result.skill = 1;
				result.strength = 7;
				return result;
			}
			else if (is_wizzard&&wizzard->r_stamina() >= 30) {
				result.being = wizzard;
				result.target = x.second.get();
				result.skill = 1;
				result.strength = 7;
				return result;
			}
			else if (is_tank&&tank->r_stamina() >= 30) {
				result.being = tank;
				result.target = x.second.get();
				result.skill = 1;
				result.strength = 7;
				return result;
			}
		}
	}
	//0 -select min hp, 1-select wizzard, 2 - select stunned
	tactic choice = std::rand() % 3;
	if (choice == 0) {
		Health min_hp = INT16_MAX;
		for (auto&x : *team->get_team())
			if (x.second->r_health() < min_hp&&x.second->iam_alive()) {
				min_hp = x.second->r_health();
				result.target = x.second.get();
			}
		if (is_ghost&&ghost->r_stamina() >= 30 && ghost->int_is_boosted()) {
			result.being = ghost;
			result.skill = 1;
			result.strength = 8;
			return result;
		}
		else if (is_ghost&&ghost->r_stamina() >= 30) {
			result.being = ghost;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_orc&&orc->r_stamina() >= 35 && orc->str_is_boosted()) {
			result.being = orc;
			result.skill = 2;
			result.strength = 8;
			return result;
		}
		else if (is_orc&&orc->r_stamina() >= 35) {
			result.being = orc;
			result.skill = 2;
			result.strength = 5;
			return result;
		}
		else if (is_spider&&spider->r_stamina() >= 35 & spider->dex_is_boosted()) {
			result.being = spider;
			result.skill = 3;
			result.strength = 8;
			return result;
		}
		else if (is_spider&&spider->r_stamina() >= 35) {
			result.being = spider;
			result.skill = 3;
			result.strength = 5;
			return result;
		}
		else if (is_werewolf&&werewolf->r_stamina() >= 40 && werewolf->str_is_boosted()) {
			result.being = werewolf;
			result.skill = 2;
			result.strength = 9;
			return result;
		}
		else if (is_werewolf&&werewolf->r_stamina() >= 35 && werewolf->str_is_boosted()) {
			result.being = werewolf;
			result.skill = 1;
			result.strength = 8;
			return result;
		}
		else if (is_werewolf&&werewolf->r_stamina() >= 35) {
			result.being = werewolf;
			result.skill = 1;
			result.strength = 6;
			return result;
		}
		else if (is_archer&&archer->r_stamina() >= 35) {
			result.being = archer;
			result.skill = 2;
			result.strength = 5;
			return result;
		}
		else if (is_mage&&mage_warrior->r_stamina() >= 30) {
			result.being = mage_warrior;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_fighter&&fighter->r_stamina() >= 35) {
			result.being = fighter;
			result.skill = 2;
			result.strength = 5;
			return result;
		}
		else if (is_fighter&&fighter->r_stamina() >= 30) {
			result.being = fighter;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_wizzard&&wizzard->r_stamina() >= 30) {
			result.being = wizzard;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_tank&&tank->r_stamina() >= 30) {
			result.being = tank;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_wolf&&wolf->r_stamina() >= 30&&wolf->str_is_boosted()) {
			result.being = wolf;
			result.skill = 1;
			result.strength = 8;
			return result;
		}
		else if (is_wolf&&wolf->r_stamina() >= 30) {
			result.being = wolf;
			result.skill = 1;
			result.strength = 6;
			return result;
		}
	}
	else if (choice == 1 && team->get_wizzard().second->iam_alive()) {
		result.target = team->get_wizzard().second.get();
		if (is_ghost&&ghost->r_stamina() >= 30 && ghost->int_is_boosted()) {
			result.being = ghost;
			result.skill = 1;
			result.strength = 8;
			return result;
		}
		else if (is_ghost&&ghost->r_stamina() >= 30) {
			result.being = ghost;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_orc&&orc->r_stamina() >= 35 && orc->str_is_boosted()) {
			result.being = orc;
			result.skill = 2;
			result.strength = 8;
			return result;
		}
		else if (is_orc&&orc->r_stamina() >= 35) {
			result.being = orc;
			result.skill = 2;
			result.strength = 5;
			return result;
		}
		else if (is_spider&&spider->r_stamina() >= 35 & spider->dex_is_boosted()) {
			result.being = spider;
			result.skill = 3;
			result.strength = 8;
			return result;
		}
		else if (is_spider&&spider->r_stamina() >= 35) {
			result.being = spider;
			result.skill = 3;
			result.strength = 5;
			return result;
		}
		else if (is_werewolf&&werewolf->r_stamina() >= 40 && werewolf->str_is_boosted()) {
			result.being = werewolf;
			result.skill = 2;
			result.strength = 9;
			return result;
		}
		else if (is_werewolf&&werewolf->r_stamina() >= 35 && werewolf->str_is_boosted()) {
			result.being = werewolf;
			result.skill = 1;
			result.strength = 8;
			return result;
		}
		else if (is_werewolf&&werewolf->r_stamina() >= 35) {
			result.being = werewolf;
			result.skill = 1;
			result.strength = 6;
			return result;
		}
		else if (is_archer&&archer->r_stamina() >= 35) {
			result.being = archer;
			result.skill = 2;
			result.strength = 5;
			return result;
		}
		else if (is_mage&&mage_warrior->r_stamina() >= 30) {
			result.being = mage_warrior;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_fighter&&fighter->r_stamina() >= 35) {
			result.being = fighter;
			result.skill = 2;
			result.strength = 5;
			return result;
		}
		else if (is_fighter&&fighter->r_stamina() >= 30) {
			result.being = fighter;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_wizzard&&wizzard->r_stamina() >= 30) {
			result.being = wizzard;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
		else if (is_tank&&tank->r_stamina() >= 30) {
			result.being = tank;
			result.skill = 1;
			result.strength = 5;
			return result;
		}
	}
	else if (choice == 2) {
		for (auto&x : *team->get_team())
			if (x.second->iam_stuned() && x.second->iam_alive()) {
				result.target = x.second.get();
				if (is_ghost&&ghost->r_stamina() >= 30 && ghost->int_is_boosted()) {
					result.being = ghost;
					result.skill = 1;
					result.strength = 8;
					return result;
				}
				else if (is_ghost&&ghost->r_stamina() >= 30) {
					result.being = ghost;
					result.skill = 1;
					result.strength = 5;
					return result;
				}
				else if (is_orc&&orc->r_stamina() >= 35 && orc->str_is_boosted()) {
					result.being = orc;
					result.skill = 2;
					result.strength = 8;
					return result;
				}
				else if (is_orc&&orc->r_stamina() >= 35) {
					result.being = orc;
					result.skill = 2;
					result.strength = 5;
					return result;
				}
				else if (is_spider&&spider->r_stamina() >= 35 & spider->dex_is_boosted()) {
					result.being = spider;
					result.skill = 3;
					result.strength = 8;
					return result;
				}
				else if (is_spider&&spider->r_stamina() >= 35) {
					result.being = spider;
					result.skill = 3;
					result.strength = 5;
					return result;
				}
				else if (is_werewolf&&werewolf->r_stamina() >= 40 && werewolf->str_is_boosted()) {
					result.being = werewolf;
					result.skill = 2;
					result.strength = 9;
					return result;
				}
				else if (is_werewolf&&werewolf->r_stamina() >= 35 && werewolf->str_is_boosted()) {
					result.being = werewolf;
					result.skill = 1;
					result.strength = 8;
					return result;
				}
				else if (is_werewolf&&werewolf->r_stamina() >= 35) {
					result.being = werewolf;
					result.skill = 1;
					result.strength = 6;
					return result;
				}
				else if (is_archer&&archer->r_stamina() >= 35) {
					result.being = archer;
					result.target = x.second.get();
					result.skill = 2;
					result.strength = 4;
					return result;
				}
				else if (is_mage&&mage_warrior->r_stamina() >= 30) {
					result.being = mage_warrior;
					result.target = x.second.get();
					result.skill = 1;
					result.strength = 4;
					return result;
				}
				else if (is_fighter&&fighter->r_stamina() >= 35) {
					result.being = fighter;
					result.target = x.second.get();
					result.skill = 2;
					result.strength = 4;
					return result;
				}
				else if (is_fighter&&fighter->r_stamina() >= 30) {
					result.being = fighter;
					result.target = x.second.get();
					result.skill = 1;
					result.strength = 4;
					return result;
				}
				else if (is_wizzard&&wizzard->r_stamina() >= 30) {
					result.being = wizzard;
					result.target = x.second.get();
					result.skill = 1;
					result.strength = 4;
					return result;
				}
				else if (is_tank&&tank->r_stamina() >= 30) {
					result.being = tank;
					result.target = x.second.get();
					result.skill = 1;
					result.strength = 4;
					return result;
				}
			}
	}
	Health min_hp = INT16_MAX;
	for (auto&x : *team->get_team())
		if (x.second->r_health() < min_hp&&x.second->iam_alive()) {
			min_hp = x.second->r_health();
			result.target = x.second.get();
		}
	if (is_ghost&&ghost->r_stamina() >= 30 && ghost->int_is_boosted()) {
		result.being = ghost;
		result.skill = 1;
		result.strength = 8;
		return result;
	}
	else if (is_ghost&&ghost->r_stamina() >= 30) {
		result.being = ghost;
		result.skill = 1;
		result.strength = 5;
		return result;
	}
	else if (is_orc&&orc->r_stamina() >= 35 && orc->str_is_boosted()) {
		result.being = orc;
		result.skill = 2;
		result.strength = 8;
		return result;
	}
	else if (is_orc&&orc->r_stamina() >= 35) {
		result.being = orc;
		result.skill = 2;
		result.strength = 5;
		return result;
	}
	else if (is_spider&&spider->r_stamina() >= 35 & spider->dex_is_boosted()) {
		result.being = spider;
		result.skill = 3;
		result.strength = 8;
		return result;
	}
	else if (is_spider&&spider->r_stamina() >= 35) {
		result.being = spider;
		result.skill = 3;
		result.strength = 5;
		return result;
	}
	else if (is_werewolf&&werewolf->r_stamina() >= 40 && werewolf->str_is_boosted()) {
		result.being = werewolf;
		result.skill = 2;
		result.strength = 9;
		return result;
	}
	else if (is_werewolf&&werewolf->r_stamina() >= 35 && werewolf->str_is_boosted()) {
		result.being = werewolf;
		result.skill = 1;
		result.strength = 8;
		return result;
	}
	else if (is_werewolf&&werewolf->r_stamina() >= 35) {
		result.being = werewolf;
		result.skill = 1;
		result.strength = 6;
		return result;
	}
	else if (is_archer&&archer->r_stamina() >= 35) {
		result.being = archer;
		result.skill = 2;
		result.strength = 3;
		return result;
	}
	else if (is_mage&&mage_warrior->r_stamina() >= 30) {
		result.being = mage_warrior;
		result.skill = 1;
		result.strength = 3;
		return result;
	}
	else if (is_fighter&&fighter->r_stamina() >= 33) {
		result.being = fighter;
		result.skill = 2;
		result.strength = 3;
		return result;
	}
	else if (is_fighter&&fighter->r_stamina() >= 30) {
		result.being = fighter;
		result.skill = 1;
		result.strength = 3;
		return result;
	}
	else if (is_wizzard&&wizzard->r_stamina() >= 30) {
		result.being = wizzard;
		result.skill = 1;
		result.strength = 3;
		return result;
	}
	else if (is_tank&&tank->r_stamina() >= 30) {
		result.being = tank;
		result.skill = 1;
		result.strength = 3;
		return result;
	}
	else {
		result.being = nullptr;
		result.skill = 1;
		result.strength = -127;
	}
	return result;
}
void Battle::check() {
	 int team_life_temp = 0;
	 int iterator = 0;
	 for (auto &c : *team->get_team()) {
		 if (c.second->r_health() > 0) {
			 team_life_temp++;
			 team_life[iterator] = true;
		 }
		 else team_life[iterator] = false;
		 iterator++;
	 }
	 int enemy_life_temp = 0;
	 iterator = 0;
	 for (auto &c : *e_team->get_e_team()) {
		 if (c.second->r_health() > 0) {
			 enemy_life_temp++;
			 enemies_life[iterator] = true;
		 }
		 else enemies_life[iterator] = false;
		 iterator++;
	 }
	 team_active = team_life_temp;
	 enemies_active = enemy_life_temp;
 }
void Battle::draw_alive() {
	for (int i = 0; i < 5; i++)if (team_life[i])window->draw(*team->get_team()->operator[](i).first);
	for (int i = 0; i < enemies; i++) if (enemies_life[i])window->draw(e_team->get_e_team()->operator[](i).first);
}
void Battle::show_actual_stats() {
	for (auto&x : team_stats)x->draw();
	for (auto&x : eteam_stats) x->draw();
}
void Battle::update_status() {
	auto it = team_stats.begin();
	for (auto&x : *team->get_team()) {
		string classs = typeid(*x.second).name();
		(*it)->set_text(classs + " Hp:" + std::to_string(x.second->r_health()) + "/" + std::to_string(x.second->r_m_health())); it++;
		(*it)->set_text("St:" + std::to_string(x.second->r_stamina()) + "/" + std::to_string(x.second->r_m_stamina())); it++;
	}
	it = eteam_stats.begin();
	for (auto&x : *e_team->get_e_team()) {
		string classs = typeid(*x.second).name();
		(*it)->set_text(classs + " Hp:" + std::to_string(x.second->r_health()) + "/" + std::to_string(x.second->r_m_health())); it++;
		(*it)->set_text("St:" + std::to_string(x.second->r_stamina()) + "/" + std::to_string(x.second->r_m_stamina())); it++;
	}
}
void Battle::our_round() {
	Text round("Our round!!", window, ratio, sf::Vector2u(window->getSize().x*0.6*ratio.x, window->getSize().y*0.05*ratio.y));
	Text select_pm("Select party member!", window, ratio, sf::Vector2u(window->getSize().x*0.6*ratio.x, window->getSize().y*0.11*ratio.y));
	Text select_skill("Select your skill!", window, ratio, sf::Vector2u(window->getSize().x*0.6*ratio.x, window->getSize().y*0.11*ratio.y));
	Text select_target("Select your targer!", window, ratio, sf::Vector2u(window->getSize().x*0.6*ratio.x, window->getSize().y*0.11*ratio.y));
	Text * current = &select_pm;
	bool escape = 0;
	short status = 0;
	short action = 0;
	std::shared_ptr<Party_member>actual_party_member;
	Being *actual_target = nullptr;
	unsigned short skill_number;
	Button pass_button(window, ratio, "Pass round", sf::Vector2u(window->getSize().x*0.4*ratio.x, window->getSize().y*0.05*ratio.y));
	while (team_active > 0 && enemies_active > 0 && window->isOpen() && !escape&&action<3) {
		bool pass = false;
		sf::Event event;
		while (window->pollEvent(event)) {
			//if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))escape = 1;//window->close();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				window->clear();
				window->draw(background);
				draw_alive();
				update_status();
				show_actual_stats();
				for (auto&x : all_action)x->draw();
				window->display();
				update_status();
			}
		}
		window->clear();
		window->draw(background);
		int temp_skill = 1;
		while (status == 0) {
			window->clear();
			window->draw(background);
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))break;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				window->clear();
				window->draw(background);
				draw_alive();
				update_status();
				show_actual_stats();
				for (auto&x : all_action)x->draw();
				window->display();
				update_status();
			}
			current = &select_pm;
			for (auto&x : team_button) {
				if (x.second->r_health() > 0&&!x.second->iam_stuned()) {
					x.first->draw();
					if (x.first->is_target(sf::Mouse::getPosition()))x.first->set_yellow_background();
					else x.first->set_white_background();
					
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) if (x.first->is_clicked(sf::Mouse::getPosition())) {
							actual_party_member = x.second;
							if (is_type<Archer>(x.second.get()))prize.archer_action++;
							else if (is_type<Fighter>(x.second.get()))prize.fighter_action++;
							else if (is_type<Wizzard>(x.second.get()))prize.wizzard_action++;
							else if (is_type<Tank>(x.second.get()))prize.tank_action++;
							else prize.m_warrior_action++;
							status++;
							wait(200);
						}
				}
			}
			if (pass_button.is_target(sf::Mouse::getPosition()))pass_button.set_yellow_background();
			else pass_button.set_white_background();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))if (pass_button.is_clicked(sf::Mouse::getPosition())) { pass = true; action = 3; status = 4; break; }
			draw_alive();
			round.draw();
			if (current)current->draw();
			pass_button.draw();
			window->display();
		}
		while (status == 1) {
			window->clear();
			window->draw(background);
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))break;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				window->clear();
				window->draw(background);
				draw_alive();
				update_status();
				show_actual_stats();
				for (auto&x : all_action)x->draw();
				window->display();
				update_status();
			}
			current = &select_skill;
			int skill = 1;
			temp_skill = 1;
			for (auto&x : skill_button) {
				if (skill == 1)x->set_text(actual_party_member->get_first_skill()->r_name());
				else if (skill == 2)x->set_text(actual_party_member->get_second_skill()->r_name());
				else x->set_text(actual_party_member->get_third_skill()->r_name());
				x->draw();
				if (x->is_target(sf::Mouse::getPosition()))x->set_yellow_background();
				else x->set_white_background();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))if (x->is_clicked(sf::Mouse::getPosition())) {
					status++;
					skill_number = temp_skill;
					if (is_type<Fighter>(actual_party_member.get()) && skill_number == 3) {
						status = 0;
						action++;
						actual_target = actual_party_member.get();
						window->clear();
						window->draw(background);
						draw_alive();
						round.draw();
						if (current)current->draw();
						window->display();
					}
					wait(200);
				}
				temp_skill++;
				skill++;
			}
			if (pass_button.is_target(sf::Mouse::getPosition()))pass_button.set_yellow_background();
			else pass_button.set_white_background();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				if (pass_button.is_clicked(sf::Mouse::getPosition())) {pass = true; action = 3; status = 4; break;}
			draw_alive();
			round.draw();
			if (current)current->draw();
			pass_button.draw();
			window->display();
		}
		while (status == 2) {
			current = &select_target;
			window->clear();
			window->draw(background);
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))break;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				window->clear();
				window->draw(background);
				draw_alive();
				update_status();
				show_actual_stats();
				for (auto&x : all_action)x->draw();
				window->display();
				update_status();
			}
			for (auto&x : team_button) {
				if (x.second->r_health() > 0) {
					x.first->draw();
					if (x.first->is_target(sf::Mouse::getPosition()))x.first->set_yellow_background();
					else x.first->set_white_background();
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))if (x.first->is_clicked(sf::Mouse::getPosition())) {
						wait(200);
						action++;
						status = 0;
						actual_target = x.second.get();
					}
				}
			}
			for (auto&x : enemies_button) {
				if (x.second->r_health() > 0) {
					x.first->draw();
					if (x.first->is_target(sf::Mouse::getPosition()))x.first->set_yellow_background();
					else x.first->set_white_background();
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))if (x.first->is_clicked(sf::Mouse::getPosition())) {
						wait(200);
						action++;
						status = 0;
						actual_target = x.second;
					}
				}
			}
			if (pass_button.is_target(sf::Mouse::getPosition()))pass_button.set_yellow_background();
			else pass_button.set_white_background();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))if (pass_button.is_clicked(sf::Mouse::getPosition())) { pass = true; action = 3; status = 4; break; }
			draw_alive();
			round.draw();
			if (current)current->draw();
			pass_button.draw();
			window->display();
		}
		current = nullptr;
		if (!pass) {
			if (actual_target != nullptr) {
				string text = typeid(*actual_party_member.get()).name();
				string skill("");
				if (skill_number == 1) {
					if (actual_party_member->get_first_skill()->use_skill(actual_party_member.get(), actual_target)) skill = actual_party_member->get_first_skill()->r_name();
					else { action--; continue; }
				}
				else if (skill_number == 2) {
					if (actual_party_member->get_second_skill()->use_skill(actual_party_member.get(), actual_target)) skill = actual_party_member->get_second_skill()->r_name();
					else { action--; continue; }
				}
				else {
					if (actual_party_member->get_third_skill()->use_skill(actual_party_member.get(), actual_target)) skill = actual_party_member->get_third_skill()->r_name();
					else { action--; continue; }
				}
				text += " use " + skill + " on " + typeid(*actual_target).name();
				if (all_action.size() == 10) while (!all_action.empty()) all_action.pop_front();
				std::shared_ptr<Text> action_text(new Text(text, window, ratio, sf::Vector2u(window->getSize().x*0.45*ratio.x, (window->getSize().y*0.2 + all_action.size() * 30)*ratio.y), 25));
				all_action.push_back(action_text);
				update_status();
				check();
			}
			check();
			update_status();
			draw_alive();
			round.draw();
			if (current)current->draw();
			window->display();
		}
	}
}
void Battle::enemy_round() {
	Text round("Enemy round!!", window, ratio, sf::Vector2u(window->getSize().x*0.6*ratio.x, window->getSize().y*0.05*ratio.y));
	bool escape = 0;
	short action = 0;
	while (team_active > 0 && enemies_active > 0 && window->isOpen() && !escape&&action < 3) {
		Text actual_status("Enemies doing " + std::to_string(action + 1) + " move", window, ratio, sf::Vector2u(window->getSize().x*0.6*ratio.x, window->getSize().y*0.11*ratio.y));
		window->clear();
		window->draw(background);
		sf::Event event;
		while (window->pollEvent(event)) {
			//if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))escape = 1;//window->close();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				window->clear();
				window->draw(background);
				draw_alive();
				update_status();
				show_actual_stats();
				for (auto&x : all_action)x->draw();
				window->display();
				update_status();
			}
		}
		AI();
		if (result.strength >0 ) {
			string text = typeid(*result.being).name();
			string skill("");
			if (result.skill == 1) {
				result.being->get_first_skill()->use_skill(result.being, result.target);
				skill = result.being->get_first_skill()->r_name();
			}
			else if (result.skill == 2) {
				result.being->get_second_skill()->use_skill(result.being, result.target);
				skill = result.being->get_second_skill()->r_name();
			}
			else {
				result.being->get_third_skill()->use_skill(result.being, result.target);
				skill = result.being->get_third_skill()->r_name();
			}
			text += " use " + skill + " on " + typeid(*result.target).name();
			if (all_action.size() == 10)while (!all_action.empty()) all_action.pop_front();
			std::shared_ptr<Text> action_text(new Text(text, window, ratio, sf::Vector2u(window->getSize().x*0.45*ratio.x, (window->getSize().y*0.2 + all_action.size() * 30)*ratio.y), 25));
			all_action.push_back(action_text);
			check();
			update_status();
			draw_alive();
			round.draw();
			actual_status.draw();
			window->display();
			wait(1500);
			action++;
		}
		else {action = 3;break;}
	}
}
