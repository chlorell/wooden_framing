//
//  iOS_wrapper.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 15.08.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//


#include <string>
#include <iostream>
#include <memory>

#include <OpenGLES/ES2/glext.h>

#include <pugixml.hpp>
#include <Box2D/Box2D.h>
#include <glm/glm.hpp>


#include <boost/filesystem.hpp>


#include "iOS_wrapper.hpp"
#include "simple_renderer.hpp"

namespace floppy{

    static std::unique_ptr<simple_renderer> renderer;
    static std::string base_path;
    
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
    
    renderer.reset(new simple_renderer(base_path));
}


void stopEngine(){
    std::cout<<"stopEngine"<<std::endl;
    renderer.reset();
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
    if(renderer)
    {
        renderer->draw();
    }
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
    base_path=path;
    for(auto entry : boost::filesystem::directory_iterator(path))
    {
         std::cout<<">>"<<entry.path().c_str()<<std::endl;
    }
    
 
}
    
}