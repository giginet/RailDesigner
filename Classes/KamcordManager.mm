//
//  KamcordEvent.cpp
//  kamcordTest
//
//  Created by FUJITAYASUO on 2015/05/01.
//
//

#import "KamcordManager.h"
#import <Kamcord/Kamcord.h>

namespace platform {

    KamcordManager::KamcordManager(){
    };

    platform::KamcordManager::~KamcordManager(){
    };
    
    KamcordManager* KamcordManager::getInstance()
    {
        static KamcordManager manager;
        return &manager;
    }
    
    void KamcordManager::setup(std::string key, std::string secret, std::string appName) {

        NSString* NSKey = [[[NSString alloc] initWithCString:key.c_str() encoding:NSUTF8StringEncoding] autorelease];
        NSString* NSSecret = [[[NSString alloc] initWithCString:secret.c_str() encoding:NSUTF8StringEncoding] autorelease];
        NSString* NSAppName = [[[NSString alloc] initWithCString:appName.c_str() encoding:NSUTF8StringEncoding] autorelease];

        
        UIViewController* rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        [Kamcord setDeveloperKey:NSKey
                 developerSecret:NSSecret
                         appName:NSAppName
        parentViewController:rootViewController];

        return;
    }
    
    void KamcordManager::startRecording()
    {
        [Kamcord startRecording];
    }
    
    void KamcordManager::stopRecording()
    {
        [Kamcord stopRecording];
        [Kamcord showView];
    }
    
    void KamcordManager::pauseRecording()
    {
        [Kamcord pause];
    }
    
    void KamcordManager::resumeRecording()
    {
        [Kamcord resume];
    }
    
}