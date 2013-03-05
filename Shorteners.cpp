//
//  Shorteners.cpp
//  PListPersist
//
//  Created by François Dupayrat on 25/01/13.
//
//

#include "Shorteners.h"

CCString* getResourcesPath(const char* file)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return Screate(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(file));
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return ScreateF("/assets/%s", file);
#endif
}

CCPoint* ccpCreate(CCPoint pos)
{
    CCPoint* pRet = new CCPoint(pos);
    pRet->autorelease();
    return pRet;
}

CCPoint* ccpCreate(float x, float y)
{
    CCPoint* pRet = new CCPoint(x, y);
    pRet->autorelease();
    return pRet;
}

CCSize* sizeCreate(float width, float height)
{
    CCSize* pRet = new CCSize(width, height);
    pRet->autorelease();
    return pRet;
}

//note : keys have to be passed as CCString, unfortunately. Must be NULL terminated
CCDictionary* createDictionaryWithParameters(CCObject* firstObject, ... )
{
    CCObject* eachObject;
	va_list argumentList;
	bool key = true;
	CCObject* object;
	if (firstObject)                      // The first argument isn't part of the varargs list,
	{                                   // so we'll handle it separately.
		//put all parameters in a Dictionary to access them as key/value pairs
		CCDictionary* values = CCDictionary::create();
		object = firstObject;
		va_start(argumentList, firstObject);          // Start scanning for arguments after firstObject.
		while ((eachObject = va_arg(argumentList, CCObject*)) != NULL) // As many times as we can get an argument of type "id"
		{
			if(key)
			{
				//keys should be Strings
				if(!isKindOfClass(eachObject, CCString))
				{
					CCLOG("Warning : not a key, value ignored");
				}
				else
				{
                    CCString* key = (CCString*)eachObject;
                    values->setObject(object, key->m_sString);
				}
			}
			else
			{
				object = eachObject;
			}
			key = !key;
		}
		va_end(argumentList);
		return values;
	}
	else
	{
		CCLOG("Warning : createDictionaryWithParameters called with no firstObject");
	}
    return NULL;
}

CCArray* createArrayWithParameters(CCObject* firstObject, ... )
{
    CCObject* eachObject;
	va_list argumentList;
	if (firstObject)                      // The first argument isn't part of the varargs list,
	{                                   // so we'll handle it separately.
		//put all parameters in a Dictionary to access them as key/value pairs
		CCArray* values = CCArray::create();
        values->addObject(firstObject);
		va_start(argumentList, firstObject);          // Start scanning for arguments after firstObject.
		while ((eachObject = va_arg(argumentList, CCObject*)) != NULL) // As many times as we can get an argument of type "id"
		{
            values->addObject(eachObject);
		}
		va_end(argumentList);
		return values;
	}
	else
	{
		CCLOG("Warning : createArrayWithParameters called with no firstObject");
	}
    return NULL;
}
