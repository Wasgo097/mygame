#include "Armor.h"

void Armor::save_to_file(string path) const {
	std::ofstream str;
	std::ofstream str2;
	str.open("save/" + path + "/armor.bin", std::ios::binary | std::ios::out);
	str2.open("save/" + path + "/armor_type.bin", std::ios::binary | std::ios::out);
	str2 << "physic";
	str.write((char*)&price, sizeof(price));
	str.write((char*)&res_damage, sizeof(res_damage));
	str.write((char*)&weight, sizeof(weight));
	str << name;
	str.close();
	str2.close();
}

void Armor::load_from_file(string path) {
	std::ifstream str;
	str.open("save/" + path + "/armor.bin", std::ios::binary | std::ios::in);
	if (!str.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	str.read((char*)&price, sizeof(price));
	str.read((char*)&res_damage, sizeof(res_damage));
	str.read((char*)&weight, sizeof(weight));
	str >> name;
	res_effect = new std::pair<Effect, Defence>[res_effect_size];
	res_effect[0].first = Effect::bleeding;
	res_effect[0].second = 0;
	res_effect[1].first = Effect::toxic;
	res_effect[1].second = 0;
	res_effect[2].first = Effect::stunning;
	res_effect[2].second = 0;
	str.close();
}

Armor * rand_armor(Quality x) {
	Price pri;
	Name nam;
	Defence def;
	Weight wei;
	def = ((int)x + 1) *std::rand() % 15 + ((int)x) * 10;
	pri = std::rand() % 100 + def * 10 + ((int)x) * 100;
	if (x == Quality::weak)nam = "Weak Armor";
	else if (x == Quality::medium)nam = "Armor";
	else if (x == Quality::strong)nam = "Good Armor";
	else if (x == Quality::rare)nam = "Epic Armor";
	else nam = "Legendary Armor";
	int wei2 = std::rand() % 3;
	if (wei2 == 0)wei = Weight::light;
	else if (wei2 == 1)wei = Weight::medium;
	else wei = Weight::heavy;
	Armor *arm = new Armor(nam, pri, def, wei);
	return arm;
}

Armor * compare_armor(Armor * first, Armor * second) {
	if (first->get_quality()>second->get_quality())return first;
	else return second;
}

Armor * compare_armor_worst(Armor * first, Armor * second) {
	if (first->get_quality() > second->get_quality())return second;
	else return first;
}
