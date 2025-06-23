#include "Camera.h"

Camera::Camera() {}

void Camera::set_projection_type(ProjectionType type) {
    projection_type_ = type;
}

void Camera::set_perspective(float fov_y, float aspect, float near_z, float far_z) {
    fov_y_ = fov_y;
    aspect_ = aspect;
    near_z_ = near_z;
    far_z_ = far_z;
    projection_type_ = ProjectionType::Perspective;
}

void Camera::set_orthographic(float left, float right, float bottom, float top, float near_z, float far_z) {
    left_ = left;
    right_ = right;
    bottom_ = bottom;
    top_ = top;
    ortho_near_z_ = near_z;
    ortho_far_z_ = far_z;
    projection_type_ = ProjectionType::Orthographic;
}

void Camera::set_position(const glm::vec3& pos) {
    position_ = pos;
}

void Camera::set_look_at(const glm::vec3& target) {
    look_at_ = target;
}

void Camera::set_up(const glm::vec3& up) {
    up_ = up;
}

glm::mat4 Camera::get_view_matrix() const {
    return glm::lookAt(position_, look_at_, up_);
}

glm::mat4 Camera::get_projection_matrix() const {
    glm::mat4 proj;
    if (projection_type_ == ProjectionType::Perspective) {
        proj = glm::perspective(fov_y_, aspect_, near_z_, far_z_);
    } else {
        proj = glm::ortho(left_, right_, bottom_, top_, ortho_near_z_, ortho_far_z_);
    }
    // Flip Y for Vulkan
    proj[1][1] *= -1;
    return proj;
}

glm::mat4 Camera::get_view_projection_matrix() const {
    return get_projection_matrix() * get_view_matrix();
} 