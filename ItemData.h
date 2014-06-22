#pragma once
#include "AbstractListItemData.h"
#include <string>
#include <map>
using namespace std;

class ItemData : public AbstractListItemData
{
public:
	enum ITEM_TYPE {
		CONSUME,
		ATTRIBUTE,
		SPECIAL
	};

	ItemData(int id, string name, TargetType target, bool multi, ITEM_TYPE type)
		:AbstractListItemData(id,name,target,multi),m_type(type) {}
	~ItemData(){}

	ITEM_TYPE getItemType() const {return m_type;}
private:
	ITEM_TYPE m_type;
};