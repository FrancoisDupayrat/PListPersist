//
//  PListPersist.cpp
//  PListPersist
//
//  Created by François Dupayrat on 14/01/13.
//
//

#include "PListPersist.h"
#include "CCFloat.h"
#include "CCBool.h"
#include "Shorteners.h"
#include "LocalPath.h"

using namespace pugi;

//Code from code_save_custom_writer to print doc result
struct xml_string_writer: pugi::xml_writer
{
    std::string result;
    
    virtual void write(const void* data, size_t size)
    {
        result += std::string(static_cast<const char*>(data), size);
    }
};

std::string node_to_string(pugi::xml_node node)
{
    xml_string_writer writer;
    node.print(writer);
    
    return writer.result;
}

void appendObject(CCObject* obj, xml_node& node)
{
    if(isKindOfClass(obj, CCDictionary))
    {
    	//CCLOG("Dictionary recognized");
        CCDictionary* dict = (CCDictionary*)obj;
        xml_node children = node.append_child("dict");
        CCArray* keys = dict->allKeys();
        if(keys != NULL)
        {
            for(int i = 0; i < keys->count(); i++)
            {
                CCString* key = (CCString*)keys->objectAtIndex(i);
                children.append_child("key").append_child(node_pcdata).set_value(key->getCString());
                appendObject(dict->objectForKey(key->getCString()), children);
            }
        }
    }
    else if(isKindOfClass(obj, CCArray))
    {
    	//CCLOG("Array recognized");
        CCArray* array = (CCArray*)obj;
        xml_node children = node.append_child("array");
        for(int i = 0; i < array->count(); i++)
        {
            CCObject* child = (CCObject*)array->objectAtIndex(i);
            appendObject(child, children);
        }
    }
    else if (isKindOfClass(obj, CCString))
    {
    	//CCLOG("String recognized");
        node.append_child("string").append_child(node_pcdata).set_value(((CCString*)obj)->getCString());
    }
    else if (isKindOfClass(obj, CCInteger))
    {
    	//CCLOG("Integer recognized");
        int value = TOINT(obj);
        CCString* stringVal = ScreateF("%d", value);
        node.append_child("integer").append_child(node_pcdata).set_value(stringVal->getCString());
    }
    else if (isKindOfClass(obj, CCFloat))
    {
    	//CCLOG("Float recognized");
        float value = TOFLOAT(obj);
        CCString* stringVal = ScreateF("%g", value);
        node.append_child("real").append_child(node_pcdata).set_value(stringVal->getCString());
    }
    else if (isKindOfClass(obj, CCBool))
    {
    	//CCLOG("Bool recognized");
        bool value = TOBOOL(obj);
        node.append_child(value ? "true" : "false");
    }
    else
    {
        CCLOG(ScreateF("Warning: unrecognized type %s when saving plist, check if the object is in plist format", typeid(*obj).name())->getCString());
    }
}

void saveObjectToFile(CCObject* obj, const char* name)
{
    xml_document doc;
    //add the verbose things so that it's a proper plist like those created by xcode
    xml_node decl = doc.prepend_child(node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";
    xml_node doctype = doc.append_child(node_doctype);
    doctype.set_value("plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"");
    xml_node plistNode = doc.append_child("plist");
    
    //construct the actual plist informations
    appendObject(obj, plistNode);
    
#if VERBOSE_LOAD
    CCLOG(ScreateF("Saving document :\n%s", node_to_string(doc).c_str())->getCString());
#endif
    doc.save_file(getLocalPath(name)->getCString());
}

CCObject* loadObject(xml_node node)
{
    const char* name = node.name();
    CCObject* obj = NULL;
    if(strcmp(name, "dict") == 0)
    {
        obj = Dcreate();
        char* key;
        bool isKey = true;
        for(xml_node child = node.first_child(); child; child = child.next_sibling())
        {
            if(isKey)
            {
                key = const_cast<char*>(child.first_child().value());//remove const while reading value, easier that way
            }
            else
            {
                CCObject* result = loadObject(child);
                if(result != NULL)
                {
                    ((CCDictionary*)obj)->setObject(result, key);
                }
            }
            isKey = !isKey;
        }
    }
    else if(strcmp(name, "array") == 0)
    {
        obj = Acreate();
        for(xml_node child = node.first_child(); child; child = child.next_sibling())
        {
            CCObject* result = loadObject(child);
            if(result != NULL)
            {
                ((CCArray*)obj)->addObject(result);
            }
        }
    }
    else if(strcmp(name, "string") == 0)
    {
        obj = Screate(node.first_child().value());
    }
    else if(strcmp(name, "integer") == 0)
    {
        obj = Icreate(atoi(node.first_child().value()));
    }
    else if(strcmp(name, "real") == 0)
    {
        obj = Fcreate(atof(node.first_child().value()));
    }
    else if(strcmp(name, "true") == 0)
    {
        obj = Bcreate(true);
    }
    else if(strcmp(name, "false") == 0)
    {
        obj = Bcreate(false);
    }
    else
    {
        CCLOG(ScreateF("Warning: unrecognized type \"%s\" when loading plist, check if the plist is correctly formated", name)->getCString());
    }
    return obj;
}

CCObject* loadObjectFromFile(const char* name, bool resource)
{
    xml_document doc;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(resource)
    {
        CCLOG("Warning: trying to load a resource on Android won't work, do you copy it to resource beforehand ? Using local path anyway");
    }
    //TODO : add something to load the file to local folder here instead of at start-up
    const char* path = getLocalPath(name)->getCString();
#else
    const char* path = resource ? getResourcesPath(name)->getCString() : getLocalPath(name)->getCString();
#endif
#if VERBOSE_LOAD
    CCLOG(ScreateF("Loading from path :\n%s", path)->getCString());
#endif
    doc.load_file(path);
#if VERBOSE_LOAD
    CCLOG("Document loaded, parsing it");
    CCLOG(node_to_string(doc).c_str()); 
#endif
    CCObject* result = loadObject(doc.child("plist").first_child());

#if VERBOSE_LOAD
    CCLOG("Parse successful, returning");
#endif
    return result;
}
