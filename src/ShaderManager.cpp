#include "ShaderManager.hpp"

#include <fstream>
#include "sge/Logger.hpp"

namespace sge
{

    ShaderManager::ShaderManager()
    {
        log::lifeTime log("ShaderManager", "Constructor");

        addSearchPath("/home/jumbo/Projects/C_projects/Test_OpeGL_Engine/external/sge/res/shaders/", false);
        add("basic 2d", "/2d/basic.vert", "2d/basic.frag");
    }

    rendering::ShaderProgram& ShaderManager::at(std::string_view name)
    {
        return m_shaders.at(name);
    }

    void ShaderManager::add(std::string_view name, std::string_view vertex_path, std::string_view frag_path)
    {
        std::string vert = foundPath(vertex_path);
        std::string frag = foundPath(frag_path);
        rendering::ShaderProgram shader(vert, frag);
        m_shaders.insert({name, shader});
        log::info("%s", vert.c_str());
        log::info("%s", frag.c_str());

    }

    std::string ShaderManager::foundPath(std::string_view rel_path) const
    { 
        for(auto path : paths)
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

        return " ";
    }

    void ShaderManager::addSearchPath(std::string_view path, bool recursive)
    {
        paths.push_back( {path.data(), recursive} );
    }

}
