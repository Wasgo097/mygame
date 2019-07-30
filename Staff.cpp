#include "Staff.h"

void Staff::save_to_file(string path) const {
	std::ofstream str;
	str.open("save/" + path + "/staff.bin", std::ios::binary | std::ios::out);
	str.write((char*)&price, sizeof(price));
	str.write((char*)&damage, sizeof(damage));
	str.write((char*)&m_damage, sizeof(m_damage));
	str.write((char*)&weight, sizeof(weight));
	str.write((char*)&effect, sizeof(effect));
	str << name;
	str.close();
}
void Staff::load_from_file(string path){
	std::ifstream str;
	str.open("save/" + path + "/staff.bin", std::ios::binary | std::ios::in);
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
Staff * rand_staff(Quality x)
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
		nam = "Magic Weak Staff";
	}
	else if (x == Quality::medium)
	{
		nam = "Magic Staff";
	}
	else if (x == Quality::strong)
	{
		nam = "Magic Good Staff";
	}
	else if (x == Quality::rare)
	{
		nam = "Magic Epic Staff";
	}
	else
	{
		nam = "Magic Legendary Staff";
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
	Staff *swd = new Staff(pri, nam, dam, wei, m_dam, eff);
	return swd;
}

Staff * comapre_staff(Staff * first, Staff * second) {
	int point_first = first->get_quality();
	int point_second = second->get_quality();
	if (point_first > point_second)return first;
	else return second;
}

Staff * comapre_staff_worst(Staff * first, Staff * second) {
	int point_first = first->get_quality();
	int point_second = second->get_quality();
	if (point_first > point_second)return second;
	else return first;
}
