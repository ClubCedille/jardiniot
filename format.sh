#!/bin/bash


clang-format -i -style=file jardiniot-emb/rev2/main/*/*.cpp
clang-format -i -style=file jardiniot-emb/rev2/main/*/*.c 
clang-format -i -style=file jardiniot-emb/rev2/main/*/*.hpp
clang-format -i -style=file jardiniot-emb/rev2/main/*/*.h
clang-format -i -style=file jardiniot-emb/rev2/main/*/*/*.cpp
clang-format -i -style=file jardiniot-emb/rev2/main/*/*/*.c 
clang-format -i -style=file jardiniot-emb/rev2/main/*/*/*.hpp
clang-format -i -style=file jardiniot-emb/rev2/main/*/*/*.h
  
    