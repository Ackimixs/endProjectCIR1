#!/bin/bash

gcc c/*.c -o c/main -lm
./c/main


mv planets-EulerAsy.json web/scripts
mv planets-Euler.json web/scripts


exit 0