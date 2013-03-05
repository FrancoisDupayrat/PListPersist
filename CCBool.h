//
//  CCBool.h
//  PListPersist
//
//  Created by François Dupayrat on 15/01/13.
//
//

#ifndef SocialHandy_CCBool_h
#define SocialHandy_CCBool_h

#include "cocos2d.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

class CC_DLL CCBool : public CCObject
{
public:
    CCBool(bool v)
    : m_nValue(v) {}
    bool getValue() const {return m_nValue;}
    
    static CCBool* create(bool v)
    {
        CCBool* pRet = new CCBool(v);
        pRet->autorelease();
        return pRet;
    }
    
    virtual CCObject* copyWithZone(CCZone* pZone)
    {
        CCAssert(pZone == NULL, "CCBool should not be inherited.");
        CCBool* pInt = new CCBool(m_nValue);
        return pInt;
    }
private:
    bool m_nValue;
};

// end of data_structure group
/// @}

NS_CC_END

#endif
