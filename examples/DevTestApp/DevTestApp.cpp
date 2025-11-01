#include <sge/Application.hpp>

class App: public sge::Application
{
public:
    App(const char* title) : Application(title)
    {
        scene.addShadersSearchPath("/home/jumbo/Projects/C_projects/sge/res/", true);

        point_1 = scene.addObject<sge::geometry::objects2D::Point>({{50.0f, 20.0f, 0.2f, {1.0f, 0.0f, 0.0f, 1.0f}}, 20}, "point basic 2d");
        line_1 = scene.addObject<sge::geometry::objects2D::Line>({{80.5f, 60.0f, 0.1f, {0.0f, 1.0f, 1.0f, 1.0f},},
                                                                  {160.1f, 120.0f, 0.2f, {1.0f, 0.0f, 1.0f, 1.0f}},
                                                                  {1.0f, 1.0f, 1.0f, 1.0f}, 5.0f}, "line basic 2d");
    }

    ~App() override {}

private:

    sge::geometry::objects2D::Point* point_1;
    sge::geometry::objects2D::Line* line_1;

    void onUpdate() override
    {
        point_1->vertex.x = cursorX();
        point_1->vertex.y = cursorY();

        line_1->end.x = cursorX();
        line_1->end.y = cursorY();
    }
};

int main()
{
    App app("DevTestApp");
    app.start();
    return 0;
}
