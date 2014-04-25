#pragma once
#include <map>
#include <string>
using namespace std;

class PlayerData
{
public:
	PlayerData(string cName);
	~PlayerData(void);
	string getPlayerName() const;
	
	void setProperty(string &cProName,int iProValue);
	int getProperty(string &cProName);
	
	int useItem(string &name);

private:
	string m_name;
	map<string,int> m_properties;	//name-value
	map<string,int> m_items;		//name-amount
	map<string,int> m_skills;		//name-status
};

