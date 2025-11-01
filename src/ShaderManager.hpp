#ifndef SGE_SRC_SHADERMANAGER_HPP_
#define SGE_SRC_SHADERMANAGER_HPP_

namespace sge::rendering
{
    class ShaderProgram;
}
#include <string_view>
#include <map>
#include <vector>
#include <memory>

namespace sge
{

    class ShaderManager
    {
    public:
        ShaderManager();
        

        void push();
        std::shared_ptr<rendering::ShaderProgram>& at(std::string_view name);
        std::map<std::string_view, std::shared_ptr<rendering::ShaderProgram>>::iterator add(std::string_view name, std::string_view vertex_path, std::string_view frag_path);

        void addSearchPath(std::string_view path, bool recursive);
        
    
    private:

        std::string foundPath(std::string_view rel_path) const;

        struct ShaderInfo
        {
            const char* name = "";
            const char* vert = "";
            const char* frag = "";
        };

        struct Path
        {
            const char* path = nullptr;
            bool recursive = false;
        };
        
        std::vector<ShaderInfo> m_baseShadersInfo;
        std::vector<Path> m_paths;
        std::map<std::string_view, std::shared_ptr<rendering::ShaderProgram>> m_shaders;
    };

}

#endif
