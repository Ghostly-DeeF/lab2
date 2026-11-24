#include <gtest/gtest.h>

#include "GlContext.hpp"
#include "Rendering/ShaderProgram.hpp"
#include "ShaderManager.hpp"

#include <sge/SGEexception.hpp>

#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace
{
    namespace fs = std::filesystem;

    using sge::ShaderManager;
    using sge::errors::glsl_compile_error;
    using sge::errors::shader_not_found;

#ifndef SGE_TEST_SHADERS_DIR
#error "SGE_TEST_SHADERS_DIR has to be defined by CMake"
#endif


    constexpr const char* kShadersDir = SGE_TEST_SHADERS_DIR;
    constexpr const char* kFlatShadersDir = SGE_TEST_SHADERS_DIR "/2d";

    constexpr const char* kPointBaseShader = "point basic 2d";
    constexpr const char* kLineBaseShader = "line basic 2d";

    constexpr const char* kPointVertex = "2d_point_basic.vert";
    constexpr const char* kLineVertex = "2d_line_basic.vert";
    constexpr const char* kFragment = "2d_basic.frag";

    class TempDir
    {
    public:
        TempDir()
        {
            static std::atomic<unsigned> counter{0};

            const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
            m_path = fs::temp_directory_path() /
                     ("sge_shader_manager_test_" + std::to_string(stamp) + "_" + std::to_string(counter++));

            fs::create_directories(m_path);
        }

        ~TempDir()
        {
            std::error_code ec;
            fs::remove_all(m_path, ec);
        }

        TempDir(const TempDir&) = delete;
        TempDir& operator=(const TempDir&) = delete;

        const fs::path& path() const { return m_path; }

        fs::path write(const std::string& relative_path, std::string_view content) const
        {
            const fs::path file = m_path / relative_path;

            fs::create_directories(file.parent_path());

            std::ofstream out(file, std::ios::binary);
            out << content;

            return file;
        }

    private:
        fs::path m_path;
    };

    void copyShader(const TempDir& dir, const char* name)
    {
        fs::copy_file(fs::path(kFlatShadersDir) / name, dir.path() / name, fs::copy_options::overwrite_existing);
    }

    class ShaderManagerTest : public ::testing::Test
    {
    protected:
        ShaderManager m_manager;
    };

    class ShaderManagerGlTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            if (!sge::test::ensureGlContext())
                GTEST_SKIP() << "OpenGL context is not available";
        }

        ShaderManager m_manager;
    };


    TEST_F(ShaderManagerTest, AtUnknownShaderReturnsNullptr)
    {
        const std::string name = "unknown shader";

        EXPECT_EQ(m_manager.at(name), nullptr);
    }

    TEST_F(ShaderManagerTest, AtEmptyNameReturnsNullptr)
    {
        EXPECT_EQ(m_manager.at(""), nullptr);
    }

    TEST_F(ShaderManagerTest, AtBaseShaderWithoutSearchPathsThrowsNotFound)
    {
        EXPECT_THROW(m_manager.at(kPointBaseShader), shader_not_found);
    }

    TEST_F(ShaderManagerTest, AtBaseShaderWithEmptySearchPathThrowsNotFound)
    {
        TempDir dir;
        const std::string dir_path = dir.path().string();

        m_manager.addSearchPath(dir_path, false);

        EXPECT_THROW(m_manager.at(kPointBaseShader), shader_not_found);
    }

    TEST_F(ShaderManagerTest, FailedAddDoesNotRegisterShader)
    {
        const std::string name = "custom shader";

        EXPECT_THROW(m_manager.add(name, "custom.vert", "custom.frag"), shader_not_found);

        // The failed add() must not leave a half-registered shader behind.
        EXPECT_EQ(m_manager.at(name), nullptr);
    }

    TEST_F(ShaderManagerTest, AddWithoutSearchPathsReportsMissingVertexFile)
    {
        const std::string vertex = "custom.vert";

        try
        {
            m_manager.add("custom shader", vertex, "custom.frag");
            FAIL() << "add() has to throw when the vertex file is missing";
        }
        catch (const shader_not_found& error)
        {
            EXPECT_STREQ(error.path(), vertex.c_str());
        }
    }

    TEST_F(ShaderManagerTest, AddReportsMissingFragmentFile)
    {
        TempDir dir;
        dir.write(kPointVertex, "// the source is never compiled, the fragment file is missing\n");

        const std::string dir_path = dir.path().string();
        m_manager.addSearchPath(dir_path, false);

        const std::string fragment = "missing.frag";

        try
        {
            m_manager.add("custom shader", kPointVertex, fragment);
            FAIL() << "add() has to throw when the fragment file is missing";
        }
        catch (const shader_not_found& error)
        {
            EXPECT_STREQ(error.path(), fragment.c_str());
        }
    }

    TEST_F(ShaderManagerTest, SearchIsCaseSensitive)
    {
        TempDir dir;
        dir.write("CaseSensitive.vert", "// source is irrelevant\n");

        const std::string dir_path = dir.path().string();
        m_manager.addSearchPath(dir_path, false);

        EXPECT_THROW(m_manager.add("custom shader", "casesensitive.vert", "custom.frag"), shader_not_found);
    }

    TEST_F(ShaderManagerTest, FlatSearchDoesNotDescendIntoSubdirectories)
    {
        // The base shaders live in res/shaders/2d, so a non-recursive search
        // over res/shaders must not find them.
        m_manager.addSearchPath(kShadersDir, false);

        EXPECT_THROW(m_manager.at(kPointBaseShader), shader_not_found);
    }

    TEST_F(ShaderManagerTest, MissingSearchPathThrowsFilesystemError)
    {
        TempDir dir;
        const std::string missing_dir = (dir.path() / "does_not_exist").string();

        m_manager.addSearchPath(missing_dir, false);

        EXPECT_THROW(m_manager.add("custom shader", "custom.vert", "custom.frag"), fs::filesystem_error);
    }

    TEST_F(ShaderManagerGlTest, LoadsBaseShaderFromSearchPath)
    {
        m_manager.addSearchPath(kFlatShadersDir, false);

        const auto shader = m_manager.at(kPointBaseShader);

        ASSERT_NE(shader, nullptr);
        shader->use();
    }

    TEST_F(ShaderManagerGlTest, CachesLoadedShader)
    {
        m_manager.addSearchPath(kFlatShadersDir, false);

        const auto first = m_manager.at(kPointBaseShader);
        const auto second = m_manager.at(kPointBaseShader);

        ASSERT_NE(first, nullptr);
        EXPECT_EQ(first, second);
    }

    TEST_F(ShaderManagerGlTest, LoadsDistinctBaseShaders)
    {
        m_manager.addSearchPath(kFlatShadersDir, false);

        const auto point = m_manager.at(kPointBaseShader);
        const auto line = m_manager.at(kLineBaseShader);

        ASSERT_NE(point, nullptr);
        ASSERT_NE(line, nullptr);
        EXPECT_NE(point, line);
    }

    TEST_F(ShaderManagerGlTest, LoadsExplicitlyAddedShader)
    {
        m_manager.addSearchPath(kFlatShadersDir, false);

        const auto it = m_manager.add("custom shader", kPointVertex, kFragment);

        EXPECT_EQ(it->first, "custom shader");
        ASSERT_NE(it->second, nullptr);
        EXPECT_EQ(m_manager.at("custom shader"), it->second);
    }

    TEST_F(ShaderManagerGlTest, RecursiveSearchFindsShaderInSubdirectory)
    {
        m_manager.addSearchPath(kShadersDir, true);

        EXPECT_NE(m_manager.at(kPointBaseShader), nullptr);
    }

    TEST_F(ShaderManagerGlTest, FirstSearchPathWins)
    {
        TempDir first;
        TempDir second;

        copyShader(first, kPointVertex);
        copyShader(first, kFragment);

        second.write(kPointVertex, "#version 330 core\nthis is not valid glsl\n");
        copyShader(second, kFragment);

        const std::string first_path = first.path().string();
        const std::string second_path = second.path().string();

        m_manager.addSearchPath(first_path, false);
        m_manager.addSearchPath(second_path, false);

        // The first search path contains valid sources while the second one
        // does not, so a successful load proves that the first path was used.
        EXPECT_NO_THROW(m_manager.add("custom shader", kPointVertex, kFragment));
        EXPECT_NE(m_manager.at("custom shader"), nullptr);
    }

    TEST_F(ShaderManagerGlTest, InvalidShaderPropagatesCompileError)
    {
        TempDir dir;
        dir.write(kPointVertex, "#version 330 core\nvoid main() { this is not glsl; }\n");
        copyShader(dir, kFragment);

        const std::string dir_path = dir.path().string();
        m_manager.addSearchPath(dir_path, false);

        EXPECT_THROW(m_manager.add("broken shader", kPointVertex, kFragment), glsl_compile_error);

        // A shader that failed to compile must not be registered.
        EXPECT_EQ(m_manager.at("broken shader"), nullptr);
    }

    TEST_F(ShaderManagerGlTest, FailedLoadIsNotCached)
    {
        EXPECT_THROW(m_manager.at(kPointBaseShader), shader_not_found);

        m_manager.addSearchPath(kFlatShadersDir, false);

        EXPECT_NE(m_manager.at(kPointBaseShader), nullptr);
    }


    TEST_F(ShaderManagerTest, AvailableShadersListsBuiltInShaders)
    {
        const auto shaders = m_manager.availableShaders();

        EXPECT_NE(std::find(shaders.begin(), shaders.end(), kPointBaseShader), shaders.end());
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), kLineBaseShader),  shaders.end());
    }

    TEST_F(ShaderManagerTest, AvailableShadersDoesNotRequireFiles)
    {
        EXPECT_FALSE(m_manager.availableShaders().empty());
    }

    TEST_F(ShaderManagerTest, RegisterShaderAddsToRegistry)
    {
        const std::string name = "custom shader";
        const auto before = m_manager.availableShaders().size();

        EXPECT_TRUE(m_manager.registerShader(name, "custom.vert", "custom.frag"));

        const auto shaders = m_manager.availableShaders();
        EXPECT_EQ(shaders.size(), before + 1);
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), name), shaders.end());
    }

    TEST_F(ShaderManagerTest, RegisterShaderSupportsMultipleNewShaders)
    {
        ASSERT_TRUE(m_manager.registerShader("A", "a.vert", "a.frag"));
        ASSERT_TRUE(m_manager.registerShader("B", "b.vert", "b.frag"));
        ASSERT_TRUE(m_manager.registerShader("C", "c.vert", "c.frag"));

        const auto shaders = m_manager.availableShaders();
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), "A"), shaders.end());
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), "B"), shaders.end());
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), "C"), shaders.end());
    }

    TEST_F(ShaderManagerTest, RegisterShaderUpdatesExistingEntry)
    {
        const auto before = m_manager.availableShaders().size();

        EXPECT_FALSE(m_manager.registerShader(kPointBaseShader, "other.vert", "other.frag"));

        EXPECT_EQ(m_manager.availableShaders().size(), before);
    }

    TEST_F(ShaderManagerTest, RegisterShaderDoesNotDuplicateNames)
    {
        m_manager.registerShader(kPointBaseShader, "a.vert", "a.frag");
        m_manager.registerShader(kPointBaseShader, "b.vert", "b.frag");

        const auto shaders = m_manager.availableShaders();
        EXPECT_EQ(std::count(shaders.begin(), shaders.end(), kPointBaseShader), 1);
    }

    TEST_F(ShaderManagerTest, RegisterShaderEmptyNameDoesNotMutateRegistry)
    {
        const auto before = m_manager.availableShaders();

        EXPECT_THROW(m_manager.registerShader("", "x.vert", "x.frag"), std::invalid_argument);

        EXPECT_EQ(m_manager.availableShaders(), before);
    }

    TEST_F(ShaderManagerTest, RegisterShaderIsCaseSensitive)
    {
        EXPECT_TRUE(m_manager.registerShader("Shader", "s.vert", "s.frag"));
        EXPECT_TRUE(m_manager.registerShader("shader", "s.vert", "s.frag"));

        const auto shaders = m_manager.availableShaders();
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), "Shader"), shaders.end());
        EXPECT_NE(std::find(shaders.begin(), shaders.end(), "shader"), shaders.end());
    }

    TEST_F(ShaderManagerTest, RegisteredShaderStillFailsToLoadWithoutFiles)
    {
        ASSERT_TRUE(m_manager.registerShader("ghost", "ghost.vert", "ghost.frag"));

        // Регистрация ≠ загрузка: при отсутствии search path загрузка падает.
        EXPECT_THROW(m_manager.at("ghost"), shader_not_found);
    }
}
