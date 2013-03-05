//
//  LocalPath.java
//  PListPersist
//
//  Created by François Dupayrat on 15/01/13.
//
//
package com.plistpersist.localpath;

import java.io.*;

import android.os.Bundle;
import android.util.Log;

public class LocalPath{
    public static String getLocalPath()
    {
		//TODO : make it so activity reference the main activity
    	String localPath = activity.getFilesDir().getPath();
    	Log.d("LocalPath", "returning local path : " + localPath);
    	return localPath;
    }
}
