#include "Wolf.h"

Wolf * rand_wolf(Quality q) {
	//magic iteam >6
	int i = std::rand() % 10;
	Level lv = (int)q * 10 + std::rand() % 10;
	if (i > 6) {
		return  new Wolf(rand_m_fangs(q), rand_m_helmet(q), rand_m_armor(q), rand_m_shield(q), lv);
	}
	else {
		return new Wolf(rand_fangs(q), rand_helmet(q), rand_armor(q), rand_shield(q), lv);
	}
}
