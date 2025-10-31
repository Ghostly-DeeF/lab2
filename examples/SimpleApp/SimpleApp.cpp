#include <sge/Application.hpp>

class App: public sge::Application
{
public:
    App(const char* title) : Application(title) {}

    ~App() override {}

private:
    void onUpdate() override
    {
    
    }
};

int main()
{
    App app("app1");
    app.start();
    return 0;
}
