//
//  collada_loader.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 01.09.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#include "collada_loader.hpp"
#include <glm/gtc/matrix_transform.hpp>


using namespace floppy;


void collada_loader::traverse(std::istream& istream)
{

    input_document.load(istream);
}

glm::mat4 collada_loader::projection_from_camera(pugi::xml_node node)
{
    double xfov=49.f;
    double aspect=1.7f;
    double znear=0.1f;
    double zfar=100.f;
    
 
        pugi::xml_node perspective=node.first_element_by_path("optics/technique_common/perspective");
        
        xfov=std::atof(perspective.child_value("xfov"));
        aspect=std::atof(perspective.child_value("aspect_ratio"));
        znear=std::atof(perspective.child_value("znear"));
        zfar=std::atof(perspective.child_value("zfar"));
       
 
        //xfov to yfov
     return glm::perspective(2 * atan(tan(xfov * 0.5) * aspect), aspect, znear, zfar);
}


glm::mat4 collada_loader::load_node_transform(pugi::xml_node node)
{
    glm::mat4 ret(glm::one<glm::mat4>());
    std::stringstream is(node.child_value("matrix"));
    for(int i=0;i<4;++i)
          for(int j=0;j<4;++j)
              is>>ret[i][j];
    
    return ret;
}