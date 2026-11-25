/**
 * @file Events.hpp
 *
 * @author Ghostly-DeeF (moleg200@yandex.ru)
 * @brief Файл содержит описание типов данных и callback-функций для обработки событий окна
 * @version 0.0.1
 * @date 2026-10-25
 *
 * @copyright Copyright (c) 2026
 *
 * Файл содержит описание структур данных, используемых для передачи
 * параметров событий окна (размер окна, положение курсора), а также
 * псевдонимов типов callback-функций, вызываемых при возникновении
 * соответствующих событий.
 */
#ifndef SGE_EVENTS_HPP_
#define SGE_EVENTS_HPP_

#include <functional>

namespace sge::events
{
    /**
     * @struct windowSizeData
     * @brief Данные о размере окна.
     *
     * Хранит ширину и высоту окна, передаваемые в callback изменения размера.
     */
    struct windowSizeData
    {
        size_t width = 0;   /**< Ширина окна. */
        size_t height = 0;  /**< Высота окна. */
    };

    /**
     * @struct cursorPos
     * @brief Данные о положении курсора.
     *
     * Хранит координаты курсора по осям X и Y, передаваемые в callback
     * изменения положения курсора.
     */
    struct cursorPos
    {
        double x = 0; /**< Положение курсора по оси X. */
        double y = 0; /**< Положение курсора по оси Y. */
    };

    /**
     * @brief Тип callback-функции изменения размера окна.
     *
     * Функция вызывается при изменении размера окна и получает
     * актуальные размеры в виде структуры @ref windowSizeData.
     */
    using resizeCallback = std::function<void(const windowSizeData&)>;

    /**
     * @brief Тип callback-функции изменения положения курсора.
     *
     * Функция вызывается при изменении положения курсора и получает
     * актуальные координаты в виде структуры @ref cursorPos.
     */
    using cursorCallback = std::function<void(const cursorPos&)>;
}

#endif