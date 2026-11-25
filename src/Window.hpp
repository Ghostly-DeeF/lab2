/**
 * @file Window.hpp

 * @author Ghostly-DeeF (moleg200@yandex.ru)
 * @brief Файл содержит описание класса Window
 * @version 0.0.1
 * @date 2026-10-25
 * 
 * @copyright Copyright (c) 2026
 * 
 * Файл содержит описание основного класса Window, который реализует окно.
 */
#ifndef SGE_WINDOW_HPP_
#define SGE_WINDOW_HPP_

#include "Events.hpp"
#include "KeyMap.hpp"
#include <string>

struct GLFWwindow;

/**
 * @brief Тип указателя на функцию загрузки адресов OpenGL.
 */
typedef void* (* GLaddr)(const char *name);

namespace sge
{
    /**
     * @class Window
     * @brief Класс управления окном приложения.
     *
     * Инкапсулирует создание и управление окном GLFW, обработку событий,
     * состояние клавиатуры и мыши, курсора, скролла, фокуса, а также
     * пользовательские callback-функции изменения размера окна и положения курсора.
     *
     * Класс поддерживает перемещение, но запрещает копирование.
     *
     * @warning Копирование объекта Window запрещено.
     * @note Метод update() должен вызываться в каждом кадре основного цикла приложения.
     */
    class Window
    {
    public:
        /**
         * @brief Конструирует новый объект окна.
         *
         * Создаёт окно с указанным заголовком, шириной и высотой.
         *
         * @param[in] title Заголовок окна.
         * @param[in] width Ширина окна.
         * @param[in] height Высота окна.
         *
         * @throw sge::errors::glfw_error Исключение при ошибке инициализации или создания окна GLFW.
         */
        Window(std::string title, size_t width, size_t height);

        /**
         * @brief Перемещающий конструктор.
         *
         * Переносит владение окном и внутренними данными из другого объекта.
         *
         * @param[in,out] other Перемещаемый объект окна.
         */
        Window(Window &&) noexcept;

        /**
         * @brief Копирующий конструктор удалён.
         */
        Window(const Window &) = delete;

        /**
         * @brief Перемещающий оператор присваивания.
         *
         * Переносит владение окном и внутренними данными из другого объекта.
         *
         * @param[in,out] other Перемещаемый объект окна.
         * @return Ссылка на текущий объект.
         */
        Window &operator=(Window &&) noexcept;

        /**
         * @brief Копирующий оператор присваивания удалён.
         */
        Window &operator=(const Window &) = delete;

        /**
         * @brief Уничтожает объект окна.
         *
         * Освобождает ресурсы окна и, при необходимости, завершает работу GLFW.
         */
        ~Window();

        /**
         * @brief Обновляет состояние окна и обрабатывает события.
         *
         * Должен вызываться в каждом кадре основного цикла приложения.
         */
        void update();

        /**
         * @brief Устанавливает режим вертикальной синхронизации.
         *
         * @param[in] status true — включить вертикальную синхронизацию, false — выключить.
         *
         * @note Метод объявлен как const, но изменяет состояние вертикальной синхронизации GLFW.
         */
        void setVSync(bool status) const;

        /**
         * @brief Проверяет, активно ли окно.
         *
         * @return true, если окно активно и должно продолжать работу.
         * @return false, если окно должно быть закрыто.
         */
        bool is_active() const noexcept;

        /**
         * @brief Возвращает текущую ширину окна.
         *
         * @return size_t Ширина окна.
         */
        size_t getWidth() const noexcept;

        /**
         * @brief Возвращает текущую высоту окна.
         *
         * @return size_t Высота окна.
         */
        size_t getHeight() const noexcept;

        /**
         * @brief Проверяет, находится ли окно в фокусе.
         *
         * @return true, если окно находится в фокусе.
         * @return false, если окно не находится в фокусе.
         */
        bool isFocused() const noexcept;

        /**
         * @brief Возвращает позицию курсора по оси X.
         *
         * @return double Позиция курсора по оси X.
         */
        double getCursorX() const noexcept;

        /**
         * @brief Возвращает позицию курсора по оси Y.
         *
         * @return double Позиция курсора по оси Y.
         */
        double getCursorY() const noexcept;

        /**
         * @brief Проверяет состояние нажатия клавиши клавиатуры.
         *
         * @param[in] key Клавиша клавиатуры.
         * @return true, если клавиша нажата.
         * @return false, если клавиша не нажата.
         *
         * @throw sge::errors::glfw_error Исключение при ошибке работы с GLFW.
         */
        bool keyPress(input::Keyboard key) const;

        /**
         * @brief Проверяет состояние нажатия кнопки мыши.
         *
         * @param[in] key Кнопка мыши.
         * @return true, если кнопка мыши нажата.
         * @return false, если кнопка мыши не нажата.
         *
         * @throw sge::errors::glfw_error Исключение при ошибке работы с GLFW.
         */
        bool keyPress(input::Mouse key) const;

        /**
         * @brief Возвращает значение скролла по оси X.
         *
         * @return double Значение скролла по оси X.
         */
        double getScrollX() const noexcept;

        /**
         * @brief Возвращает значение скролла по оси Y.
         *
         * @return double Значение скролла по оси Y.
         */
        double getScrollY() const noexcept;

        /**
         * @brief Завершает работу окна.
         *
         * Освобождает ресурсы окна и переводит объект в состояние завершения.
         */
        void shutdown();

        /**
         * @brief Проверяет, было ли окно завершено.
         *
         * @return true, если окно уже завершено.
         * @return false, если окно ещё не завершено.
         */
        bool is_shutdown() const noexcept;

        /**
         * @brief Возвращает функцию загрузки адресов OpenGL.
         *
         * @return GLaddr Указатель на функцию загрузки адресов OpenGL.
         */
        GLaddr getGlAddressFunc();

        /**
         * @brief Устанавливает пользовательский callback изменения размера окна.
         *
         * @param[in] resize_function Функция, вызываемая при изменении размера окна.
         */
        void setResizeCallback(const events::resizeCallback& resize_function);

        /**
         * @brief Устанавливает пользовательский callback положения курсора.
         *
         * @param[in] cursor_function Функция, вызываемая при изменении положения курсора.
         */
        void setCursorCallback(const events::cursorCallback& cursor_function);

    private:
        /**
         * @brief Внутренние данные окна.
         *
         * Хранит заголовок, размеры, состояние курсора, скролла, фокуса
         * и пользовательские callback-функции.
         */
        struct WindowData
        {
            std::string title = "";
            size_t width = 0;
            size_t height = 0;

            /**
             * @brief Данные положения курсора.
             */
            struct cursorData
            {
                double x = .0;
                double y = .0;
            };
            cursorData cursor = {.0, .0};

            /**
             * @brief Данные скролла.
             */
            struct scrollData
            {
                double x = .0;
                double y = .0;
            };
            scrollData scroll = {.0, .0};

            bool focused = true;
            events::resizeCallback custom_resize_function;
            events::cursorCallback custom_cursor_function;
        };

        GLFWwindow* m_pWindow = nullptr;
        WindowData m_data;
        bool m_isDestroy = false;

        static inline int m_glfwInitNum = 0;

        /**
         * @brief Регистрирует внутренний callback изменения размера окна.
         */
        void setResizeCallback();

        /**
         * @brief Регистрирует внутренний callback положения курсора.
         */
        void setCursorCallback();

        /**
         * @brief Регистрирует внутренний callback скролла.
         */
        void setScrollCallback();

        /**
         * @brief Регистрирует внутренний callback фокуса окна.
         */
        void setFocusCallback();
    };
}

#endif