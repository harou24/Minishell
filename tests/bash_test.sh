#!/bin/bash

VALGRIND="valgrind\
			--trace-children=yes\
			"

declare -a testsArray=( \
	"ls" \
	"echo" \
	"ls ; echo a" \
	"ls -l ; echo a" \
	"ls -l ./; echo a" \
	"ls ; echo" \
	"ls -l ; echo" \
	"ls -l ./; echo" \
	"ls; echo" \
	"ls -l; echo" \
	"ls -l ./; echo" \
	"ls;echo;" \
	"   ls;echo;" \
	"ls -l;echo;" \
	"ls -l ./;echo;" \
	"ls -l | cat" \
	"ls -l| cat " \
	"ls -l; echo $?" \
	"  ls -l| cat " \
	"  ls -l   | cat " \
	"  cat < ./minimake.sh" \
	"echo $USER" \
	"pwd" \
	"pwd; ls -l " \
	"cd /" \
	"env" \
	"export a=5" \
	"a=5" \
	"exit 0" \
	"exit" \
	)

run_tests()
{
	for op in "${testsArray[@]}"
	do
		echo "Running OP :'$op'"
		timeout 3 ./build/apps/minishell -c "$op"
		err=$?
		if [ ! $err -eq 0 ]; then
			echo "OP '$op' failed!' with errorcode $err -> ./minimake.sh $1"
			pkill -9 minishell
			return 1
		fi
	done
	
	# ctrl c test
	(
	./build/apps/minishell -c 'sleep 3'
	) &
	pid=$!
	
	sleep 0.1
	kill -INT $pid 
	err=$?
	if [ ! $err -eq 0 ]; then
		echo "Ctrl-C failed with kill errorcode $err -> ./minimake.sh $1"
		pkill -9 minishell
		return 1
	fi
	
	echo
	echo "Tests ran succesfully -> ./minimake.sh $1"
}

compile()
{
	[ $# -gt 0 ] && ./minimake.sh $1 || ./minimake.sh
}

run_tests_for()
{
	echo "Running $1 tests for './minimake.sh $2'"; sleep 2
	for ((i = 1; i <= $1; i++ )); do
		run_tests $2 || return 1
	done
}

if [ $# -eq 0 ]; then
	echo "usage: $0 [number of tests]"
	exit 1
fi

cd ../ || exit 1

#FLAG=clean; compile $FLAG || exit 1
FLAG=release; compile $FLAG && run_tests_for $1 $FLAG || exit 1
FLAG=debug; compile $FLAG && run_tests_for $1 $FLAG || exit 1
#FLAG=test; compile $FLAG && run_tests_for $1 $FLAG || exit 1
#FLAG=testOpt; compile $FLAG && run_tests_for $1 $FLAG || exit 1

echo -e "\033[0m"
echo "Tests ran succesfully for $1 times."
