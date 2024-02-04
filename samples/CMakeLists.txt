file(GLOB hdrs "*.h*" "../include/*.h")
file(GLOB srcs "*.cpp" "../src/Polynom.cpp")

add_executable(polinoms ${srcs} ${hdrs})
