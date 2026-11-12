#ifndef SGE_TESTS_GLCONTEXT_HPP_
#define SGE_TESTS_GLCONTEXT_HPP_

namespace sge::test
{
    /**
     * @brief Creates a hidden OpenGL 3.3 core context and makes it current.
     *
     * The context is created lazily, at most once per process. It is used by
     * the tests that have to create real shader programs.
     *
     * @return true if a context is current, false if GLFW or GLAD could not be
     *         initialized (for example, there is no display or GL driver).
     */
    bool ensureGlContext();
}

#endif
