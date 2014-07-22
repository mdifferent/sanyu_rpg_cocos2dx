#include "AbstractBattlerData.h"

AbstractBattlerData::AbstractBattlerData(string sName):m_name(sName){}

AbstractBattlerData::~AbstractBattlerData(void){}

AbstractBattlerData::AbstractBattlerData(const AbstractBattlerData &data)
	:m_name(data.getName()),m_status(data.getStatus())
{
}

int AbstractBattlerData::getProperty(const PLAYER_PROP_TYPE cProName) const
{
	if (m_properties.find(cProName) != m_properties.end())
		return m_properties.at(cProName);
	else
	{
		CCLOG("Invalid player property!");
		return -1;
	}
}

void AbstractBattlerData::setProperty(PLAYER_PROP_TYPE cProName,int iProValue)
{
	if(m_properties.find(cProName) != m_properties.end())
		m_properties[cProName] = iProValue;
	else
		m_properties.insert(std::make_pair(cProName,iProValue));
}

void AbstractBattlerData::setStatus(BATTLER_STATUS status) {
    m_status = status;
    if (m_status == DEAD) {
        setProperty(CURRENT_HP, 0);
    }
}