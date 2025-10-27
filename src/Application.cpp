#include "Rendering/ShaderProgram.hpp"
#include "sge/Application.hpp"

#include "sge/2dprimitives.hpp"
#include "sge/SGEexception.hpp"

#include <chrono>

#include "sge/Logger.hpp"


namespace sge
{

    Application::Application()
        : m_window("Sge app", 1024, 1024), m_render(m_window.getGlAddressFunc())
    {
        log::constructor("Application");
        setAllCallbacks();
    }
    
    Application::Application(const char* title)
        : m_window(title, 1024, 1024), m_render(m_window.getGlAddressFunc())
    {
        log::constructor("Application"); 
        setAllCallbacks();
    
    }
    
    Application::Application(const char* title, size_t width, size_t height)
        : m_window(title, width, height), m_render(m_window.getGlAddressFunc())
    {
        log::constructor("Application");
        setAllCallbacks();
    }


    Application::Application(Application &&moved) noexcept
        : m_window(std::move(moved.m_window)), m_render(m_window.getGlAddressFunc())
    {}
    
    Application &Application::operator=(Application &&moved) noexcept
    {
        if (&moved == this)
            return *this;

        m_window = std::move(moved.m_window);
        m_render = std::move(moved.m_render);
        scene = std::move(moved.scene);
        m_frameTime = moved.m_frameTime;
        moved.m_frameTime = .0;
    
        return *this;
    }


    void Application::start()
    {
        log::lifeTime log("APP", "main loop");
        
    
        while(m_window.is_active())
        {
            auto start_time = std::chrono::high_resolution_clock::now();

            m_window.update();
            m_render.update();
            onUpdate();
            scene.rendering(); 

            m_frameTime = (std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start_time)).count();
        }

        
        m_window.shutdown();
    }

    void Application::setAllCallbacks()
    {
        m_window.setResizeCallback(
            [&](const events::windowSizeData& size_data)
            {
                m_render.setWindowSize(size_data.width, size_data.height);
                scene.setWindowSize(size_data.width, size_data.height);
                userResizeCallback(size_data.width, size_data.height);
            }
        );

        m_window.setCursorCallback(
            [&](const events::cursorPos& cursor_pos)
            {
                userCursorCallback(cursor_pos.x, cursor_pos.y);
            }
        );
    }

    void Application::setVSync(bool status) const
    {
        m_window.setVSync(status);
    }

    size_t Application::width() const noexcept
    {
        return m_window.getWidth();
    }

    size_t Application::height() const noexcept
    {
        return m_window.getHeight();
    }

    bool Application::isFocused() const noexcept
    {
        return m_window.isFocused();
    }

    double Application::getFrameTime() const noexcept
    {
        return m_frameTime;
    }

    double Application::getFrameRate() const noexcept
    {
        return 1000.0 / m_frameTime;
    }

    double Application::cursorX() const noexcept
    {
        return m_window.getCursorX();
    }

    double Application::cursorY() const noexcept
    {
        return m_window.getCursorY();
    }

    bool Application::keyPress(input::Keyboard key) const
    {
        return m_window.keyPress(key);
    }

    bool Application::keyPress(input::Mouse key) const
    {
        return m_window.keyPress(key);
    }

    double Application::scrollX() const noexcept
    {
        return m_window.getScrollX();
    }

    double Application::scrollY() const noexcept
    {
        return m_window.getScrollY();
    }

    Application::~Application()
    {
        log::destructor("Application Destructor"); 
    }

}
