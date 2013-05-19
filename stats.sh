#!/bin/bash

wc -l magA.dat
wc -l magB.dat
wc -l magC.dat

cat u4get.log | grep "less number" > lessNumber.log
wc -l lessNumber.log

cat u4get.log | grep "out of range" > outOfRange.log
wc -l outOfRange.log

cat u4get.log | grep "no PM" > noPM.log
wc -l noPM.log

cat u4get.log | grep "total PM" > exceedsPM.log
wc -l exceedsPM.log

cat u4get.log | egrep "II.*(12.90[1-9]|12.9[1-9]\d)" > edgeStars.log
wc -l edgeStars.log 

