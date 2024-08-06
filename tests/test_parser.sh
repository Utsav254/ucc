#!/bin/bash

#run build commands first
cmake .. > /dev/null
make -C ..

if [ $? -ne 0 ]; then
	echo "build failed"
	exit 1
else
	echo "build successful"
fi

# check if command line args are valid

OUTPUT_DIR="test_outputs/"
UCC_PATH="../"

if [ $# -eq 1 ]; then
	if [ -d $1 ]; then
		echo "found directory: $1. Will run tests..."
	else
		echo "invalid test directory provided"
		exit 1
	fi
else 
	echo -e "Provide exactly one command line argument.\nThis will be the Path to directory with c files to parse."
	exit 1
fi

TEST_DIR="$1"

if [ ! -d "$OUTPUT_DIR" ]; then
	mkdir -p "$OUTPUT_DIR"
fi

pass_count=0
fail_count=0

find "$TEST_DIR" -type f -name "*.c" | while read -r file; do
	
	echo "---------------Testing: $file---------------"

	dir="$(dirname "$file")"
    filename="$(basename "$file" .c)"

	new_dir="$OUTPUT_DIR${dir}/${filename}"

	asmfile="$new_dir/${filename}.s"

	stdoutlog="$new_dir/compiler_stdout.log"
	stderrlog="$new_dir/compiler_stderr.log"

	if [ ! -d "$new_dir" ]; then
        mkdir -p "$new_dir"
    fi
	
	cp "$file" "$new_dir/${filename}.c"

	$UCC_PATH/ucc -S"$file" -o"$asmfile" >"$stdoutlog" 2>"$stderrlog"

	if [ $? -ne 0 ]; then
		((fail_count++))
		echo -e "\033[31mParsing Failure\033[0m"
	else
		((pass_count++))
		echo -e "\033[32mParsing Success\033[0m"
	fi

	echo -e "Passes: $pass_count\nFails: $fail_count"

done



