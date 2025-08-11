#ifndef SGE_SRC_SHADERMANAGER_HPP_
#define SGE_SRC_SHADERMANAGER_HPP_

#include "Rendering/ShaderProgram.hpp"
#include <string_view>
#include <map>
#include <vector>

namespace sge
{

    class ShaderManager
    {
    public:
        ShaderManager();
        

        void push();
        rendering::ShaderProgram& at(std::string_view name);
        void add(std::string_view name, std::string_view vertex_path, std::string_view frag_path);

        void addSearchPath(std::string_view path, bool recursive);
        
    
    private:

        std::string foundPath(std::string_view rel_path) const;

        struct Path
        {
            const char* path = nullptr;
            bool recursive = false;
        };

        std::vector<Path> paths;
        std::map<std::string_view, rendering::ShaderProgram> m_shaders;
    };

}

#endif
