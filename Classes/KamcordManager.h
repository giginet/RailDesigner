//
//  KamcordEvent.h
//  kamcordTest
//
//  Created by FUJITAYASUO on 2015/05/01.
//
//
#include "cocos2d.h"

#ifndef __everyplayTest__KamcordManager__
#define __everyplayTest__KamcordManager__

namespace platform
{
    
    class KamcordManager
    {
    public:
        KamcordManager();
        ~KamcordManager();
        
        static KamcordManager* getInstance();
        void setup(std::string key, std::string secret, std::string appName);
        void startRecording();
        void stopRecording();
        void pauseRecording();
        void resumeRecording();
        
    private:
        
    };
    
}

#endif /* defined(__everyplayTest__KamcordManager__) */
