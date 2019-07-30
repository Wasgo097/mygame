#include "m_Shield.h"

void m_Shield::save_to_file(string path) const {
	std::ofstream str;
	std::ofstream str2;
	str.open("save/" + path + "/shield.bin", std::ios::binary | std::ios::out);
	str2.open("save/" + path + "/shield_type.bin", std::ios::binary | std::ios::out);
	str2 << "magic";
	str.write((char*)&price, sizeof(price));
	str.write((char*)&res_damage, sizeof(res_damage));
	str.write((char*)&weight, sizeof(weight));
	str.write((char*)res_effect, sizeof(res_effect));
	str << name;
	str.close();
	str2.close();
}

void m_Shield::load_from_file(string path) {
	std::ifstream str;
	str.open("save/" + path + "/shield.bin", std::ios::binary | std::ios::in);
	res_effect = new std::pair<Effect, Defence>[res_effect_size];
	if (!str.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	str.read((char*)&price, sizeof(price));
	str.read((char*)&res_damage, sizeof(res_damage));
	str.read((char*)&weight, sizeof(weight));
	str.read((char*)res_effect, sizeof(res_effect));
	str >> name;
	str.close();
}

m_Shield * rand_m_shield(Quality x)
{
	Price pri;
	Name nam;
	Defence def;
	Weight wei;
	std::pair  <Effect, Defence> * res_eff = new std::pair  <Effect, Defence>[3];
	res_eff[0].first = Effect::bleeding;
	res_eff[0].second = (int)x *std::rand() % 15 + ((int)x);
	res_eff[1].first = Effect::toxic;
	res_eff[1].second = (int)x *std::rand() % 20 + ((int)x);
	res_eff[2].first = Effect::stunning;
	res_eff[2].second = (int)x *std::rand() % 10 + ((int)x);
	def = ((int)x + 1) *std::rand() % 15 + ((int)x) * 10;
	pri = std::rand() % 100 + def * 10 + ((int)x) * 200 + res_eff[0].second * 10 + res_eff[1].second * 10 + res_eff[2].second * 10;
	if (x == Quality::weak)
	{
		nam = "Weak Magic Shield";
	}
	else if (x == Quality::medium)
	{
		nam = "Magic Shield";
	}
	else if (x == Quality::strong)
	{
		nam = "Good Magic Shield";
	}
	else if (x == Quality::rare)
	{
		nam = "Epic Magic Shield";
	}
	else
	{
		nam = "Legendary Magic Shield";
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
	m_Shield *arm = new m_Shield(res_eff, nam, pri, def, wei);
	return arm;
}
