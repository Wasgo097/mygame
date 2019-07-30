#include "Wizzard.h"

void Wizzard::save_to_file() const {
	string path = "wizzard";
	std::ofstream str;
	str.open("save/" + path + "/wizzard.bin", std::ios::binary | std::ios::out);
	str.write((char*)&lv, sizeof(lv));
	str.write((char*)&m_health, sizeof(m_health));
	str.write((char*)&m_stamina, sizeof(m_stamina));
	str.write((char*)&strenght.first, sizeof(strenght.first));
	str.write((char*)&inteligence.first, sizeof(inteligence.first));
	str.write((char*)&dexterity.first, sizeof(dexterity.first));
	str.write((char*)&durability.first, sizeof(durability.first));
	str.write((char*)&max_exp, sizeof(max_exp));
	str.write((char*)&cur_exp, sizeof(cur_exp));
	weapon->save_to_file(path);
	helmet->save_to_file(path);
	armor->save_to_file(path);
	shield->save_to_file(path);
	str.close();
}

void Wizzard::load_from_file() {
	string path = "wizzard";
	std::ifstream main;
	main.open("save/" + path + "/wizzard.bin", std::ios::binary | std::ios::in);
	if (!main.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	main.read((char*)&lv, sizeof(lv));
	main.read((char*)&m_health, sizeof(m_health));
	c_health = m_health;
	main.read((char*)&m_stamina, sizeof(m_stamina));
	c_stamina = m_stamina;
	main.read((char*)&strenght.first, sizeof(strenght.first));
	strenght.second = 0;
	main.read((char*)&inteligence.first, sizeof(inteligence.first));
	inteligence.second = 0;
	main.read((char*)&dexterity.first, sizeof(dexterity.first));
	dexterity.second = 0;
	main.read((char*)&durability.first, sizeof(durability.first));
	durability.second = 0;
	main.read((char*)&max_exp, sizeof(max_exp));
	main.read((char*)&cur_exp, sizeof(cur_exp));
	main.close(); 
	weapon = new Staff();
	weapon->load_from_file(path);
	string type = "";
	std::ifstream helm_type;
	helm_type.open("save/" + path + "/helmet_type.bin", std::ios::binary | std::ios::in);
	if (!helm_type.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	helm_type >> type;
	if (type == "physic") {
		helmet = new Helmet("Helmet");
		helmet->load_from_file(path);
	}
	else {
		helmet = new m_Helmet();
		helmet->load_from_file(path);
	}
	helm_type.close();
	std::ifstream arm_type;
	arm_type.open("save/" + path + "/armor_type.bin", std::ios::binary | std::ios::in);
	if (!arm_type.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	arm_type >> type;
	if (type == "physic") {
		armor = new Armor("Armor");
		armor->load_from_file(path);
	}
	else {
		armor = new m_Armor();
		armor->load_from_file(path);
	}
	arm_type.close();
	std::ifstream shie_type;
	shie_type.open("save/" + path + "/shield_type.bin", std::ios::binary | std::ios::in);
	if (!shie_type.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	shie_type >> type;
	if (type == "physic") {
		shield = new Shield("Shield");
		shield->load_from_file(path);
	}
	else {
		shield = new m_Shield();
		shield->load_from_file(path);
	}
	shie_type.close();
}
