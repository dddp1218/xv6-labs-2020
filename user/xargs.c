#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAXN 1024

int main(int argc, char* argv[]){
    // 如果参数个数小于 2
    if (argc < 2) {
        // 打印参数错误提示
        fprintf(2, "usage: xargs command\n");
        // 异常退出
        exit(1);

    }

    char *argvs[MAXARG];
    int index = 0;
    for(int i = 1;i<argc;++i){
        argvs[index++] = argv[i];
    }
    char buf[MAXN] = {"\0"};
    
    int n;
    while((n = read(0, buf, MAXN)) > 0){
        char temp[MAXN] = {"\0"};
        argvs[index] = temp;
        int temp_index = 0;
        for(int i = 0; i<strlen(buf);++i){
            if(buf[i]=='\n'){
                temp[temp_index] = '\0';  // 在临时数组末尾添加终止符
                argvs[index++] = temp;    // 将临时数组作为参数添加到 argvs 数组中
                if(fork()==0){
                    exec(argv[1], argvs);
                }
                wait(0);
                temp_index = 0;           // 清空临时数组
            }else{
                temp[temp_index++] = buf[i];
            }
        }
    }
    exit(0);
}