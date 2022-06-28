#!/bin/bash

gcc c/*.c -o c/main -lm
./c/main



if [ -f "planets-EulerAsy.json" ]; then
  mv planets-EulerAsy.json web/scripts
  printf "\nFile planets-EulerAsy.json move in the web/scripts folder\n"
fi

if [ -f "planets-Euler.json" ]; then
  mv planets-Euler.json web/scripts
  printf "\nFile planets-Euler.json move in the web/scripts folder\n"
fi


exit 0