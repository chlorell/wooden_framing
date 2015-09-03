//
//  iOS_wrapper.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 15.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#include "iOS_wrapper.hpp"

#include <string>
#include <iostream>

#include <OpenGLES/ES2/glext.h>

#include <boost/filesystem.hpp>

#include <pugixml.hpp>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>

namespace floppy{
    
    
int desiredFPS()
{
    return 60;
}

void startEngine(){
    std::cout<<"startEngine"<<std::endl;
    
     std::cout<<"b2_version="<<b2_version.major<<"."<<b2_version.minor<<"@"<<b2_version.revision<<std::endl;
     std::cout<<"liquidFunVersion="<<b2_liquidFunVersionString<<std::endl;
   
    std::cout<<"PUGIXML_VERSION="<<PUGIXML_VERSION<<std::endl;
    glm::vec2 ver(b2_version.major,b2_version.minor);
    
    
}


void stopEngine(){
    std::cout<<"stopEngine"<<std::endl;
}

    
void appPause(){
    std::cout<<"appPause"<<std::endl;
}

void appResume(){
    std::cout<<"appResume"<<std::endl;
}


void everyFrameUpdate(){
 
}

void drawCalls(){
   
    glClearColor(0., 0., 0., 1.);
    glClear(GL_COLOR_BUFFER_BIT);
}

void appWillTerminate()
{
    std::cout<<"appWillTerminate"<<std::endl;
}


void appDidGoToBackground()
{
    std::cout<<"appDidGoToBackground"<<std::endl;
}


void failedToCreateGLContext()
{
    std::cout<<"failedToCreateGLContext"<<std::endl;
}
    
    
void setResourcesBaseDirectory(const char * path)
{
        std::cout<<"setResourcesBaseDirectory:"<<path<<std::endl;
    
    for(auto entry : boost::filesystem::directory_iterator(path))
    {
         std::cout<<">>"<<entry.path().c_str()<<std::endl;
    }
    
 
}
    
}