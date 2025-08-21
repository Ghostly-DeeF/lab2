#include "ShaderManager.hpp"

#include "sge/SGEexception.hpp"
#include <fstream>
#include <algorithm>

#include "sge/Logger.hpp"

namespace sge
{

    ShaderManager::ShaderManager()
    {
        log::lifeTime log("ShaderManager", "Constructor");

        m_baseShadersInfo.emplace_back(ShaderInfo{"basic 2d", "/2d/basic.vert", "2d/basic.frag"} );

    }

    rendering::ShaderProgram& ShaderManager::at(std::string_view name)
    {
        auto it_loaded = m_shaders.find(name);
        if(it_loaded != m_shaders.end())
            return (*it_loaded).second;
        
        auto it_unloaded = std::find_if(m_baseShadersInfo.begin(), m_baseShadersInfo.end(),
                [&](const auto& data){ return data.name == name; });

        if(it_unloaded != m_baseShadersInfo.end())
            return ( *add( (*it_unloaded).name, (*it_unloaded).vert, (*it_unloaded).frag) ).second;

        sge::errors::shader_not_loaded("The shader was not found in the list of loaded shaders", name);

        return;
    }

    std::map<std::string_view, rendering::ShaderProgram>::iterator ShaderManager::add(std::string_view name, std::string_view vertex_path, std::string_view frag_path)
    {
        std::string vert = foundPath(vertex_path);
        std::string frag = foundPath(frag_path);
        rendering::ShaderProgram shader(vert, frag);
        log::info("%s", vert.c_str());
        log::info("%s", frag.c_str());
        return m_shaders.insert({name, shader}).first;
    }

    std::string ShaderManager::foundPath(std::string_view rel_path) const
    {
        for(auto path : m_paths)
        {
            std::string full_path = path.path;

            if ((full_path[full_path.length()-1] == '/' || full_path[full_path.length()-1] == '\\') && (rel_path[0] == '/' || rel_path[0] == '\\'))
            {
                full_path.erase(full_path.length()-1, 1);
            } else
            if (!(full_path[full_path.length()-1] == '/' || full_path[full_path.length()-1] == '\\' || rel_path[0] == '/' || rel_path[0] == '\\') )
            {
                full_path += '/';
            }
            
            full_path += rel_path;

            std::ifstream file(full_path);
            if(file.good())
                return full_path; 

            full_path.clear();
        }

        throw errors::shader_not_found("The shader file was not found", rel_path);
    }

    void ShaderManager::addSearchPath(std::string_view path, bool recursive)
    {
        m_paths.push_back( {path.data(), recursive} );
    }

}
