#include "sge/Application.hpp"

#include "sge/Logger.hpp"

namespace sge
{

    Application::Application()
        : m_window("Sge app", 1024, 1024)
    {
        log::info("Application Constructor");
        setAllCallbacks();
    }
    
    Application::Application(const char* title)
        : m_window(title, 1024, 1024)
    {
        log::info("Application Constructor");
        setAllCallbacks();
    }
    
    Application::Application(const char* title, size_t width, size_t height)
        : m_window(title, width, height)
    {
        log::info("Application Constructor");
        setAllCallbacks();
    }


    Application::Application(Application &&moved) noexcept
        : m_window(std::move(moved.m_window))
    {}
    
    Application &Application::operator=(Application &&moved) noexcept
    {
        if (&moved == this)
            return *this;

        m_window = std::move(moved.m_window);
    
        return *this;
    }


    void Application::start()
    {
        log::info("App start");
        while(m_window.is_active())
        {
            m_window.update();
            onUpdate();
        }
        m_window.shutdown();
    }

    void Application::setAllCallbacks()
    {
        m_window.setResizeCallback(
            [&](const windowSizeData& size_data)
            {
                userResizeCallback(size_data.width, size_data.height);
            }
        );

        m_window.setCursorCallback(
            [&](const cursorPos& cursor_pos)
            {
                userCursorCallback(cursor_pos.x, cursor_pos.y);
            }
        );
    }


    Application::~Application()
    {
        log::info("Application Destructor"); 
    }

}
