set(target polinoms_test)

file(GLOB_RECURSE srcs "*.cpp")

add_executable(${target} ${srcs})
target_link_libraries(${target} PUBLIC gtest polynoms)
