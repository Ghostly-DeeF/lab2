/**
 * @file ShaderManager.hpp

 * @author Ghostly-DeeF (moleg200@yandex.ru)
 * @brief Файл содержит описание класса ShaderManager
 * @version 0.0.1
 * @date 2026-10-25
 * 
 * @copyright Copyright (c) 2026
 * 
 * Файл содержит описание класса ShaderManager, который управляет загруженными шейдерами.
 */
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

    /**
     * @class ShaderManager
     * @brief Класс для управления, загрузки и хранения шейдерных программ.
     * 
     * Предоставляет интерфейс для поиска файлов шейдеров по указанным путям,
     * их компиляции и кэширования для дальнейшего использования в рендеринге.
     */
    class ShaderManager
    {
    public:
        ShaderManager();
        

        void push();

        /**
         * @brief Получает шейдерную программу по её имени.
         * @param name Имя шейдера.
         * @return Умный указатель на шейдерную программу (std::shared_ptr<rendering::ShaderProgram>).
         */
        std::shared_ptr<rendering::ShaderProgram> at(std::string_view name);

        /**
         * @brief Тип словаря для хранения шейдерных программ по их именам.
         * Используется прозрачный компаратор std::less<> для поиска по std::string_view.
         */
        using ShaderMap = std::map<std::string, std::shared_ptr<rendering::ShaderProgram>, std::less<>>;
        
        /**
         * @brief Добавляет новый шейдер в менеджер.
         * @param name Имя шейдера для идентификации.
         * @param vertex_path Путь к файлу вершинного шейдера.
         * @param frag_path Путь к файлу фрагментного шейдера.
         * @return Итератор на добавленный элемент в словаре ShaderMap.
         */
        ShaderMap::iterator add(std::string_view name, std::string_view vertex_path, std::string_view frag_path);

        /**
         * @brief Добавляет путь в список директорий для поиска файлов шейдеров.
         * @param path Путь к директории.
         * @param recursive Флаг, указывающий, нужно ли искать рекурсивно во вложенных папках.
         */
        void addSearchPath(std::string_view path, bool recursive);
        
        /**
         * @brief Регистрирует информацию о шейдере для последующей загрузки.
         * @param name Имя шейдера.
         * @param vertex_path Путь к вершинному шейдеру.
         * @param frag_path Путь к фрагментному шейдеру.
         * @return true, если регистрация прошла успешно, иначе false.
         */
        bool registerShader(std::string_view name, std::string_view vertex_path, std::string_view frag_path);
        
        /**
         * @brief Возвращает список имен всех доступных (зарегистрированных) шейдеров.
         * @return Вектор строк с именами шейдеров.
         */
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
