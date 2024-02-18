cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(count_hakobikata_tb)

add_compile_options(-Wall -O2)

find_package(yaml-cpp REQUIRED)

include_directories(
  include
  ${YAML_CPP_INCLUDE_DIR}
)

add_executable(count_hakobikata_tb
  src/count_hakobikata_tb_main.cpp
)

add_executable(generate_scenario_descriptions
  src/generate_scenario_descriptions_main.cpp
)

target_link_libraris(generate_scenario_descriptions
  ${YAML_CPP_LIBRARIES}
)


