set(SAMPLE_LIST ${SAMPLE_LIST} camera-fps PARENT_SCOPE)

add_executable(camera-fps
  ../utils/glfw_freecam.cpp
  main.cpp
)

target_link_libraries(camera-fps LINK_PUBLIC
  engine
  GLEW SOIL glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl
)
