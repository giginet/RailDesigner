package org.kawaz.RailDesigner.videorec;

import org.cocos2dx.cpp.AppActivity;

import android.app.Activity;

import com.kamcord.android.Kamcord;

public class KamcordManager {

	public static void setup(final String key,final String secret,final String appName) {
		
		Kamcord.initKeyAndSecret(key, secret, appName);
		Kamcord.initActivity(AppActivity.getActivity());
	}
	
	public static void startRecording() {
		Kamcord.startRecording();
	}
	
	public static void stopRecording() {
		Kamcord.stopRecording();
		Kamcord.showView();
	}
}
