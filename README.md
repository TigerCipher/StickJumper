# Markdown File

A remake of the first game I ever let others play - a project back from high school. The original was made with Java with no hardware rendering. It was fairly buggy, collision physics were hit and miss. The art was literally fancy stick figures and boxes. This time around I am remaking the game in C++ with OpenGL. The art style might change as well so that some lighting would make sense. Pre-built binaries and any official releases will be for x64 Windows, but the code should function properly on all OpenGL supported PC platforms. I do use VCPKG as a package manager so if you wish to build the code yourself I will list dependencies below as I go, as I do not supply them here on the repo.

---

#### Dependencies
- glm
- glew
- glfw (maybe SDL2 I haven't decided at the time of writing this)
- imgui (dev builds only)
- fmt
- spdlog