//
//  iOS_wrapper.h
//  WoodFraming
//
//  Created by Mateusz Bugaj on 15.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#ifndef __WoodFraming__iOS_wrapper__
#define __WoodFraming__iOS_wrapper__


namespace floppy
{

    int desiredFPS();
    void startEngine();
    void stopEngine();

    void appPause();
    void appResume();
    void appWillTerminate();
    void appDidGoToBackground();

    void everyFrameUpdate();
    void drawCalls();

    //errors:

    void failedToCreateGLContext();


    void setResourcesBaseDirectory(const char * path);
};




#endif /* defined(__WoodFraming__iOS_wrapper__) */
