add_executable(SDL2-Base
        main.cpp
        ltimer.cpp
        ltimer.h
        LTexture.cpp
        LTexture.h
        resource.cpp
        resource.h)

target_link_libraries(SDL2-Base ${SDL2_LIBS} ${SDL2_IMAGE_LIBRARIES})