//
//  TouchEventProcessDelegate.h
//  sanyu
//
//  Created by wuhanming on 14-6-21.
//
//

#ifndef sanyu_TouchEventProcessDelegate_h
#define sanyu_TouchEventProcessDelegate_h

class TouchEventProcessDelegate
{
public:
    enum TouchMessage {
        SELECT_PLAYER,
        PLAYER_ACTION_ATTACK,
        PLAYER_ACTION_SKILL,
        PLAYER_ACTION_ITEM,
        PLAYER_ACTION_DEFENSE,
        PLAYER_ACTION_ESCAPE,
        CLOSE_PLAYER_MENU,
        SELECT_MONSTER,
        SELECT_LIST_CELL,
        CLOSE_SELECT_LIST
    };
    
    virtual void receiveMessage(TouchMessage,...) = 0;
    virtual int getPlayerCount() = 0;
    virtual int getMonsterCount() = 0;
};

#endif
