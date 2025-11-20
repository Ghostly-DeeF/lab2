#include "ShaderManager.hpp"

#include "Rendering/ShaderProgram.hpp"
#include "sge/SGEexception.hpp"
#include <filesystem>
#include <algorithm>

#include "sge/Logger.hpp"

namespace sge
{

    ShaderManager::ShaderManager()
    {
        log::lifeTime log("ShaderManager", "Constructor");

        m_baseShadersInfo.emplace_back(ShaderInfo{"point basic 2d", "2d_point_basic.vert", "2d_basic.frag"} );
        m_baseShadersInfo.emplace_back(ShaderInfo{"line basic 2d", "2d_line_basic.vert", "2d_basic.frag"} );


    }

    std::shared_ptr<rendering::ShaderProgram> ShaderManager::at(std::string_view name)
    {
        auto it_loaded = m_shaders.find(name);
        if(it_loaded != m_shaders.end())
            return (*it_loaded).second;
        
        auto it_unloaded = std::find_if(m_baseShadersInfo.begin(), m_baseShadersInfo.end(),
                [&](const auto& data){ return data.name == name; });

        if(it_unloaded != m_baseShadersInfo.end())
            return ( *add( (*it_unloaded).name, (*it_unloaded).vert, (*it_unloaded).frag) ).second;

        sge::errors::shader_not_loaded("The shader was not found in the list of loaded shaders", name);
        return nullptr;
    }

    std::map<std::string_view, std::shared_ptr<rendering::ShaderProgram>>::iterator ShaderManager::add(std::string_view name, std::string_view vertex_path, std::string_view frag_path)
    {
        std::string vert = foundPath(vertex_path);
        std::string frag = foundPath(frag_path);
        //log::info("%s", vert.c_str());
        //log::info("%s", frag.c_str());
        return m_shaders.insert({name, std::make_shared<rendering::ShaderProgram>(vert, frag)}).first;
    }

    std::string ShaderManager::foundPath(std::string_view rel_path) const
    {
        for(auto path : m_paths)
        {

            if(path.recursive)
            {
                for (const auto& entry : std::filesystem::recursive_directory_iterator(path.path))
                {
                    //log::info("%s  %s", entry.path().c_str(), rel_path.data());
                    if (entry.is_regular_file() &&
                        !entry.is_directory() &&
                        !entry.is_symlink() &&
                        entry.path().filename() == rel_path)
                    { 
                        return entry.path();
                    }
                }
            }
            else
            {
                for (const auto& entry : std::filesystem::directory_iterator(path.path))
                {
                    //log::info("%s  %s", entry.path().c_str(), rel_path.data());
                    if (entry.is_regular_file() &&
                        !entry.is_directory() &&
                        !entry.is_symlink() &&
                        entry.path().filename() == rel_path)
                    { 
                        return entry.path();
                    }
                }
            }

        }

        throw errors::shader_not_found("The shader file was not found", rel_path);
    }

    void ShaderManager::addSearchPath(std::string_view path, bool recursive)
    {
        m_paths.push_back( {path.data(), recursive} );
    }

}
