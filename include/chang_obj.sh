#!/bin/bash

cd ~
cd /home/alex/Workspace/OpenALPR/openalpr/src
echo "Current Directory: /home/alex/Workspace/OpenALPR/openalpr/src"
echo "Build in Progress"
make
echo "Build Complete"
cd openalpr
echo "Replacing Object files"
cd ~
cd ../../usr/lib
cp -i /home/alex/Workspace/OpenALPR/openalpr/src/openalpr/libopenalpr.so ./
cp -i /home/alex/Workspace/OpenALPR/openalpr/src/openalpr/libopenalpr.so.2 ./

