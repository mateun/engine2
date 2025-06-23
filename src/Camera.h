#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    enum class ProjectionType { Perspective, Orthographic };

    Camera();

    void set_projection_type(ProjectionType type);
    void set_perspective(float fov_y, float aspect, float near_z, float far_z);
    void set_orthographic(float left, float right, float bottom, float top, float near_z, float far_z);
    void set_position(const glm::vec3& pos);
    void set_look_at(const glm::vec3& target);
    void set_up(const glm::vec3& up);

    glm::mat4 get_view_matrix() const;
    glm::mat4 get_projection_matrix() const;
    glm::mat4 get_view_projection_matrix() const;

private:
    ProjectionType projection_type_ = ProjectionType::Perspective;
    // Perspective params
    float fov_y_ = glm::radians(60.0f);
    float aspect_ = 1.0f;
    float near_z_ = 0.1f;
    float far_z_ = 100.0f;
    // Ortho params
    float left_ = -1.0f, right_ = 1.0f, bottom_ = -1.0f, top_ = 1.0f;
    float ortho_near_z_ = 0.1f, ortho_far_z_ = 100.0f;
    // View params
    glm::vec3 position_ = glm::vec3(0, 0, 3);
    glm::vec3 look_at_ = glm::vec3(0, 0, 0);
    glm::vec3 up_ = glm::vec3(0, 1, 0);
}; 