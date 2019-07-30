#include "m_Bow.h"

void m_Bow::save_to_file(string path) const {
	std::ofstream str;
	std::ofstream str2;
	str.open("save/" + path + "/bow.bin", std::ios::binary | std::ios::out);
	str2.open("save/" + path + "/bow_type.bin", std::ios::binary | std::ios::out);
	str2 << "magic";
	str.write((char*)&price, sizeof(price));
	str.write((char*)&damage, sizeof(damage));
	str.write((char*)&m_damage, sizeof(m_damage));
	str.write((char*)&weight, sizeof(weight));
	str.write((char*)&effect, sizeof(effect));
	str << name;
	str.close();
	str2.close();
}
void m_Bow::load_from_file(string path){
	std::ifstream str;
	str.open("save/" + path + "/bow.bin", std::ios::binary | std::ios::in);
	if (!str.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	str.read((char*)&price, sizeof(price));
	str.read((char*)&damage, sizeof(damage));
	str.read((char*)&m_damage, sizeof(m_damage));
	str.read((char*)&weight, sizeof(weight));
	str.read((char*)&effect, sizeof(effect));
	str >> name;
	str.close();
}
m_Bow * rand_m_bow(Quality x) {
	Price pri;
	Name nam;
	Damage dam, m_dam;
	Weight wei;
	Effect eff;
	m_dam = 5 + (int)x *std::rand() % 16 + ((int)x) * 5;
	dam = 10 + ((int)x + 1) *std::rand() % 20 + ((int)x) * 10;
	pri = std::rand() % 200 + dam * 10 + ((int)x) * 150 + m_dam * 100;
	if (x == Quality::weak)
	{
		nam = "Magic Weak Bow";
	}
	else if (x == Quality::medium)
	{
		nam = "Magic Bow";
	}
	else if (x == Quality::strong)
	{
		nam = "Magic Good Bow";
	}
	else if (x == Quality::rare)
	{
		nam = "Magic Epic Bow";
	}
	else
	{
		nam = "Magic Legendary Bow";
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
	int eff2 = std::rand() % 3;
	if (eff2 == 0)
	{
		eff = Effect::bleeding;
	}
	else if (eff2 == 1)
	{
		eff = Effect::toxic;
	}
	else
	{
		eff = Effect::stunning;
	}
	m_Bow *swd = new m_Bow(pri, nam, dam, wei, m_dam, eff);
	return swd;
}
