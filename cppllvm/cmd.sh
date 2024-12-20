
llc -filetype=obj test.ll -o output.o
ls
clang output.o -o test_program -no-pie
ls
./test_program hii
#### end of dependent process
