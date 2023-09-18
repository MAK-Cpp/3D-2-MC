// Include standard headers
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

// Include GLEW
#include "GL/glew.h"

// Include GLFW
#include "GLFW/glfw3.h"

// Include GLM
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "shader.hpp"

// figures
#include "figures/cube.h"

static std::filesystem::path const PROJECT_DIR(PROJECT_SOURCE_DIR);
static std::filesystem::path const FRAGMENT_SHADERS_DIR = PROJECT_DIR / "shaders/fragment shaders/";
static std::filesystem::path const VERTEX_SHADERS_DIR   = PROJECT_DIR / "shaders/vertex shaders/";

std::ostream &operator<<(std::ostream &op, const glm::mat4 &mat) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            op << mat[x][y] << ' ';
        }
        op << '\n';
    }
    return op;
}

template <int T>
std::ostream &operator<<(std::ostream &op, glm::vec<T, float, glm::defaultp> const &vec) {
    op << '{';
    for (int i = 0; i < vec.length() - 1; ++i) {
        op << vec[i] << "; ";
    }
    op << vec[vec.length() - 1] << '}';
    return op;
}

glm::vec3 VectorMultiply(const glm::vec3 &a, const glm::vec3 &b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}

template <int T>
GLfloat ScalarMultiply(glm::vec<T, float, glm::defaultp> const &a, glm::vec<T, float, glm::defaultp> const &b) {
    float ans = 0;
    for (int i = 0; i < a.length(); ++i)
        ans += a[i] * b[i];
    return ans;
}

template <int T>
GLfloat VectorLength(glm::vec<T, float, glm::defaultp> const &vec) {
    return std::sqrt(ScalarMultiply(vec, vec));
}

template <int T>
float AngleBetweenVectors(glm::vec<T, float, glm::defaultp> const &a, glm::vec<T, float, glm::defaultp> const &b) {
    return ScalarMultiply(a, b) / (VectorLength(a) * VectorLength(b));
}

glm::vec3 Vec4To3(const glm::vec4 &to_3) {
    return {to_3[0], to_3[1], to_3[2]};
}

glm::vec4 Vec3To4(const glm::vec3 &to_4, const float end = 0) {
    return {to_4[0], to_4[1], to_4[2], end};
}

glm::vec3 RotateVec3(const glm::vec3 &vec_to_rotate, glm::f32 angle, const glm::highp_vec3 &axis, const float end = 0) {
    glm::vec4 result = glm::rotate(angle, axis) * Vec3To4(vec_to_rotate, end);
    return Vec4To3(result);
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {}

void CursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {}

std::pair<GLuint, GLuint> GetResolution() {
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return {mode->width, mode->height};
}

int main(int argc, char **argv) {
    // Initialise GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        getchar();
        return -1;
    }

    //    constexpr int kWidth  = 800;
    //    constexpr int kHeight = 600;
    const auto [kWidth, kHeight]      = GetResolution();
    constexpr float kCamDegrees       = 45;
    constexpr float kRotationRadians  = glm::radians(1.0f);
    constexpr float kMovementConstant = 40;

    double mouse_position_x_begin;
    double mouse_position_y_begin;
    double mouse_position_x_end;
    double mouse_position_y_end;

    glm::mat4 projection_matrix = glm::perspective(
        glm::radians(kCamDegrees),  // Вертикальное поле зрения в радианах. Обычно между
        // 90&deg; (очень широкое) и 30&deg; (узкое)
        static_cast<float>(kWidth) / static_cast<float>(kHeight),  // Отношение сторон. Зависит от размеров вашего окна.
        // Заметьте, что 4/3 == 800/600 == 1280/960
        0.1f,   // Ближняя плоскость отсечения. Должна быть больше 0.
        100.0f  // Дальняя плоскость отсечения.
    );

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Выключение возможности изменения размера окна
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Open a window and create its OpenGL context
    GLFWwindow *window = glfwCreateWindow(kWidth, kHeight, "3D2MC", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 "
                     "version of the tutorials.\n";
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;  // need to use new functional + core-profile mode
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        getchar();
        glfwTerminate();
        return -1;
    }

    // Set Viewport
    int viewport_width, viewport_height;
    glfwGetFramebufferSize(window, &viewport_width, &viewport_height);
    glViewport(0, 0, viewport_width, viewport_height);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Create and compile our GLSL program from the shaders

    GLuint const kProgramID = LoadShaders(VERTEX_SHADERS_DIR / "TransformVertexShader.glsl",
                                          FRAGMENT_SHADERS_DIR / "ColorFragmentShader.glsl");

    glm::vec4 camera_position(10, 6, 15, 0);
    glm::vec3 camera_center(0, 0, 0);
    glm::vec3 front;
    glm::vec3 side;
    glm::vec4 head(0, 1, 0, 0);

    std::vector<figure::Cube> blocks;
    std::vector<std::pair<GLfloat const, GLboolean>> is_retired;

    if (argc == 1) {
        std::cout << "ERROR: Missing .XYZ file\nusage:\n3D2MC.exe path\\to\\file.XYZ";
        return -2;
    } else {
        std::filesystem::path blocks_input(argv[1]);
        if (!std::filesystem::exists(blocks_input) || std::filesystem::is_directory(blocks_input) ||
            blocks_input.extension() != ".XYZ") {
            std::cout << "ERROR: WRONG FILE PATH " << blocks_input << '\n';
            return -2;
        }
        std::ifstream file;
        file.open(blocks_input);
        int count;
        file >> count;
        for (int i = 0; i < count; ++i) {
            GLfloat x, y, z;
            file >> x >> y >> z;
            blocks.emplace_back(x, y, z);
            is_retired.emplace_back(VectorLength<3>({x, y, z}), true);
        }
        file.close();
    }

    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint const kMatrixID = glGetUniformLocation(kProgramID, "MVP");

    glfwSetCursorPos(window, kWidth / 2, kHeight / 2);
    glfwGetCursorPos(window, &mouse_position_x_end, &mouse_position_y_end);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // TODO: write callbacks for keys and mouse (remove it from cycle)
    glfwSetCursorPosCallback(window, CursorPositionCallback);
    glfwSetKeyCallback(window, KeyCallback);

    figure::Cube::generateBuffers();

    // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        glfwPollEvents();

        front = camera_center - Vec4To3(camera_position);
        side  = VectorMultiply(front, head);

        mouse_position_x_begin = mouse_position_x_end;
        mouse_position_y_begin = mouse_position_y_end;
        // TODO: Delete in final version, its just need for my IDE
        mouse_position_x_end = 0;
        mouse_position_y_end = 0;
        glfwGetCursorPos(window, &mouse_position_x_end, &mouse_position_y_end);
        if ((mouse_position_x_begin != mouse_position_x_end || mouse_position_y_begin != mouse_position_y_end)) {
            glm::vec2 mouse_vector =
                glm::vec2(mouse_position_x_end - mouse_position_x_begin, mouse_position_y_end - mouse_position_y_begin);
            glm::vec2 normalized_mouse_vector = glm::normalize(mouse_vector);

            camera_center = RotateVec3(front, kRotationRadians * VectorLength(mouse_vector) / 2.0f,
                                       -RotateVec3(side,
                                                   std::acos(normalized_mouse_vector[1]) *
                                                       (normalized_mouse_vector[0] >= 0.f ? 1.f : -1.f),
                                                   -front)) +
                            Vec4To3(camera_position);
            glfwSetCursorPos(window, kWidth / 2, kHeight / 2);
            glfwGetCursorPos(window, &mouse_position_x_end, &mouse_position_y_end);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera_position +=
                Vec3To4(glm::normalize(VectorMultiply(front, Vec4To3(glm::normalize(head))))) / kMovementConstant;
            camera_center += glm::normalize(VectorMultiply(front, Vec4To3(glm::normalize(head)))) / kMovementConstant;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera_position -=
                Vec3To4(glm::normalize(VectorMultiply(front, Vec4To3(glm::normalize(head))))) / kMovementConstant;
            camera_center -= glm::normalize(VectorMultiply(front, Vec4To3(glm::normalize(head)))) / kMovementConstant;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera_position -= Vec3To4(glm::normalize(front)) / kMovementConstant;
            camera_center -= glm::normalize(front) / kMovementConstant;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera_position += Vec3To4(glm::normalize(front)) / kMovementConstant;
            camera_center += glm::normalize(front) / kMovementConstant;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            camera_position += glm::normalize(head) / kMovementConstant;
            camera_center += Vec4To3(glm::normalize(head)) / kMovementConstant;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            camera_position -= glm::normalize(head) / kMovementConstant;
            camera_center -= Vec4To3(glm::normalize(head)) / kMovementConstant;
        }
        glm::mat4 view = glm::lookAt(Vec4To3(camera_position),  // Камера находится в мировых
                                                                // координатах (4,3,3)
                                     camera_center,  // И направлена в начало координат
                                     Vec4To3(head)   // "Голова" находится сверху
        );

        // Clear the screen. It's not mentioned before Tutorial 02, but it can
        // cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(kProgramID);

        glm::mat4 MVP = projection_matrix * view;
        int id        = 0;
        for (figure::Cube &cube : blocks) {
            glm::vec3 delta = VectorLength(cube.coordinates()) == 0
                                  ? glm::vec3(0)
                                  : (glm::normalize(cube.coordinates()) * is_retired[id].first / 1e3f);

            //            if (id == 0) std::cout << VectorLength(cube.coordinates()) << ' ' << is_retired[id].first << '
            //            ' << 2.f * is_retired[id].first << '\n';

            if (VectorLength(cube.coordinates()) <= is_retired[id].first && VectorLength(cube.coordinates()) != 0)
                is_retired[id].second = true;
            else if (VectorLength(cube.coordinates()) >= 2.f * is_retired[id].first &&
                     VectorLength(cube.coordinates()) != 0)
                is_retired[id].second = false;

            if (is_retired[id++].second)
                cube += delta;
            else
                cube -= delta;
            glUniformMatrix4fv(kMatrixID, 1, GL_FALSE, &(MVP * cube.model())[0][0]);
            // Draw cube...
            cube.Draw();
        }

        // Swap buffers
        glfwSwapBuffers(window);
    }
    figure::Cube::clearBuffers();

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}
