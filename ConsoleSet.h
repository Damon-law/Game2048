//����̨���ڻ���������
#ifndef CONSOLE_SET_H_
#define CONSOLE_SET_H_

#include <windows.h> //HANDLE,CONSOLE_CURSOR_INFO,CONSOLE_SCREEN_BUFFER_INFO
#include <iostream>

class ConsoleSet
{
private:
	HANDLE hd;				//���
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;//����̨��Ϣ
	CONSOLE_CURSOR_INFO ccInfo;//�����Ϣ
public:
	ConsoleSet();
	bool SetForeground(short color);//����ǰ����ɫ
	bool SetBackground(short color);//������ɫ
	bool SetCursorPosition(int x, int y);//���ù�����
	bool SetCursorInvisible();
	void GetCursorPosition(PCOORD position);//��ȡ�������
	void TextOut(char * text);
	bool SetTitle(LPCWSTR lpcwstr);
	void clear();
};
//���캯��
ConsoleSet::ConsoleSet()
{
	hd = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������
	GetConsoleScreenBufferInfo(hd, &csbInfo);//��ȡ����̨������Ϣ
	GetConsoleCursorInfo(hd, &ccInfo);//��ȡ�����Ϣ
}
bool ConsoleSet::SetForeground(short color)
{
	return SetConsoleTextAttribute(hd, color | (csbInfo.wAttributes&~0xF));
}
bool ConsoleSet::SetBackground(short color)
{
	return SetConsoleTextAttribute(hd, color | (csbInfo.wAttributes&~0xF0));
}
bool ConsoleSet::SetCursorPosition(int x, int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	return SetConsoleCursorPosition(hd, position);
}
void ConsoleSet::GetCursorPosition(PCOORD position)
{
	GetConsoleScreenBufferInfo(hd, &csbInfo);
	*position = csbInfo.dwCursorPosition;
}
bool ConsoleSet::SetCursorInvisible()
{
	ccInfo.bVisible = false;
	return SetConsoleCursorInfo(hd, &ccInfo);
}
void ConsoleSet::TextOut(char * text)
{
	printf("%s", text);
}
void ConsoleSet::clear()
{
	system("cls");
}
bool ConsoleSet::SetTitle(LPCWSTR lpcwstr)
{
	return SetConsoleTitle(lpcwstr);
}
#endif // !CONSOLE_SET_H_

