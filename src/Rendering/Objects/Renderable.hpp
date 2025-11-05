/**
 * @file Renderable.hpp
 * @author Ghostly-DeeF (you@domain.com)
 * @brief 
 * @version 0.0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2025
 * 
 * Файл подключает все классы объектов для отрисовки и устанавливает зависимости классов для отрисовки и классов геометрии
 */
#ifndef SGE_SRC_RENDERING_OBJECTS_RENDERABLE_HPP_
#define SGE_SRC_RENDERING_OBJECTS_RENDERABLE_HPP_

#include "RPoint.hpp"
#include "RLine.hpp"

namespace sge::rendering::objects
{
    template<typename T> struct corresponding_type;
    template<> struct corresponding_type<sge::geometry::objects2D::Point> { using type = sge::rendering::object::RPoint; };
    template<> struct corresponding_type<sge::geometry::objects2D::Line> { using type = sge::rendering::object::RLine; };
}

#endif
