//prefix Dillon123
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<cstdio>
#include <sstream>
using namespace std;
int main()
{
     ifstream inputFile;
     fstream writefi,writefi2;
     writefi.open("data_split1.txt",ios::out);
     writefi2.open("data_offset1.txt",ios::out);
     int checkurl,checktitle,checkcontent,checkviewCount,checkres,checkduration,a,b,length,offset,sum,ccount,sums;
     inputFile.open("data_out.txt",ifstream::in);  //¤¹³\input operation¡C
     string line,urlout,titleout,contentout,viewCountout,resout,durationout,out,offsetout,file1,file2;
     offset=0;
     sum=0;
     ccount=1;
     sums=0;
     while(getline(inputFile,line)){
            //cout << line << "\n";
            sum++;
            sums++;
            if(sum>1000000){//how many in each file
                offset=0;
                writefi.close();
                writefi2.close();
                stringstream s1;
                string s2;
                ccount++;
                s1<<ccount;
                s1>>s2;
                file1="data_split"+s2+".txt";
                file2="data_offset"+s2+".txt";
                //cout<<file1<<'\n';
                //cout<<file2<<'\n'<<"------"<<'\n';
                writefi.open(file1.c_str(),ios::out);
                writefi2.open(file2.c_str(),ios::out);
                sum=1;
            }
            out="";
            offsetout="";
            checkurl=-1;
            checktitle=-1;
            checkcontent=-1;
            checkviewCount=-1;
            checkres=-1;
            checkduration=-1;

            checkurl=line.find("{\"url\":\"", 0);
            checktitle=line.find(",\"title\":\"", 0);
            checkcontent=line.find(",\"content\":\"", 0);
            checkviewCount=line.find(",\"viewCount\":\"", 0);
            checkres=line.find(",\"res\":\"", 0);
            checkduration=line.find(",\"duration\":\"", 0);
            //url
            if(checkurl>=0){
                urlout=line.substr(43,11);
                //cout << urlout << "\n";
                out=out+"Dillon123"+urlout;
            }
            //title
            if(checktitle>=0){
                if(checkcontent>=0 || checkviewCount>=0 || checkres>=0 ||checkduration>=0){
                        a=checktitle+10;
                        b=line.find("\",\"", a);
                        titleout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << titleout << "\n";
                        out=out+"Dillon123"+titleout;
                }
                else{
                        a=checktitle+10;
                        b=line.find("\"}", a);
                        titleout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << titleout << "\n";
                        out=out+"Dillon123"+titleout;
                }
            }
            else{
                //cout<<"Dillon123titleempty\n";
                out=out+"Dillon123titleempty";
            }
            //content
            if(checkcontent>=0){
                if(checkviewCount>=0 || checkres>=0 ||checkduration>=0){
                        a=checkcontent+12;
                        b=line.find("\",\"", a);
                        contentout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << contentout << "\n";
                        out=out+"Dillon123"+contentout;
                }
                else{
                        a=checkcontent+12;
                        b=line.find("\"}", a);
                        contentout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << contentout << "\n";
                        out=out+"Dillon123"+contentout;
                }
            }
            else{
                //cout<<"Dillon123contentempty\n";
                out=out+"Dillon123contentempty";
            }
            //viewCount
            if(checkviewCount>=0){
                if(checkres>=0 ||checkduration>=0){
                        a=checkviewCount+14;
                        b=line.find("\",\"", a);
                        viewCountout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << viewCountout << "\n";
                        out=out+"Dillon123"+viewCountout;
                }
                else{
                        a=checkviewCount+14;
                        b=line.find("\"}", a);
                        viewCountout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << viewCountout << "\n";
                        out=out+"Dillon123"+viewCountout;
                }
            }
            else{
                //cout<<"Dillon123viewCountempty\n";
                out=out+"Dillon123viewCountempty";
            }
            //res
            if(checkres>=0){
                if(checkduration>=0){
                        a=checkres+8;
                        b=line.find("\",\"", a);
                        resout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << resout << "\n";
                        out=out+"Dillon123"+resout;
                }
                else{
                        a=checkres+8;
                        b=line.find("\"}", a);
                        resout=line.substr(a,b-a);
                        //printf("%d¡B%d\n",a,b);
                        //cout << resout << "\n";
                        out=out+"Dillon123"+resout;
                }
            }
            else{
                //cout<<"Dillon123resempty\n";
                out=out+"Dillon123resempty";
            }
            //duration
            if(checkduration>=0){
                    a=checkduration+13;
                    b=line.find("\"}", a);
                    durationout=line.substr(a,b-a);
                    //printf("%d¡B%d\n",a,b);
                    //cout << durationout << "\n";
                    out=out+"Dillon123"+durationout;
            }
            else{
                //cout<<"Dillon123durationempty\n";
                out=out+"Dillon123durationempty";
            }

            //printf("offset:%d\n",offset);
            offsetout=offsetout+urlout+' ';
            writefi2<<offsetout;
            writefi2<<ccount<<' ';
            writefi2<<offset<<' ';
            //writefi2<<'\n';
            out=out+'\n';
            length=out.length();
            offset=offset+length+1;
            writefi<<out;
            writefi2<<offset;
            writefi2<<'\n';
    }
    writefi.close();
    writefi2.close();
    printf("sums:%d\n",sums);
}
