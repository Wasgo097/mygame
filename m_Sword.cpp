#include "m_Sword.h"

void m_Sword::save_to_file(string path) const {
	std::ofstream str;
	std::ofstream str2;
	str.open("save/" + path + "/sword.bin", std::ios::binary | std::ios::out);
	str2.open("save/" + path + "/sword_type.bin", std::ios::binary | std::ios::out);
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
void m_Sword::load_from_file(string path) {
	std::ifstream str;
	str.open("save/" + path + "/sword.bin", std::ios::binary | std::ios::in);
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
m_Sword * rand_m_sword(Quality x)
{
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
		nam = "Magic Weak Sword";
	}
	else if (x == Quality::medium)
	{
		nam = "Magic Sword";
	}
	else if (x == Quality::strong)
	{
		nam = "Magic Good Sword";
	}
	else if (x == Quality::rare)
	{
		nam = "Magic Epic Sword";
	}
	else
	{
		nam = "Magic Legendary Sword";
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
	m_Sword *swd = new m_Sword(pri, nam, dam, wei, m_dam, eff);
	return swd;
}
