//
//  collada_loader.cpp
//  WoodFraming
//
//  Created by Mateusz Bugaj on 01.09.2015.
//  Copyright (c) 2015 Ocean Planet Studios. All rights reserved.
//

#include "collada_loader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "graphics_data.hpp"
#include <numeric>
#include <algorithm>

using namespace floppy;


void collada_loader::traverse(std::istream& istream)
{

    pugi::xml_parse_result res=input_document.load(istream);
    if(res.status!=pugi::status_ok)
    {
        std::cout<<istream.rdbuf();
    }
        
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

std::vector<vertex> collada_loader::load_mesh_data(const char * mesh_id)
{
    std::string  xpath="/COLLADA/library_geometries/geometry[@id='";
    xpath+=mesh_id;
    xpath+="']";
    
    std::vector<vertex> ret;
    
    pugi::xpath_node find=input_document.select_node(xpath.c_str());
    if(find.node())
    {
        pugi::xml_node base=find.node();
        base=base.child("mesh");
        if(base)
        {
            
            pugi::xml_node polylist=base.child("polylist");
            unsigned polycount=polylist.attribute("count").as_uint();
            std::vector<unsigned short> polys(polycount);
 
                pugi::xml_node vcount=polylist.child("vcount");
                collada_loader::fill_array(vcount, polys);
            
            std::vector<unsigned> indexes(std::accumulate(polys.begin(), polys.end(), 0));
            ret.reserve(indexes.max_size());
            pugi::xml_node idxbuff=polylist.child("p");
            collada_loader::fill_array(idxbuff, indexes);
            std::vector<std::pair<std::vector<float>, unsigned short>> attributes(3);
            std::vector<unsigned short> offsets;
            std::vector<std::string> semantics;
            unsigned short max_offset=0;
            for ( auto node : polylist.children("input"))
            {
                std::string semantic=node.attribute("semantic").as_string();
                unsigned short offset=node.attribute("offset").as_uint();
                semantics.push_back(semantic);
                offsets.push_back(offset);
                if(offset>max_offset)max_offset=offset;
                attributes.push_back(load_float_array(base, node.attribute("source").as_string()));
            }
            
            for (unsigned i=0; i<indexes.size(); i+=max_offset+1) {
                vertex current;
                ret.push_back(current);
                
                
            }
            
            for (unsigned attr=0; attr<attributes.size();++attr) {
                unsigned offset=offsets[attr];
                std::string semantic=semantics[attr];
                auto arrpair=attributes[attr];
                if(semantic=="VERTEX") {
                    for (unsigned i=0; i<ret.size();++i) {
                        vertex & current=ret[i];
                        unsigned idx=i*(max_offset+1)+offset;
                        idx=indexes[idx];
                        unsigned stride=arrpair.second;
                        for (int s=0; s<std::min(stride,3u); ++s) {
                            current.pos[s]=arrpair.first[idx*stride+s];
                        }
                    }
                }else if(semantic=="NORMAL")
                {
                    for (unsigned i=0; i<ret.size();++i) {
                        vertex & current=ret[i];
                        unsigned idx=i*(max_offset+1)+offset;
                        idx=indexes[idx];
                        unsigned  stride=arrpair.second;
                        for (int s=0; s<std::min(stride,3u); ++s) {
                            current.normal[s]=arrpair.first[idx*stride+s];
                        }
                    }
                }else if(semantic=="TEXCOORD")
                {
                    for (unsigned i=0; i<ret.size();++i) {
                        vertex & current=ret[i];
                        unsigned idx=i*(max_offset+1)+offset;
                        idx=indexes[idx];
                        unsigned  stride=arrpair.second;
                        for (int s=0; s<std::min(stride,2u); ++s) {
                            current.uv[s]=arrpair.first[idx*stride+s];
                        }
                    }
                }
                    
            }
                
            
            
        }
        
    }
    
    return ret;
}

std::pair<std::vector<float>, unsigned short> collada_loader::load_float_array(pugi::xml_node node, const char * idname)
{
    if(idname[0]=='#')idname++;
    pugi::xml_node source_or_ref = node.find_child_by_attribute("id", idname);
    if (source_or_ref)
    {
        if(std::strcmp(source_or_ref.name(),"source")==0)
        {
            pugi::xml_node arr=source_or_ref.child("float_array");
            if(arr){
                std::vector<float> float_arr(arr.attribute("count").as_ullong());
                unsigned short stride=arr.attribute("stride").as_uint();
                collada_loader::fill_array(arr, float_arr);
                return std::make_pair(float_arr, stride);
            }
        }else
        {
            pugi::xml_node input=source_or_ref.child("input");
            if(input)
            {
                return load_float_array(node, input.attribute("source").as_string());
            }
        }
        
    }
    
    return std::make_pair(std::vector<float>(),0);
}


