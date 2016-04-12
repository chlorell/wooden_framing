//
//  collada_loader.h
//  WoodFraming
//
//  Created by Mateusz Bugaj on 01.09.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#ifndef __WoodFraming__collada_loader__
#define __WoodFraming__collada_loader__
#include <iostream>
#include <string>
#include <sstream>
#include <pugixml.hpp>

#include <glm/glm.hpp>

#include "graphics_data.hpp"

#include <vector>

namespace floppy
{
    template<typename srcT, typename dstT>
    struct converter
    {
        typedef srcT source_type;
        typedef dstT destination_type;
        
        static destination_type convert(const source_type& src){return (destination_type)src;}
    };
    
    
    
    
    class collada_loader
    {
            pugi::xml_document input_document;
    public:
        collada_loader(){};
        void traverse(std::istream& istream);
        template<class fa, class convert=converter<double, float> >
        static void fill_array(pugi::xml_node node, fa& arr)
        {

            std::stringstream is(node.text().get());
            while(!is.eof())
            {
                typename convert::source_type val;
                is>>val;
                arr.push_back(convert::convert(val));
            }
            
        }
        
        static glm::mat4 projection_from_camera(pugi::xml_node node);
        static glm::mat4 load_node_transform(pugi::xml_node node);
        
        std::pair<std::vector<float>, unsigned short> load_float_array(pugi::xml_node node, const char * idname);
        std::vector<vertex> load_mesh_data(const char * mesh_id);
        glm::mat4 get_node_transform(const char * mesh_name);
        glm::mat4 get_camera_projection(const char * camera_name);
    };
    
    
}


#endif /* defined(__WoodFraming__collada_loader__) */
