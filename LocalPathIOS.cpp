//
//  LocalPathIOS.cpp
//  PListPersist
//
//  Created by François Dupayrat on 14/01/13.
//
//

#include "LocalPath"

CCString* getLocalPath(const char* name)
{
    return ScreateF("%s/Documents/%s", getenv("HOME"), name);
}
