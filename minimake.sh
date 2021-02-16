#!/bin/sh

build_dir=build

if [ $# -eq 1 ] && [ "$1" == "test" ]; then
	# compile and test
	cmake -S . -B $build_dir -DBUILD_TESTING=ON && ( cd $build_dir && make ) \
	&& ( cd $build_dir && ctest --output-on-failure ./)
elif [ $# -eq 1 ] && [ "$1" == "clean" ]; then
	# clean all files which are specified in .gitignore 
	git clean -d -f -X
elif [ $# -eq 0 ]; then
	# compile and copy minishell binary and lib to root folder
	cmake -S . -B $build_dir -DBUILD_TESTING=OFF && ( cd $build_dir && make ) \
	&& cp $build_dir/apps/minishell ./ \
	&& cp $build_dir/src/libminishell.a ./ \
	&& echo -e "You can run ./\e[92mminishell\e[39m now or include \e[92mlibminishell.a\e[39m in your library."
else
	cat<<-EOF
	usage:
	  $0       -> compile
	  $0 test  -> compile and test
	  $0 clean -> remove build files 
	EOF
fi

