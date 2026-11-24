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
#include <string>
#include <functional>

namespace sge
{

    class ShaderManager
    {
    public:
        ShaderManager();
        

        void push();
        std::shared_ptr<rendering::ShaderProgram> at(std::string_view name);
        using ShaderMap = std::map<std::string, std::shared_ptr<rendering::ShaderProgram>, std::less<>>;
        ShaderMap::iterator add(std::string_view name, std::string_view vertex_path, std::string_view frag_path);

        void addSearchPath(std::string_view path, bool recursive);
        bool registerShader(std::string_view name, std::string_view vertex_path, std::string_view frag_path);
        std::vector<std::string> availableShaders() const;
        
    
    private:

        std::string foundPath(std::string_view rel_path) const;

        struct ShaderInfo
        {
            std::string name;
            std::string vert;
            std::string frag;
        };

        struct Path
        {
            std::string path;
            bool recursive = false;
        };
        
        std::vector<ShaderInfo> m_baseShadersInfo;
        std::vector<Path> m_paths;
        ShaderMap m_shaders;
    };

}

#endif
