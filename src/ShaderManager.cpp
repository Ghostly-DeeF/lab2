#include "ShaderManager.hpp"

#include "sge/Logger.hpp"

namespace sge
{

    ShaderManager::ShaderManager()
    {
        log::lifeTime log("ShaderManager", "Constructor");

        rendering::ShaderProgram basic_2d("/home/jumbo/Projects/C_projects/Test_OpeGL_Engine/external/sge/res/shaders/2d/basic.vert", "/home/jumbo/Projects/C_projects/Test_OpeGL_Engine/external/sge/res/shaders/2d/basic.frag");

        m_shaders.insert({"basic 2d", basic_2d});
    }

    rendering::ShaderProgram& ShaderManager::at(std::string_view name)
    {
        return m_shaders.at(name);
    }

}
