//
//  CCFloat.h
//  PListPersist
//
//  Created by François Dupayrat on 19/12/12.
//
//

#ifndef SocialHandy_CCFloat_h
#define SocialHandy_CCFloat_h

#include "cocos2d.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCFloat : public CCObject
{
public:
    CCFloat(float v)
    : m_nValue(v) {}
    float getValue() const {return m_nValue;}
    
    static CCFloat* create(float v)
    {
        CCFloat* pRet = new CCFloat(v);
        pRet->autorelease();
        return pRet;
    }
    
    virtual CCObject* copyWithZone(CCZone* pZone)
    {
        CCAssert(pZone == NULL, "CCFloat should not be inherited.");
        CCFloat* pInt = new CCFloat(m_nValue);
        return pInt;
    }
private:
    float m_nValue;
};

// end of data_structure group
/// @}

NS_CC_END

#endif
