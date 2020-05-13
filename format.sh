#!/bin/bash
find jardiniot-emb/rev2/main -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;
