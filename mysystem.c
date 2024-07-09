/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
  char *execpath = "/bin/sh";
int mysystem(char *command) {
  int status = 0;
  // ここにプログラムを書く
  int pid = 0;
  if (command == NULL) {
    fprintf(stderr, "commandでエラー発生\n");
    return 1;
  }
  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "forkでエラー発生\n");
    return -1;
  } else if (pid != 0) {
    while (wait(&status) != pid) {
      ;
    }
  } else {
    execl(execpath, "sh", "-c", command, NULL);
    perror(execpath);
    exit(127);
  }
  return status;
}

/* 実行例

ここに実行例を書く
% ls -l
total 616
-rw-r--r--  1 iwamiyuuki  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 iwamiyuuki  staff    2795  7  4 09:45 README.md
-rw-r--r--  1 iwamiyuuki  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 iwamiyuuki  staff   50392  7  9 18:50 mysysmain
-rw-r--r--  1 iwamiyuuki  staff     925  7  4 09:45 mysysmain.c
-rw-r--r--  1 iwamiyuuki  staff     856  7  9 18:49 mysystem.c
-rw-r--r--  1 iwamiyuuki  staff      90  7  4 09:45 mysystem.h
% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 iwamiyuuki  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 iwamiyuuki  staff    2795  7  4 09:45 README.md
-rw-r--r--  1 iwamiyuuki  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 iwamiyuuki  staff   50392  7  9 18:50 mysysmain
-rw-r--r--  1 iwamiyuuki  staff     925  7  4 09:45 mysysmain.c
-rw-r--r--  1 iwamiyuuki  staff     856  7  9 18:49 mysystem.c
-rw-r--r--  1 iwamiyuuki  staff      90  7  4 09:45 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 iwamiyuuki  staff     143  7  4 09:45 Makefile
-rw-r--r--  1 iwamiyuuki  staff    2795  7  4 09:45 README.md
-rw-r--r--  1 iwamiyuuki  staff  238232  7  4 09:45 README.pdf
-rwxr-xr-x  1 iwamiyuuki  staff   50392  7  9 18:50 mysysmain
-rw-r--r--  1 iwamiyuuki  staff     925  7  4 09:45 mysysmain.c
-rw-r--r--  1 iwamiyuuki  staff     856  7  9 18:49 mysystem.c
-rw-r--r--  1 iwamiyuuki  staff      90  7  4 09:45 mysystem.h
retval = 00000000
% ./mysysmain        
使い方 : ./mysysmain コマンド文字列
*/
