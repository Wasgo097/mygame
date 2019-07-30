#pragma once
#include "Shared.h"
class Iteam{
protected:
	Price price;
	Name name;
	Weight weight;
	Iteam(Price pri=10, Name nam="Iteam",Weight wei=Weight::medium) :price(pri),name(nam),weight(wei){}
public:
	Price r_price()const { return price; }
	void s_price(Price x) { price = x; }
	Name r_name()const { return name; }
	void s_name(Name x) { name = x; }
	Weight r_weight() { return weight; }
	void s_weight(Weight x) { weight = x; }
	virtual void save_to_file(string)const = 0;
	virtual void load_from_file(string)= 0;
};
