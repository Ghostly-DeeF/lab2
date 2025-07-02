#ifndef SGE_SRC_SHADERMANAGER_HPP_
#define SGE_SRC_SHADERMANAGER_HPP_

#include "Rendering/ShaderProgram.hpp"
#include <string_view>
#include <map>

namespace sge
{

    class ShaderManager
    {
    public:
        ShaderManager();
        

        void push();
        rendering::ShaderProgram& at(std::string_view name);
        
    
    private:
        std::map<std::string_view, rendering::ShaderProgram> m_shaders;
    };

}

#endif
