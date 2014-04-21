#pragma once
#include "cocoa/CCDictionary.h"
USING_NS_CC;

class PlayerData
{
public:
	PlayerData(CCString m_name);
	~PlayerData(void);
	void setProperty(CCString proName,int proValue);
	int getProperty(CCString);

private:
	CCString m_name;
	CCDictionary *m_properties;
	CCDictionary *m_items;
	CCDictionary *m_skills;
};

