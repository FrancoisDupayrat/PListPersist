#PListPersist
A C++ module to load and save plist files in native objects for [Cocos2d-X](https://github.com/cocos2d/cocos2d-x). Supports Android and iOS.

#Environment
***cocos2d-2.0-x-2.0.4*** or higher is recommended. Lower versions are not tested.

#Known problems
* the local path won't work out of the box on Android
* when reading a plist, it must not contain unescaped % (to escape one, double it)
* can't load from package on Android, it will automatically switch back to local resources

#Roadmap
* Get the local path on Android correctly
* Allow to load a plist from package on Android
* Add Date support
* Add Data support

#Email: <fradow@gmail.com>
#You're welcome to contribute. ;-)
