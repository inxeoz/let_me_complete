@.str = private constant [4 x i8] c"%s\0A\00"

declare i32 @printf(i8*, ...)

define i32 @main(i32 %argc, i8** %argv) {
entry:
  ; Get the first argument from the command line
  %arg_ptr = getelementptr inbounds i8*, i8** %argv, i32 1
  %arg = load i8*, i8** %arg_ptr

  ; Print the argument
  %format = getelementptr [4 x i8], [4 x i8]* @.str, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* %format, i8* %arg)

  ret i32 0
}
