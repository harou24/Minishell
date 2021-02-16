#!/bin/sh

if [ $# -eq 1 ] && [ "$1" == "test" ]; then
	# compile and test
	cmake -S . -B build -DBUILD_TESTING=ON && ( cd build && make ) \
	&& ctest --output-on-failure ./build
elif [ $# -eq 0 ]; then
	# compile and copy minishell binary to root folder
	cmake -S . -B build -DBUILD_TESTING=OFF && ( cd build && make ) \
	&& cp build/apps/minishell ./ \
	&& echo -e "You can run ./\e[92mminishell\e[39m now."
else
	echo "usage: '$0 test' for testing or '$0' to only compile minishell"
fi

