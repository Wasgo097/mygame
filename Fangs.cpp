#include "Fangs.h"

void Fangs::save_to_file(string path) const {
	std::ofstream str;
	std::ofstream str2;
	str.open("save/" + path + "/fangs.bin", std::ios::binary | std::ios::out);
	str2.open("save/" + path + "/fangs_type.bin", std::ios::binary | std::ios::out);
	str2 << "physic";
	str.write((char*)&price, sizeof(price));
	str.write(name.c_str(), name.size());
	str.write((char*)&damage, sizeof(damage));
	str.write((char*)&weight, sizeof(weight));
	str << name;
	str.close();
	str2.close();
}

void Fangs::load_from_file(string path) {
	std::ifstream str;
	str.open("save/" + path + "/fangs.bin", std::ios::binary | std::ios::in);
	if (!str.good()) {
		std::cout << "Loading error";
		exit(-1);
	}
	str.read((char*)&price, sizeof(price));
	str.read((char*)&damage, sizeof(damage));
	str.read((char*)&weight, sizeof(weight));
	str >> name;
	this->m_damage = 0;
	this->effect = Effect::none;
	str.close();
}

Fangs * rand_fangs(Quality x)
{
	Price pri;
	Name nam;
	Damage dam;
	Weight wei;
	dam = 10 + ((int)x + 1) *std::rand() % 20 + ((int)x) * 10;
	pri = std::rand() % 100 + dam * 10 + ((int)x) * 100;
	if (x == Quality::weak)
	{
		nam = "Weak Fangs";
	}
	else if (x == Quality::medium)
	{
		nam = "Fangs";
	}
	else if (x == Quality::strong)
	{
		nam = "Good Fangs";
	}
	else if (x == Quality::rare)
	{
		nam = "Epic Fangs";
	}
	else
	{
		nam = "Legendary Fangs";
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
	Fangs *swd = new Fangs(pri, nam, dam, wei);
	return swd;
}
