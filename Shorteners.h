//
//  Shorteners.h
//  PListPersist
//
//  Created by François Dupayrat on 19/12/12.
//
//

#ifndef SocialHandy_Shorteners_h
#define SocialHandy_Shorteners_h

#include "cocos2d.h"
#include "SceneSwitcher.h"
#include "CCFloat.h"
#include "CCBool.h"
USING_NS_CC;

#define isKindOfClass(obj,class) (dynamic_cast<class*>(obj) != NULL)

//Compensate for scale factor for image picked by user
#define AUTO_SCALE (Fcreate(CCDirector::sharedDirector()->getContentScaleFactor() ))

#define REAL_SCALE(obj) (Fcreate(obj \
* CCDirector::sharedDirector()->getContentScaleFactor() ))

#define TOINT(obj) (((CCInteger*)obj)->getValue())
#define TOFLOAT(obj) (((CCFloat*)obj)->getValue())
#define TOBOOL(obj) (((CCBool*)obj)->getValue())
#define TOCSTRING(obj) (((CCString*)obj)->getCString())

/* creation shorteners : since those are widly used, shortening the name makes sense (much like ccp), as well as uniformizing the format
 * format *create where * is the type
 I = Integer
 F = Float
 B = Bool
 S = String, append F for format
 D = Dictionary, append P for parameters
 A = Array, append P for parameters
 */

#define Icreate CCInteger::create
#define Fcreate CCFloat::create
#define Bcreate CCBool::create
#define Screate CCString::create
#define ScreateF CCString::createWithFormat
#define Dcreate CCDictionary::create
#define DcreateP createDictionaryWithParameters
#define Acreate CCArray::create
#define AcreateP createArrayWithParameters

CCString* getResourcesPath(const char* file);
//note : keys have to be passed as CCString, unfortunately. Must be NULL terminated
CCDictionary* createDictionaryWithParameters(CCObject* firstObject, ... );
CCArray* createArrayWithParameters(CCObject* firstObject, ... );


#endif
