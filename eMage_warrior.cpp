#include "eMage_warrior.h"

eMage_warrior * rand_eMage_warrior(Quality q)
{

	//magic iteam >6
	int i = std::rand() % 10;
	int lv = (int)q * 10 + std::rand() % 10;
	if (i > 6) {
		return new eMage_warrior(rand_m_sword(q), rand_m_helmet(q), rand_m_armor(q), rand_m_shield(q), lv);
	}
	else {
		return new eMage_warrior(rand_sword(q), rand_helmet(q), rand_armor(q), rand_shield(q), lv);
	}
}
