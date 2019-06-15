//https://blog.csdn.net/qq_25867649/article/details/50996709
//g++ -c -fPIC interface_finish.cpp -o interface_finish.o
//g++ -shared -Wl,-soname,libfoo2.so -o libfoo2.so  interface_finish.o
#include <bits/stdc++.h>
#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<cstdio>
#include <time.h>
#define BAD_POS 0xFFFFFFFF // returned by SetFilePointer and GetFileSize
#define SUCCESS 0
using namespace std;
typedef DWORD mmf_share_mode;
typedef DWORD mmf_access_mode;
typedef DWORD mmf_flags;
char input_statement[1000];
char commend_exit[] = "exit";
char commend_new[] = "new";
char commend_search[] = "search";
char commend_modify[] = "modify";
char commend_delete[] = "delete";
char search_url[] = "url";
char search_title[] = "title";
char search_content[] = "content";
char search_viewcount[] = "viewcount";
char search_res[] = "res";
char search_duration[] = "duration";
char search_bigger[] = "bigger";
char search_smaller[] = "smaller";
char search_equal[] = "equal";
void search_data1(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split1.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data2(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split2.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data3(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split3.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data4(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split4.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data5(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split5.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data6(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split6.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data7(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split7.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data8(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split8.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data9(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split9.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void search_data10(size_t offsetstart,size_t offsetlength){//search data_split1
    //cout<<"create memorymapfile..."<<endl;
    const char* shared_name = "testMmf";
    const char* file_name = ".\\data_split10.txt";
    const DWORD mmf_size = 0;
    //¦s¨ú¼Ò¦¡
    mmf_access_mode access_mode = (GENERIC_READ|GENERIC_WRITE);
    //¦@¨É¼Ò¦¡
    mmf_share_mode share_mode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    //¤å¥ó?©Ê
    mmf_flags flags = FILE_FLAG_SEQUENTIAL_SCAN;//|FILE_FLAG_WRITE_THROUGH|FILE_FLAG_NO_BUFFERING;
    DWORD error_code;
    //?«Ø¤å¥ó
    HANDLE mmHandle =
        CreateFile(file_name,
             access_mode,
             share_mode,
             NULL,
             OPEN_ALWAYS,
             flags,
             NULL);

    if (mmHandle == INVALID_HANDLE_VALUE) {
        error_code = GetLastError();
        cout<<"«Ø¥ß¥¢±Ñ"<<error_code<<endl;
    }else{
        DWORD high_size;
        DWORD file_size = GetFileSize(mmHandle, &high_size);
        if (file_size == BAD_POS && (error_code = GetLastError()) != SUCCESS) {
            CloseHandle(mmHandle);
            cout<<"error¡G"<<error_code<<endl;
        }
        DWORD size_high = 0;
        HANDLE mmfm = CreateFileMapping(mmHandle,
            NULL,
            PAGE_READWRITE,
            size_high,
            mmf_size,
            shared_name);

        error_code = GetLastError();
        if(SUCCESS != error_code){
            //cout<<"createFileMapping error"<<error_code<<endl;
        }else{
            if(mmfm == NULL){
                if(mmHandle != INVALID_HANDLE_VALUE){
                    CloseHandle(mmHandle);
                }
            }else{
                size_t view_size = 0;
                DWORD view_access = FILE_MAP_ALL_ACCESS;
                char* mmfm_base_address = (char*)MapViewOfFile(mmfm,view_access,0,0,view_size);
                if(mmfm_base_address == NULL){
                    error_code = GetLastError();
                    if(error_code != SUCCESS){
                        cout<<"error code "<<error_code<<endl;
                    }
                }else{
                    char ch_output[1800];//¦h¶}¤@­Ó¦s/0
                    char ch1[2] = "a";
                    char char_check[2] = "a";
                    char url[15];
                    size_t offset_num = 0;
                    int int_char_check;
                    size_t offset_start = offsetstart;//»Ý­nªº¸ê®Æ¶}©lªº¦a¤è
                    size_t offset_end = 0;

                    string one_line = "";
                    string url_output = "";
                    string title_output = "";
                    string content_output = "";
                    string viewCount_output = "";
                    string res_output = "";
                    string duration_output = "";
                    while(true){
                        /*memcpy(char_check,(PVOID)mmfm_base_address+offset_start+offset_num+2,(size_t)1);
                        int_char_check = (int)char_check[0];*/

                        //if(int_char_check==(int)10||int_char_check==(int)0){//§PÂ_¤å¥ó´«¦æ
                            memcpy(ch_output,(PVOID)mmfm_base_address+offset_start,offsetlength);
                            //print result
                            int pos_url=0;
                            int pos_title=0;
                            int pos_content=0;
                            int pos_viewCount=0;
                            int pos_res=0;
                            int pos_duration=0;
                            int pos_count=0;
                            for(int i=0; i<offsetlength; i++){
                                //printf("%c",ch_output[i]);
                                if(ch_output[i]=='D'){
                                    if(ch_output[i+1]=='i' && ch_output[i+2]=='l' && ch_output[i+3]=='l' && ch_output[i+4]=='o' && ch_output[i+5]=='n' && ch_output[i+6]=='1' && ch_output[i+7]=='2' && ch_output[i+8]=='3'){
                                        pos_count++;
                                        if(pos_count==1){
                                            pos_url=i+9;
                                        }
                                        else if(pos_count==2){
                                            pos_title=i+9;
                                        }
                                        else if(pos_count==3){
                                            pos_content=i+9;
                                        }
                                        else if(pos_count==4){
                                            pos_viewCount=i+9;
                                        }
                                        else if(pos_count==5){
                                            pos_res=i+9;
                                        }
                                        else if(pos_count==6){
                                            pos_duration=i+9;
                                        }
                                    }
                                }
                            }
                            cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                            cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                            cout<<"https:\/\/www.youtube.com\/watch?v=";
                            for(int i=pos_url; i<pos_title-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                            for(int i=pos_title; i<pos_content-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                            for(int i=pos_content; i<pos_viewCount-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                            for(int i=pos_viewCount; i<pos_res-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">RES</th><td>";
                            for(int i=pos_res; i<pos_duration-9; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr>");
                            cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                            for(int i=pos_duration; i<offsetlength; i++){
                                cout<<ch_output[i];
                            }
                            printf("</td></tr></tbody></table><br><br>");
                            break;
                    }
                    UnmapViewOfFile(mmfm_base_address);
                    CloseHandle(mmfm);
                    CloseHandle(mmHandle);
                }
            }
        }
    }
}
void new_data(char _url[],char _title[],char _content[],char _viewcount[],char _res[],char _duration[]){
    int tempSum = 0;
    fstream outputfile;
    outputfile.open("data_split10.txt", ios::out | ios::app);
    //判斷url有沒有被用過
    /*while(1){
        //check url has been used or not
        ifstream inputfile1;
        int ccheck,llength;
        string lline;
        char *uurl;
        ccheck=0;
        inputfile1.open("data_offset1.txt",ifstream::in);
        while(getline(inputfile1,lline)){
            llength=lline.length();
            char llinechar[llength+5];
            strcpy(llinechar,lline.c_str());
            uurl = strtok(llinechar," ");
            if(strcmp(uurl,_url)==0){
                ccheck=1;
                break;
            }
        }
        inputfile1.close();
        if(ccheck==0){
            inputfile1.open("data_offset2.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset3.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset4.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset5.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset6.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset7.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset8.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset9.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==0){
            inputfile1.open("data_offset10.txt",ifstream::in);
            while(getline(inputfile1,lline)){
                llength=lline.length();
                char llinechar[llength+5];
                strcpy(llinechar,lline.c_str());
                uurl = strtok(llinechar," ");
                if(strcmp(uurl,_url)==0){
                    ccheck=1;
                    break;
                }
            }
            inputfile1.close();
        }
        if(ccheck==1){
            cout<<"This url has been used!!\n"<<endl;
            continue;
        }
        //--------------------------------------------------------
        if((int)strlen(_url)==11){
            break;
        }
        else{
            cout<<"The length of this url is ERROR!!\n"<<endl;
        }
    }*/
    outputfile<<"Dillon123"<<_url<<"Dillon123"<<_title<<"Dillon123"<<_content<<"Dillon123"<<_viewcount<<"Dillon123"<<_res<<"Dillon123"<<_duration<<endl;
    tempSum = tempSum+56+(int)strlen(_url)+(int)strlen(_title)+(int)strlen(_content)+(int)strlen(_viewcount)+(int)strlen(_res)+(int)strlen(_duration);
    fstream file_offset;
    string pk_file_name = "data_offset10.txt";
    file_offset.open(pk_file_name.c_str(), ios::out | ios::app |ios::in);
    string line,line2;
    while(getline(file_offset,line)){
            line2=line;
    }
    int length,nextstart,nextend,intendd;
    char *url,*filenumber,*start,*endd;
    length=line2.length();
    char linechar[length+5];
    strcpy(linechar,line2.c_str());
    url = strtok(linechar," ");
    filenumber = strtok(NULL," ");
    start = strtok(NULL," ");
    endd = strtok(NULL," ");
    intendd=atoi(endd);
    //printf("\nintendd:%d\n",intendd);
    nextstart=intendd;
    nextend=nextstart+tempSum;
    //printf("\nnextstart:%d\n",nextstart);
    //printf("\nnextend:%d\n",nextend);
    file_offset.close();
    //¼g¤J¸ê®Æ
    fstream file_offset_write;
    file_offset_write.open(pk_file_name.c_str(), ios::out | ios::app |ios::in);
    file_offset_write<<_url<<" "<<"10"<<" "<<nextstart<<" "<<nextend<<" "<<endl;
    file_offset_write.close();
    printf("<div style=\"text-align:center;\"><h1>Write success!!!</h1></div>");
    outputfile.close();
}
void search_pk(char inputurls[]){
    //--------------------------------------------------
    ifstream inputfile1,inputfile2,inputfile3,inputfile4,inputfile5,inputfile6,inputfile7,inputfile8,inputfile9,inputfile10;
    string line,stringurl;
    int length,check,intfilenum;
    size_t intstart,intendd;
    char inputurl[100];
    char *url,*filenumber,*start,*endd;
    //input
        strcpy(inputurl,inputurls);
        //cout<<inputurl<<"\n";
        inputfile1.open("data_offset1.txt",ifstream::in);
        check=0;
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile1.close();
        if(check==0){
        inputfile2.open("data_offset2.txt",ifstream::in);
        while(getline(inputfile2,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile2.close();}
        if(check==0){
        inputfile3.open("data_offset3.txt",ifstream::in);
        while(getline(inputfile3,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile3.close();}
        if(check==0){
        inputfile4.open("data_offset4.txt",ifstream::in);
        while(getline(inputfile4,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile4.close();}
        if(check==0){
        inputfile5.open("data_offset5.txt",ifstream::in);
        while(getline(inputfile5,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile5.close();}
        if(check==0){
        inputfile6.open("data_offset6.txt",ifstream::in);
        while(getline(inputfile6,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile6.close();}
        if(check==0){
        inputfile7.open("data_offset7.txt",ifstream::in);
        while(getline(inputfile7,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile7.close();}
        if(check==0){
        inputfile8.open("data_offset8.txt",ifstream::in);
        while(getline(inputfile8,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile8.close();}
        if(check==0){
        inputfile9.open("data_offset9.txt",ifstream::in);
        while(getline(inputfile9,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile9.close();}
        if(check==0){
        inputfile10.open("data_offset10.txt",ifstream::in);
        while(getline(inputfile10,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            url = strtok(linechar," ");
            filenumber = strtok(NULL," ");
            start = strtok(NULL," ");
            endd = strtok(NULL," ");
            if(strcmp(url,inputurl)==0){
                //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
                check=1;
                intstart=atoi(start);
                intendd=atoi(endd);
                intfilenum=atoi(filenumber);
                break;
            }
        }
        inputfile10.close();}
        if(check==0){
            printf("<div style=\"text-align:center;\"><h1>No this record!!!</h1></div>");
        }
    //--------------------------------------------------
    intendd=intendd-intstart-2;
    if(intfilenum==1){
        search_data1(intstart,intendd);
    }
    else if(intfilenum==2){
        search_data2(intstart,intendd);
    }
    else if(intfilenum==3){
        search_data3(intstart,intendd);
    }
    else if(intfilenum==4){
        search_data4(intstart,intendd);
    }
    else if(intfilenum==5){
        search_data5(intstart,intendd);
    }
    else if(intfilenum==6){
        search_data6(intstart,intendd);
    }
    else if(intfilenum==7){
        search_data7(intstart,intendd);
    }
    else if(intfilenum==8){
        search_data8(intstart,intendd);
    }
    else if(intfilenum==9){
        search_data9(intstart,intendd);
    }
    else if(intfilenum==10){
        search_data10(intstart,intendd);
    }
}
void ddelete(char urldelete[]){
    fstream file_delete_write;
    string file_delete="delete_url.txt";
    file_delete_write.open(file_delete.c_str(), ios::out | ios::app |ios::in);
    file_delete_write<<urldelete<<endl;
    file_delete_write.close();
    printf("<div style=\"text-align:center;\"><h1>Delete url success!!!</h1></div>");
}
void checkdelete(char input_url_python[]){
    char charcheck[50];
    ifstream deletefile;
    int checkdelete=0;
    string deleteline;
    deletefile.open("delete_url.txt",ifstream::in);
    while(getline(deletefile,deleteline)){
        //cout<<"deleteline:"<<deleteline<<"\n";
        strcpy(charcheck, deleteline.c_str());
        if(strcmp(input_url_python,charcheck)==0){
            //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
            checkdelete=1;
            break;
        }
    }
    if(checkdelete==1){
        printf("<div style=\"text-align:center;\"><h1>This data has been deleted!!!</h1></div>");
    }
    else{
        search_pk(input_url_python);
    }
}
int checkdelete2(char deleteurl[]){
    char charcheck[50];
    ifstream deletefile;
    int checkdelete=0;
    string deleteline;
    deletefile.open("delete_url.txt",ifstream::in);
    while(getline(deletefile,deleteline)){
        //cout<<"deleteline:"<<deleteline<<"\n";
        strcpy(charcheck, deleteline.c_str());
        if(strcmp(deleteurl,charcheck)==0){
            //cout<<url<<" "<<filenumber<<" "<<start<<" "<<endd<<"\n";
            checkdelete=1;
            break;
        }
    }
    if(checkdelete==1){//±»„hÁË
        return 1;
    }
    else{
        return 2;
    }
}
void find_string(int check,char input_title_python[]){//vague search
        ifstream inputfile1;
        string line,out;
        int length,title_pos,content_pos,viewcount_pos,res_pos,duration_pos,ccount;
        out="";
        ccount=0;
        inputfile1.open("data_split1.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split2.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split3.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split4.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split5.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split6.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split7.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split8.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split9.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split10.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(input_title_python,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//title
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                if(checkdelete2(tempturl)==2){
                    ccount++;
                    cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                    cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                    cout<<"https:\/\/www.youtube.com\/watch?v=";
                    for(int i=9; i<title_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                    for(int i=title_pos+9; i<content_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                    for(int i=content_pos+9; i<viewcount_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                    for(int i=viewcount_pos+9; i<res_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">RES</th><td>";
                    for(int i=res_pos+9; i<duration_pos; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr>");
                    cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                    for(int i=duration_pos+9; i<length; i++){
                        cout<<linechar[i];
                    }
                    printf("</td></tr></tbody></table><br><br>");
                }
            }
        }
        inputfile1.close();
        printf("<div style=\"text-align:center;\"><h1>Total has ");
        printf("%d",ccount);
        printf(" records.</h1></div>");
}
void find_num(int check,char input_viewcount_python[]){//equal search
        ifstream inputfile1;
        string line,out;
        int length,title_pos,content_pos,viewcount_pos,res_pos,duration_pos,ccount;
        int inputnum=0;
        out="";
        ccount=0;
        inputnum=atoi(input_viewcount_python);
        int searchstatus=0;
        /*cout<<"Which do you want to search?:(bigger,smaller,equal)"<<endl;
        char x[1000];
        cin.getline(x,1000);
        if(strcmp(x,search_bigger)==0){
                searchstatus=1;
        }
        else if(strcmp(x,search_smaller)==0){
            searchstatus=2;
        }
        else{
            searchstatus=3;
        }*/
        searchstatus=3;//先預設equal
        //printf("\n---\searchstatus:%d\n---\n",searchstatus);
        inputfile1.open("data_split1.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split2.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split3.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split4.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                   string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split5.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split6.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split7.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split8.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split9.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        inputfile1.open("data_split10.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(searchstatus==1){//bigger
                if(charnum>inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else if(searchstatus==2){//smaller
                if(charnum<inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
            else{//equal
                if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//title
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    if(checkdelete2(tempturl)==2){
                        ccount++;
                        cout<<"<table class=\"table table-striped table-dark\"><thead><tr><th scope=\"col\">DATA</th></tr></thead>";
                        cout<<"<tbody><tr><th scope=\"row\">URL</th><td>";
                        cout<<"https:\/\/www.youtube.com\/watch?v=";
                        for(int i=9; i<title_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">TITLE</th><td>";
                        for(int i=title_pos+9; i<content_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">CONTENT</th><td>";
                        for(int i=content_pos+9; i<viewcount_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">VIEWCOUNT</th><td>";
                        for(int i=viewcount_pos+9; i<res_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">RES</th><td>";
                        for(int i=res_pos+9; i<duration_pos; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr>");
                        cout<<"<tr><th scope=\"row\">DURATION</th><td>";
                        for(int i=duration_pos+9; i<length; i++){
                            cout<<linechar[i];
                        }
                        printf("</td></tr></tbody></table><br><br>");
                    }
                }
            }
        }
        inputfile1.close();
        printf("<div style=\"text-align:center;\"><h1>Total has ");
        printf("%d",ccount);
        printf(" records.</h1></div>");
}
void ddelete2(char urldelete[]){
    fstream file_delete_write;
    string file_delete="delete_url.txt";
    file_delete_write.open(file_delete.c_str(), ios::out | ios::app |ios::in);
    file_delete_write<<urldelete<<endl;
    file_delete_write.close();
    printf("<div style=\"text-align:center;\"><h3>delete url ");
    cout<<urldelete<<endl;
    printf(" success!!!</h3></div>");
}
void delete_string(int check,char inputstring[]){
        ifstream inputfile1;
        string line,out;
        int length,title_pos,content_pos,viewcount_pos,res_pos,duration_pos;
        out="";
        inputfile1.open("data_split1.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split2.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split3.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split4.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split5.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split6.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split7.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split8.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split9.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split10.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, title_pos+9, content_pos-title_pos-9);//title
            }
            else if(check==2){
                out=out.assign(line, content_pos+9, viewcount_pos-content_pos-9);//content
            }
            if(out.find(inputstring,0)!=-1){
                string out2;
                out2=out2.assign(line, 9, 11);//url
                char tempturl[50];
                strcpy(tempturl,out2.c_str());
                ddelete2(tempturl);
            }
        }
        inputfile1.close();
}
void delete_num(int check,char inputstring[]){
        ifstream inputfile1;
        string line,out;
        int length,title_pos,content_pos,viewcount_pos,res_pos,duration_pos,ccount;
        int inputnum=0;
        out="";
        ccount=0;
        inputnum=atoi(inputstring);
        inputfile1.open("data_split1.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split2.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split3.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split4.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split5.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split6.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split7.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split8.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split9.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
        inputfile1.open("data_split10.txt",ifstream::in);
        while(getline(inputfile1,line)){
            length=line.length();
            char linechar[length+5];
            strcpy(linechar,line.c_str());
            title_pos=line.find("Dillon123", 9);
            content_pos=line.find("Dillon123",title_pos+9);
            viewcount_pos=line.find("Dillon123",content_pos+9);
            res_pos=line.find("Dillon123",viewcount_pos+9);
            duration_pos=line.find("Dillon123",res_pos+9);
            if(check==1){
                out=out.assign(line, viewcount_pos+9, res_pos-viewcount_pos-9);//viewcount
            }
            else if(check==2){
                out=out.assign(line, res_pos+9, duration_pos-res_pos-9);//res
            }
            else if(check==3){
                out=out.assign(line, duration_pos+9, length-duration_pos-9);//duration
            }
            char char_out[1000]={0};
            strcpy(char_out, out.c_str());
            int charnum=0;
            charnum=atoi(char_out);
            //printf("\n---\ncharnum:%d\n---\n",charnum);
            if(charnum==inputnum){
                    string out2;
                    out2=out2.assign(line, 9, 11);//url
                    char tempturl[50];
                    strcpy(tempturl,out2.c_str());
                    ddelete2(tempturl);
            }
        }
        inputfile1.close();
}
extern "C" {
    void search_urls(char data[]) {
        checkdelete(data);
    }
    void search_titles(char data[]) {
        find_string(1,data);
    }
    void search_contents(char data[]) {
        find_string(2,data);
    }
    void search_viewcounts(char data[]) {
        find_num(1,data);
    }
    void search_ress(char data[]) {
        find_num(2,data);
    }
    void search_durations(char data[]) {
        find_num(3,data);
    }
    void new_python(char urls[],char titles[],char contents[],char viewcounts[],char ress[],char durations[]) {
        new_data(urls,titles,contents,viewcounts,ress,durations);
    }
    void delete_urls(char data[]) {
        ddelete(data);
    }
    void delete_titles(char data[]) {
        delete_string(1,data);
    }
    void delete_contents(char data[]) {
        delete_string(2,data);
    }
    void delete_viewcounts(char data[]) {
        delete_num(1,data);
    }
    void delete_ress(char data[]) {
        delete_num(2,data);
    }
    void delete_durations(char data[]) {
        delete_num(3,data);
    }
}
