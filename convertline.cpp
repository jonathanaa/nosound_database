#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<cstdio>
using namespace std;
int main()
{
    FILE *file1 = fopen("data.json", "r");
    FILE *file2 = fopen("data_out.txt", "w");
    int check=0;
    int sum=0;
    char ch,ch1,ch2;
    ch1=' ';
    ch2=' ';
    while((ch = fgetc(file1)) != EOF) {
        if(ch==','){
            if(ch1=='"' && ch2=='}'){
                fputc('\n',file2);
                check=1;
                sum++;
            }
        }
        ch1=ch2;
        ch2=ch;
        if(check==0){
            fputc(ch, file2);
        }
        else{
            check=0;
        }
    }
    printf("sum:%d\n",sum);
    fclose(file1);
    fclose(file2);

    return 0;
}
