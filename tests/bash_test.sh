#!/bin/sh

declare -a arr=( \
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
	)

cd ..
./minimake.sh
for op in "${arr[@]}"
do
	echo "Running OP :'$op'"
	timeout 1 ./minishell -c "$op"
	err=$?
	if [ ! $err -eq 0 ]; then
		echo "OP '$op' failed!' with errorcode $err"
		exit 1
	fi
done

# ctrl c test
(
./minishell -c 'sleep 3'
) &
pid=$!

sleep 0.1
kill -INT $pid 
err=$?
if [ ! $err -eq 0 ]; then
	echo "Ctrl-C failed with kill errorcode $err"
	exit 1
fi

echo
echo "Tests ran succesfully"
