#include "m_Armor.h"

void m_Armor::save_to_file(string path) const {
	std::ofstream str;
	std::ofstream str2;
	str.open("save/" + path + "/armor.bin", std::ios::binary | std::ios::out);
	str2.open("save/" + path + "/armor_type.bin", std::ios::binary | std::ios::out);
	str2 << "magic";
	str.write((char*)&price, sizeof(price));
	str.write((char*)&res_damage, sizeof(res_damage));
	str.write((char*)&weight, sizeof(weight));
	str.write((char*)&res_effect[0].first,sizeof(res_effect[0].first));
	str.write((char*)&res_effect[0].second,sizeof(res_effect[0].second));
	str.write((char*)&res_effect[1].first,sizeof(res_effect[1].first));
	str.write((char*)&res_effect[1].second,sizeof(res_effect[1].second));
	str.write((char*)&res_effect[2].first,sizeof(res_effect[2].first));
	str.write((char*)&res_effect[2].second,sizeof(res_effect[2].second));
	str << name;
	str.close();
	str2.close();
}

void m_Armor::load_from_file(string path) {
	std::ifstream str;
	str.open("save/" + path + "/armor.bin", std::ios::binary | std::ios::in);
	res_effect = new std::pair<Effect, Defence>[res_effect_size];
	if (!str.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	str.read((char*)&price, sizeof(price));
	str.read((char*)&res_damage, sizeof(res_damage));
	str.read((char*)&weight, sizeof(weight));
	str.read((char*)&res_effect[0].first, sizeof(res_effect[0].first));
	str.read((char*)&res_effect[0].second, sizeof(res_effect[0].second));
	str.read((char*)&res_effect[1].first, sizeof(res_effect[1].first));
	str.read((char*)&res_effect[1].second, sizeof(res_effect[1].second));
	str.read((char*)&res_effect[2].first, sizeof(res_effect[2].first));
	str.read((char*)&res_effect[2].second, sizeof(res_effect[2].second));
	str >> name;
	str.close();
}

m_Armor * rand_m_armor(Quality x) {
	Price pri;
	Name nam;
	Defence def;
	Weight wei;
	std::pair  <Effect, Defence> * res_eff = new std::pair  <Effect, Defence>[3];
	res_eff[0].first = Effect::bleeding;
	res_eff[0].second = ((int)x + 1) *std::rand() % 20;
	res_eff[1].first = Effect::toxic;
	res_eff[1].second = ((int)x + 1) *std::rand() % 10;
	res_eff[2].first = Effect::stunning;
	res_eff[2].second = ((int)x+1) *std::rand() % 15;
	def = ((int)x + 1) *std::rand() % 15 + ((int)x) * 10;
	pri = std::rand() % 100 + def * 10 + ((int)x) * 200 + res_eff[0].second * 10 + res_eff[1].second * 10 + res_eff[2].second * 10;
	if (x == Quality::weak)
	{
		nam = "Weak Magic Armor";
	}
	else if (x == Quality::medium)
	{
		nam = "Magic Armor";
	}
	else if (x == Quality::strong)
	{
		nam = "Good Magic Armor";
	}
	else if (x == Quality::rare)
	{
		nam = "Epic Magic Armor";
	}
	else
	{
		nam = "Legendary Magic Armor";
	}
	int wei2 = std::rand() % 3;
	if (wei2 == 0)
	{
		wei = Weight::light;
	}
	else if (wei2 == 1)
	{
		wei = Weight::medium;
	}
	else
	{
		wei = Weight::heavy;
	}
	m_Armor *arm = new m_Armor(res_eff, nam, pri, def, wei);
	return arm;
}
