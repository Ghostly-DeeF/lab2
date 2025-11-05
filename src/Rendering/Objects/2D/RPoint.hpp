/**
 * @file RPoint.hpp
 * @author Ghostly-DeeF (you@domain.com)
 * @brief 
 * @version 0.0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2025
 * 
 * Класс почки, подготовленный для отрисовки
 */
#ifndef SGE_SRC_RENDERING_OBJECTS_2D_RPOINT_HPP_
#define SGE_SRC_RENDERING_OBJECTS_2D_RPOINT_HPP_

#include "../../ShaderProgram.hpp"
#include "sge/2dprimitives.hpp"
#include "../../VertexArray.hpp"
#include "../../../math/Linear.hpp"

namespace sge::rendering::objects2D
{
    /**
     * @brief Класс точки
     * 
     * Класс, который отвечает за отрисовку геометрии 2D точки
     */
    class RPoint {
    public:
        /**
         * @brief Конструирует новый объект RPoint
         * 
         * Объект конструируется со статичными координатами {0, 0, 0}
         */
        RPoint(sge::geometry::objects2D::Point, const std::shared_ptr<ShaderProgram>&);
        RPoint(RPoint &&) = default;
        RPoint(const RPoint &) = delete;
        RPoint &operator=(RPoint &&) = default;
        RPoint &operator=(const RPoint &) = delete;
        ~RPoint() = default;

        /**
         * @brief 
         * @li Логика отрисовки:
         * 1. Проверка видимости линии в границах окна\n
         * 2. Если не изменились координаты начальной/конечной точек или размеры окна то\n
         *   2.1 Преобразование статичных координат в требуемые координаты системы окна\n
             2.2 Пересчет матрицы трансформации\n
         * 3. Установка параметров шейдера (матрица трансформации и динамический цвет) и отрисовка
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
        sge::geometry::objects2D::Point* getGeometry();

    private:
        sge::geometry::objects2D::Point m_geometry;
        VertexArray m_VAO;
        const std::shared_ptr<ShaderProgram> m_shader;

        math::mat4 m_transform = 1.0f;
        math::vec3 m_oldPos{-1.0f, -1.0f, -1.0f};
        math::vec2 m_oldWindowData{-1.0f, -1.0f};
        
    };    
}
#endif
