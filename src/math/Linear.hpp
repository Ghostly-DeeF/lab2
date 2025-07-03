#ifndef SGE_SRC_MATH_LINEAR_HPP_
#define SGE_SRC_MATH_LINEAR_HPP_

#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sge::math
{
    using vec3 = glm::vec3;
    using vec4 = glm::vec4;

    using mat4 = glm::mat4;
    
    inline mat4 translate(const mat4& m, const vec3& v)
    {
        return glm::translate(m, v);
    }

}

#endif
