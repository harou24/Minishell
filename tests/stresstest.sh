#!/bin/bash

set -e

VALGRIND="valgrind\
			--leak-check=full \
			--trace-children=yes\
			"

if ! which valgrind; then
	echo "no valgrind."; unset VALGRIND
fi
if ! which cmake; then
	echo "install cmake."; exit 1
fi

declare -a testsArrayNonCrash=( \
	'ls' \
	'ls;' \
	';ls;' \
	'echo' \
	'ls -l | cat' \
	'ls ; echo a' \
	'ls -l ; echo a' \
	'ls -l ./; echo a' \
	'ls ; echo' \
	'ls -l ; echo' \
	'ls -l ./; echo' \
	'ls; echo' \
	'ls -l; echo' \
	'ls -l ./; echo' \
	'ls;echo;' \
	'   ls;echo;' \
	'ls -l;echo;' \
	'ls -l ./;echo;' \
	'ls -l| cat ' \
	'ls -l | cat| cat | cat | cat | cat | cat | cat' \
	'echo a | cat| cat | cat | cat | cat | cat | cat' \
	'ls -l; echo $?' \
	'  ls -l| cat ' \
	'  ls -l   | cat ' \
	'  cat < ./minimake.sh' \
	'echo User:$USER' \
	'pwd' \
	'pwd; ls -l ' \
	'pwd; ls -l ./src' \
	'env' \
	'export' \
	'export a=5' \
	'exit' \
	'exit 0' \
	'a=5' \
	'a=5; echo $a' \
	'echo $a; a=5; echo $a' \
	'echo "$a"; a=5; echo '$a'' \
	'echo "$PWD"' \
	'echo "'$PWD'"' \
	'echo '"$PWD"'' \
	'echo "'"$PWD"'"' \
	'unset a; a=5; unset a;'
	'cd ~' \
	'cd ~/' \
	'cd ~/' \
	'cd -' \
	'cd /' \
	'cd -; cd -' \
	'echo "hello" > /dev/null' \
	'echo "hello" > build/stress.tmp; cat build/stress.tmp' \
	'echo "hello" >> build/stress.tmp; cat build/stress.tmp' \
	'echo "ls ./src" > /dev/null' \
	'echo "ls ./src" > build/stress.tmp; cat build/stress.tmp' \
	'echo "ls ./src" >> build/stress.tmp; cat build/stress.tmp' \
	'cat < build/stress.tmp' \
	'touch build/stress.tmp' \
	'touch build/stress.tmp; rm build/stress.tmp' \
	'echo > "build/stress.tmp"' \
	'echo $PWD; echo "$PWD"' \
	'echo $PWD ; echo $HOME ; echo "$PWD" ; ' \
	'echo hello | echo' \
	'export | grep -e "PWD="' \
	'echo > build/stress.tmp multi file ; wc build/stress.tmp' \
	'echo a b cd > build/stress.tmp multi file ; wc build/stress.tmp' \
	'export PATH="$PATHtest:working:multiplepath:directory1:directory2"' \
	)

declare -a testsArrayCmp=( \
	'ls ./src' \
	'ls./src' \
	'echo abc' \
	'ls ./src; echo a' \
	'ls -l./src; echo a' \
	'ls -l ./src; echo a' \
	'ls ./src; echo' \
	'ls -l ./src; echo' \
	'ls -l ./src; echo' \
	'ls ./src; echo' \
	'ls -l./src; echo' \
	'ls -l ./src; echo' \
	'ls ./src;echo;' \
	'   ls ./src;echo;' \
	'ls -l ./src;echo;' \
	'ls -l ./src;echo;' \
	'ls -l ./src| cat' \
	'ls -l ./src| cat ' \
	'ls -l ./src| cat ; echo a' \
	'ls -l ./src; echo $?' \
	'  ls -l ./src| cat ' \
	'  ls -l   ./src| cat ' \
	'  cat < ./minimake.sh' \
	'echo User:$USER' \
	'pwd' \
	'pwd; ls -l ./src' \
	'cd ./src' \
	'export a=5' \
	'a=5' \
	'a=5; echo $a' \
	'echo $a; a=5; echo $a' \
	'echo "$a"; a=5; echo '$a'' \
	'echo "$PWD"' \
	'echo "'$PWD'"' \
	'echo '"$PWD"'' \
	'echo "'"$PWD"'"' \
	'echo "hello" > /dev/null' \
	'echo "hello" > build/stress.tmp; cat build/stress.tmp; rm build/stress.tmp' \
	'echo "hello" >> build/stress.tmp ;echo "hello" >> build/stress.tmp; cat build/stress.tmp; rm build/stress.tmp' \
	'ls ./src > /dev/null' \
	'ls ./src > build/stress.tmp; cat build/stress.tmp; rm build/stress.tmp' \
	'ls ./src >> build/stress.tmp;ls ./src >> build/stress.tmp; cat build/stress.tmp; rm build/stress.tmp' \
	'echo a > build/stress.tmp; cat < build/stress.tmp' \
	'touch build/stress.tmp' \
	'touch build/stress.tmp; rm build/stress.tmp' \
	'rm build/stress.tmp' \
	'FAULTY; ls'
	'export PATH="$PATHtest:working:multiplepath:directory1:directory2"; echo $PATH' \
	#'echo > build/stress.tmp multi file ; wc build/stress.tmp' \
	#'echo a b cd > build/stress.tmp multi file ; wc build/stress.tmp' \
	)

run_tests()
{
	if [ ! "$VALGRIND" == "" ]; then
		timeout 1 valgrind ./build/apps/minishell -c 'true' &>/dev/null
		if [ $? -eq 0 ]; then
			echo "enabling VALGRIND for tests!"
			VALGRIND_ENABLED=true
		else
			echo "disabling VALGRIND for tests!"
			unset VALGRIND_ENABLED
			sleep 0.5
		fi
	fi

	for op in "${testsArrayNonCrash[@]}"
	do
		echo "Running OP :'$op'"
		timeout 3 ./build/apps/minishell -c "$op" &> /tmp/minishell.out
		err=$?

		if [ "$VALGRIND_ENABLED" == "true" ]; then
			echo "Running valgrind OP :'$op'"
			timeout 3 $VALGRIND ./build/apps/minishell -c "$op" &> /tmp/minishell.out
			valgrinderr=$?
		else
			valgrinderr=0
		fi

		if [[ ! $err -eq 0 || ! $valgrinderr -eq 0 ]]; then
			echo "Last command output: "; echo \'
			cat /tmp/minishell.out
			echo \'
			echo "OP '$op' failed!' with errorcode $err, valgrind errorcode $valgrinderr -> ./minimake.sh $1"
			pkill -9 minishell
			return 1
		fi
		sleep 0.1
	done

	for op in "${testsArrayCmp[@]}"
	do
		echo "Running compare OP :'$op'"
		timeout 3 ./build/apps/minishell -c "$op" > /tmp/minishell.out 2>/dev/null
		minishell_err=$?

		bash -c "$op" > /tmp/bash.out 2>/dev/null
		bash_err=$?

		if [ ! $bash_err -eq $minishell_err ]; then
			echo "Compare OP '$op' failed!' bash_error{$bash_err}, minishell_error{$minishell_err} -> ./minimake.sh $1"
			pkill -9 minishell
			return 1
		fi
		diff /tmp/minishell.out /tmp/bash.out 
		if [ ! $? -eq 0 ] ; then
			echo "Compare OP '$op' failed!' -> ./minimake.sh $1"
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
	if [ $# -gt 0 ]; then
		./minimake.sh $1
	else
		./minimake.sh
	fi
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

test -f ./minimake.sh ||  { cd ../ && test -f ./minimake.sh || exit 1; }

FLAG=clean; compile $FLAG || exit 1
FLAG=debug; compile $FLAG && run_tests_for $1 $FLAG || exit 1
FLAG=release; compile $FLAG && run_tests_for $1 $FLAG || exit 1
FLAG=test; compile $FLAG && run_tests_for $1 $FLAG || exit 1
FLAG=testOpt; compile $FLAG && run_tests_for $1 $FLAG || exit 1

echo -e "\033[0m"
echo "Tests ran succesfully for $1 times."
