; ModuleID = 'slang'
source_filename = "slang"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %0 = call i32 (i8*, ...) @println(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0), i32 15)
  %1 = call i32 (i8*, ...) @println(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0), i32 33)
}

declare i32 @println(i8*, ...)
