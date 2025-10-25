/**
 * @file Application.hpp

 * @author Ghostly-DeeF (you@domain.com)
 * @brief Файл содержит описание основного класса Application
 * @version 0.0.1
 * @date 2025-10-16
 * 
 * @copyright Copyright (c) 2025
 * 
 * Файл содержит описание основного класса Application, который реализует основные функции работы с приложением.
 */
#ifndef SGE_INCLUDE_SGE_APPLICATION_HPP_
#define SGE_INCLUDE_SGE_APPLICATION_HPP_

#include "../../src/Window.hpp"
#include "../../src/Scene.hpp"
#include "../../src/GlRender.hpp"

namespace sge
{
    /**
     * @brief Главный класс приложения
     * 
     * Главный класс приложения, который реализует основные функции
     * @li Пример использования:
     * @code {C++}
     * class UserApp : public sge::Application {
     * public:
     *     UserApp(const char* title) : Application(title) {}
     * private:
     *     void onUpdate() override {
     *         sge::log::info("User Update");
     *     }
     * }
     * 
     * int main() {
     *     UserApp app("User App Title");
     *     app.start();
     * }
     * @endcode
     */
    class Application
    {
    public:
        /**
         * @brief Конструирует новый объект приложения
         * 
         * Коструктор по умолчанию.\n
         * Новый объект создается с названием "Sge app" и размером 1024x1024px
         * @throw sge::errors::gl_error Исключение класса, реализующего рендеринг
         * @throw sge::errors::glfw_error Исключение класса, реализующего окно
         */
        Application();

        /**
         * @brief Конструирует новый объект приложения
         * 
         * Новый объект создается с названием @p title и размером 1024x1024px
         * @param[in] title Название окна
         * @throw sge::errors::gl_error Исключение класса, реализующего рендеринг
         * @throw sge::errors::glfw_error Исключение класса, реализующего окно
         */
        Application(const char* title);

        /**
         * @brief Конструирует новый объект приложения
         * 
         * Новый объект создается с названием @p title шириной @p width и высотой @p height
         * @param[in] title Название окна
         * @param[in] width Ширина окна
         * @param[in] height Высота окна
         * @throw sge::errors::gl_error Исключение класса, реализующего рендеринг
         * @throw sge::errors::glfw_error Исключение класса, реализующего окно
         */
        Application(const char* title, size_t width, size_t height);

        
        Application(Application &&) noexcept;
        Application(const Application &) = delete;
        Application &operator=(Application &&) noexcept;
        Application &operator=(const Application &) = delete;

        /**
         * @brief Удаляет объект Application
         * 
         * Виртуальный деструктор для удаления объекта
         */
        virtual ~Application();
    
        /**
         * @brief Метод запуска приложения
         * 
         * Запускает приложение. При запуске начинает работать основной цикл приложения.\n
         * Порядок обновления компонентов:
         *  @li обновление окна @ref Window::update();
         *  @li обновление рендера @ref GlRender::update;
         *  @li выполнение пользовательской функции @ref Application::onUpdate();
         *  @li рендеринг объектов на сцене @ref Scene::rendering(std::size_t windows_width, std::size_t window_height);
         */
        void start();

        void setVSync(bool status) const;

        /**
         * @brief Получение ширины окна
         * 
         * @return size_t Ширина окна
         */
        size_t width() const noexcept;

        /**
         * @brief Получение высоты окна
         * 
         * @return size_t Высота окна
         */
        size_t height() const noexcept;

        /**
         * @brief Получение состояния фокуса окна
         * 
         * @return true Окно находится в фокусе
         * @return false Окно находится не в фокусе
         */
        bool isFocused() const noexcept;

        double getFrameTime() const noexcept;
        double getFrameRate() const noexcept;

        /**
         * @brief Получение позиции мыши по оси X
         * 
         * @return double Позиция мыши по оси X
         */
        double cursorX() const noexcept;

        /**
         * @brief Получение позиции мыши по оси Y
         * 
         * @return double Позиция мыши по оси Y
         */
        double cursorY() const noexcept;

        /**
         * @brief Получение состояния нажатия кнопки на клавиатуре
         * 
         * @param[in] key Кнопка на клавиатуре
         * @return true Кнопка нажата
         * @return false Кнопка не нажата
         * @throw sge::errors::glfw_error Исключение из библиотеки, реализующей окно
         */
        bool keyPress(input::Keyboard key) const;

        /**
         * @brief Получение состояния нажатия кнопки на мышке
         * 
         * @param[in] key Кнопка на мышке
         * @return true Кнопка нажата
         * @return false Кнопка не нажата
         * @throw sge::errors::glfw_error Исключение из библиотеки, реализующей окно
         */
        bool keyPress(input::Mouse key) const;

        /**
         * @brief Получение скролла по оси X
         * 
         * @return double Скролл по оси X
         */
        double scrollX() const noexcept;

        /**
         * @brief Получение скролла по оси X
         * 
         * @return double Скролл по оси X
         */
        double scrollY() const noexcept;

    private:
        Window m_window;
        GlRender m_render;

    public:

        /**
         * @brief Класс сцены
         * 
         * Класс содержит в себе функции для управления объектами на сцене.
         */
        Scene scene;
        
        
    private:

        double m_frameTime = .0;
        
        /**
         * @brief Пользовательский метод обновления
         * 
         * Виртуальный метод, который позволяет пользователю добавить свою логику в цикл обновления приложения.\n
         * Данный метод вызывается в функции @ref Application::start()
         */
        virtual void onUpdate() = 0;

        /**
         * @brief Callback для обработки изменения размера экрана
         * 
         * Метод вызывается автоматически при изменении размера экрана.\n
         * По умолчанию callback не содержит никакого тела функции
         * @param[in] width Ширина экрана
         * @param[in] height Высота экрана
         */
        virtual void userResizeCallback(size_t width, size_t height) {};

        /**
         * @brief Callback для обработки положения мыши
         * 
         * Метод вызывается автоматически при изменении положения мыши.\n
         * По умолчанию callback не содержит никакого тела функции
         * @param[in] xpos Положение мыши по оси X
         * @param[in] ypos Положение мыши по оси Y
         */
        virtual void userCursorCallback(double xpos, double ypos) {};

        void setAllCallbacks();
        
    };
}

#endif
