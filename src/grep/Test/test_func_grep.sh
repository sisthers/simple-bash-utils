#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"s Test/test_0_grep.txt VAR"
"for grep.c grep.h Makefile VAR"
"for grep.c VAR"
"VAE for -e ^int grep.c grep.h Makefile VAR"
"VAE for -e ^int grep.c VAR"
"VAE regex -e ^print grep.c VAR -f Test/test_ptrn_grep.txt"
"VAE while -e void grep.c Makefile VAR -f Test/test_ptrn_grep.txt"
"for -e . grep.c VAR"
"VAE w for VAR grep.c"
"VAE for grep.c"
"VAR -e int grep.c for"
"grep.c for -e^int VAR"
"grep.c VAR for -e o"
"grep.c VARe^int"
)

declare -a extra=(
"VARn for Test/test_1_grep.txt Test/test_2_grep.txt"
"VARn for Test/test_1_grep.txt"
"VARn -e ^\} Test/test_1_grep.txt"
"VARce ^int Test/test_1_grep.txt Test/test_2_grep.txt"
"VARe ^int Test/test_1_grep.txt"
"VARnivh = Test/test_1_grep.txt Test/test_2_grep.txt"
"VARe"
"VARie INT Test/test_5_grep.txt"
"VARechar Test/test_1_grep.txt Test/test_2_grep.txt"
"VARne = -e out Test/test_5_grep.txt"
"VARiv int Test/test_5_grep.txt"
"VARin int Test/test_5_grep.txt"
"VARc -l aboba Test/test_1_grep.txt Test/test_5_grep.txt"
"VARv Test/test_1_grep.txt -e ank"
"VARnoe ) Test/test_5_grep.txt"
"VARl for Test/test_1_grep.txt Test/test_2_grep.txt"
"VARo -e int Test/test_4_grep.txt"
"VARe = -e out Test/test_5_grep.txt"
"VARnoe ing -e as -e the -e not -e is Test/test_6_grep.txt"
"VARe ing -e as -e the -e not -e is Test/test_6_grep.txt"
"VARc -e . Test/test_1_grep.txt -e '.'"
"VARl Test/for no_file.txt Test/test_2_grep.txt"
"VARf Test/test_3_grep.txt Test/test_5_grep.txt"
)

testing()
{
    t=$(echo $@ | sed -e "s/VAR/$var/" -e "s/VAE/$vae/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "success grep $t"
    else
      (( FAIL++ ))
      echo "fail grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}


# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

# 1 параметр
for var1 in v c l n h o
do
  for i in "${tests[@]}"
  do
	  for var0 in e
		do
		  vae="-$var0"
		  var="-$var1"
		  testing $i
    done
	done
done

# 2 параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
              for var0 in e
		           do
		            vae="-$var0"
                var="-$var1 -$var2"
                testing $i
              done
            done
        fi
    done
done

# 3 параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                  for var0 in e
                  do
                    vae="-$var0"
                    var="-$var1 -$var2 -$var3"
                    testing $i
                  done
                done
            fi
        done
    done
done

# 2 сдвоенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        if [ $var1 != $var2 ]
        then
            for i in "${tests[@]}"
            do
                for var0 in e
                do
                  vae="-$var0"
                  var="-$var1$var2"
                  testing $i
                done
            done
        fi
    done
done

# 3 строенных параметра
for var1 in v c l n h o
do
    for var2 in v c l n h o
    do
        for var3 in v c l n h o
        do
            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
            then
                for i in "${tests[@]}"
                do
                  for var0 in e
                  do
                    vae="-$var0"
                    var="-$var1$var2$var3"
                    testing $i
                  done
                done
            fi
        done
    done
done



echo "FAIL: $FAIL"
echo "SUCCESS: $SUCCESS"
echo "ALL: $COUNTER"
