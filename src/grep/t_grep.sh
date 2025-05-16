#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt

for var in -v -c -n -h -o -l
do
  TEST1="for s21_grep.c Makefile $var"
  ./s21_grep $TEST1 > s21_grep.txt
  grep $TEST1 > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
  then
    (( COUNTER_SUCCESS++ ))
  else
    echo "TEST1 $var" >> log.txt
    (( COUNTER_FAIL++ ))
  fi
  rm s21_grep.txt grep.txt

  TEST2="for s21_grep.c $var"
  ./s21_grep $TEST2 > s21_grep.txt
  grep $TEST2 > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ] #Files s21_grep.txt and grep.txt are identical
  then
    (( COUNTER_SUCCESS++ ))
  else
    echo "TEST2 $var" >> log.txt
    (( COUNTER_FAIL++ ))
  fi
  rm s21_grep.txt grep.txt
done

for var in -v -c -n -h -o -l
do
  for var2 in -v -c -n -h -o -l
  do
    if [ $var != $var2 ]
    then
      TEST3="for s21_grep.c Makefile $var $var2"
      ./s21_grep $TEST3 > s21_grep.txt
      grep $TEST3 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "TEST3 $var $var2" >> log.txt
        (( COUNTER_FAIL++ ))
      fi
      rm s21_grep.txt grep.txt

      TEST4="for s21_grep.c $var $var2"
      ./s21_grep $TEST4 > s21_grep.txt
      grep $TEST4 > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ] #Files s21_grep.txt and grep.txt are identical
      then
        (( COUNTER_SUCCESS++ ))
      else
        echo "TEST4 $var $var2" >> log.txt
        (( COUNTER_FAIL++ ))
      fi
      rm s21_grep.txt grep.txt
    fi
    done
  done
for var in -v -c -n -h -o -l
do
  for var2 in -v -c -n -h -o -l
  do
    for var3 in -v -c -n -h -o -l
    do
      if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
      then

        TEST5="for s21_grep.c Makefile $var $var2 $var3"
        ./s21_grep $TEST5 > s21_grep.txt
        grep $TEST5 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ] #Файлы s21_grep.txt и grep.txt идентичны
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST5 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

        TEST6="for s21_grep.c $var $var2 $var3"
        ./s21_grep $TEST6 > s21_grep.txt
        grep $TEST6 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ] #Files s21_grep.txt and grep.txt are identical
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST6 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

        TEST7="-e for -e ^int s21_grep.c Makefile $var $var2 $var3"
        ./s21_grep $TEST7 > s21_grep.txt
        grep $TEST7 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST7 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

        TEST8="-e for -e ^int s21_grep.c $var $var2 $var3"
        ./s21_grep $TEST8 > s21_grep.txt
        grep $TEST8 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST8 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

        TEST9="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
        ./s21_grep $TEST9 > s21_grep.txt
        grep $TEST9 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST9 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

        TEST10="-e regex -e void s21_grep.c Makefile $var $var2 $var3 -f pattern.txt"
        ./s21_grep $TEST10 > s21_grep.txt
        grep $TEST10 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST10 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

        TEST11="-e while -e void s21_grep.c Makefile $var $var2 $var3 -f pattern.txt -f test.txt"
        ./s21_grep $TEST11 > s21_grep.txt
        grep $TEST11 > grep.txt
        DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
        if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          (( COUNTER_SUCCESS++ ))
        else
          echo "TEST11 $var $var2 $var3" >> log.txt
          (( COUNTER_FAIL++ ))
        fi
        rm s21_grep.txt grep.txt

      fi
    done
  done
done
# echo test12
# TEST12="-e while -e void s21_grep.c -f fgkjfgkj.txt"
# ./s21_grep $TEST12
# grep $TEST12
# echo test13 
# TEST13="-e while -e void Makefifgffgle.c -f test.txt"
# ./s21_grep $TEST13
# grep $TEST13
# echo test14
# TEST14="-e while -e void Makefifgffgle.c -f testfvffvfv.txt"
# ./s21_grep $TEST14
# grep $TEST14
# echo test15
# TEST15=""
# ./s21_grep $TEST15
# grep $TEST15
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"