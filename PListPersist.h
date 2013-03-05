//
//  PListPersist.h
//  PListPersist
//
//  Created by François Dupayrat on 14/01/13.
//
//

#ifndef __SocialHandy__PListPersist__
#define __SocialHandy__PListPersist__

#define VERBOSE_SAVE 1
#define VERBOSE_LOAD 1

#include "cocos2d.h"
USING_NS_CC;
#include "pugixml.hpp"

//Currently handle Dictionary, Array, Integer, Float, Bool and String in a plist format
// NOT HANDLED : Date and Data

void saveObjectToFile(CCObject* obj, const char* name);
CCObject* loadObjectFromFile(const char* name, bool resource = false);

#endif /* defined(__SocialHandy__PListPersist__) */
