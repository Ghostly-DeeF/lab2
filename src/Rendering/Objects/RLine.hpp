/**
 * @file RLine.hpp
 * @author Ghostly-DeeF (you@domain.com)
 * @brief 
 * @version 0.0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2025
 * 
 * Класс линии, подготовленный для отрисовки
 */
#ifndef SGE_SRC_RENDERING_OBJECT_RLINE_HPP_
#define SGE_SRC_RENDERING_OBJECT_RLINE_HPP_

#include "../ShaderProgram.hpp"
#include "sge/2dprimitives.hpp"
#include "../VertexArray.hpp"

namespace sge::rendering::object
{
    /**
     * @brief Класс линии
     * 
     * Класс, который отвечает за отрисовку геометрии 2D линии
     */
    class RLine {
    public:
        /**
         * @brief Конструирует новый объект RLine
         * 
         * Объект конструируется со статичными координатами {0, 0, 0}, {1, 0, 0} и цветами из полей @ref sge::geometry::objects2D::Line::start и @ref sge::geometry::objects2D::Line::end
         */
        RLine(sge::geometry::objects2D::Line, const std::shared_ptr<ShaderProgram>&);
        RLine(RLine &&) = default;
        RLine(const RLine &) = delete;
        RLine &operator=(RLine &&) = default;
        RLine &operator=(const RLine &) = delete;
        ~RLine() = default;

        /**
         * @brief Функция отрисовки объекта
         * 
         * @li Логика отрисовки:
         * 1. Проверка видимости линии в границах окна\n
         * 2. Если не изменились координаты начальной/конечной точек или размеры окна то\n
         *   2.1 Преобразование статичных координат в требуемые координаты системы окна\n
             2.2 Пересчет матрицы трансформации\n
         * 3. Установка параметров шейдера (матрица трансляции и динамический цвет) и отрисовка
         *
         * @param[in] window_width ширина экрана
         * @param[in] window_height высота экрана
         */
        void rendering(size_t window_width, size_t window_height);

        /**
         * @brief Возвращает объект Geometry
         * 
         * @return sge::geometry::objects2D::Line* геометрия линии
         */
        sge::geometry::objects2D::Line* getGeometry();

    private:
        sge::geometry::objects2D::Line m_geometry;
        VertexArray m_VAO;
        const std::shared_ptr<ShaderProgram> m_shader;

        math::mat4 m_transform = 1.0f;
        math::vec3 m_oldPosStart{-1.0f, -1.0f, -1.0f};
        math::vec3 m_oldPosEnd{-1.0f, -1.0f, -1.0f};
        math::vec2 m_oldWindowData{-1.0f, -1.0f};
    };    
}
#endif
