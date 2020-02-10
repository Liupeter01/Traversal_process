#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<TlHelp32.h>  //����
#include<locale.h>

void displayall()
{
          setlocale(LC_ALL, "zh-CN");
          PROCESSENTRY32 pe32 = { 0 };    //���̿�����Ϣ
          pe32.dwSize = sizeof(pe32);   //���ýṹ���С
          HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //��������
          BOOL bmore = Process32First(hprocess, &pe32);   //Ѱ�ң�ͨ��ָ��ı��ⲿ����
          while (bmore)
          {
                    wprintf(L"%-ls , %40ld\n", pe32.szExeFile, pe32.th32ParentProcessID);
                    bmore = Process32Next(hprocess, &pe32);  //����
          }
}

void closeprocessbyname(wchar_t *str)
{
          setlocale(LC_ALL, "zh-CN");
          PROCESSENTRY32 pe32 = { 0 };    //���̿�����Ϣ
          pe32.dwSize = sizeof(pe32);   //���ýṹ���С
          HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //��������
          BOOL bmore = Process32First(hprocess, &pe32);   //Ѱ�ң�ͨ��ָ��ı��ⲿ����
          while (bmore)
          {
                    if (wcscmp(str, pe32.szExeFile) == 0)
                    {
                              printf("find it\n");
                              HANDLE pro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);  //�򿪽���
                              TerminateProcess(pro, 0);
                    }
                    bmore = Process32Next(hprocess, &pe32);  //����
          }
}

void closeprocessbyPID(unsigned long id)
{
          setlocale(LC_ALL, "zh-CN");
          PROCESSENTRY32 pe32 = { 0 };    //���̿�����Ϣ
          pe32.dwSize = sizeof(pe32);   //���ýṹ���С
          HANDLE hprocess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  //��������
          BOOL bmore = Process32First(hprocess, &pe32);   //Ѱ�ң�ͨ��ָ��ı��ⲿ����
          while (bmore)
          {
                    if (id == pe32.th32ProcessID)
                    {
                              printf("find it\n");
                              HANDLE pro = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);  //�򿪽���
                              TerminateProcess(pro, 0);
                    }
                    bmore = Process32Next(hprocess, &pe32);  //����
          }
}

int main()
{
          displayall();

          closeprocessbyname(L"mspaint.exe");
          return 0;
}