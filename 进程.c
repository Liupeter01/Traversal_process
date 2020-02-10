#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<TlHelp32.h>  //快照
#include<locale.h>

void displayall()
{
          setlocale(LC_ALL, "zh-CN");
          PROCESSENTRY32 pe32 = { 0 };    //进程快照信息
          pe32.dwSize = sizeof(pe32);   //设置结构体大小
          HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //创建快照
          BOOL bmore = Process32First(hprocess, &pe32);   //寻找，通过指针改变外部变量
          while (bmore)
          {
                    wprintf(L"%-ls , %40ld\n", pe32.szExeFile, pe32.th32ParentProcessID);
                    bmore = Process32Next(hprocess, &pe32);  //查找
          }
}

void closeprocessbyname(wchar_t *str)
{
          setlocale(LC_ALL, "zh-CN");
          PROCESSENTRY32 pe32 = { 0 };    //进程快照信息
          pe32.dwSize = sizeof(pe32);   //设置结构体大小
          HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //创建快照
          BOOL bmore = Process32First(hprocess, &pe32);   //寻找，通过指针改变外部变量
          while (bmore)
          {
                    if (wcscmp(str, pe32.szExeFile) == 0)
                    {
                              printf("find it\n");
                              HANDLE pro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);  //打开进程
                              TerminateProcess(pro, 0);
                    }
                    bmore = Process32Next(hprocess, &pe32);  //查找
          }
}

void closeprocessbyPID(unsigned long id)
{
          setlocale(LC_ALL, "zh-CN");
          PROCESSENTRY32 pe32 = { 0 };    //进程快照信息
          pe32.dwSize = sizeof(pe32);   //设置结构体大小
          HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //创建快照
          BOOL bmore = Process32First(hprocess, &pe32);   //寻找，通过指针改变外部变量
          while (bmore)
          {
                    if (id == pe32.th32ProcessID)
                    {
                              printf("find it\n");
                              HANDLE pro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);  //打开进程
                              TerminateProcess(pro, 0);
                    }
                    bmore = Process32Next(hprocess, &pe32);  //查找
          }
}

int main()
{
          displayall();

          closeprocessbyname(L"mspaint.exe");
          return 0;
}