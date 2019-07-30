#include "Spider.h"

Spider * rand_spider(Quality q) {
	//magic iteam >8
	int i = std::rand() % 10;
	Level lv = (int)q * 10 + std::rand() % 10;
	if (i > 8) {
		return  new Spider(rand_m_fangs(q), rand_m_helmet(q), rand_m_armor(q), rand_m_shield(q), lv);
	}
	else {
		return new Spider(rand_fangs(q), rand_helmet(q), rand_armor(q), rand_shield(q), lv);
	}
}
