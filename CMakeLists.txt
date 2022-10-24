cmake_minimum_required(VERSION 3.21)
project(project1)

set(CMAKE_CXX_STANDARD 20)

add_executable(project1 main.cpp Cmd_Arg_Parser.cpp Cmd_Arg_Parser.h Bitmap.cpp Bitmap.h BaseFilter.h FilterPipelineFactory.cpp FilterPipelineFactory.h Application.h Application.cpp BlurFilter.cpp BlurFilter.h CropFilter.cpp CropFilter.h GsFilter.cpp GsFilter.h NegFilter.cpp NegFilter.h SharpFilter.cpp SharpFilter.h EdgeFilter.cpp EdgeFilter.h)
