//控制台窗口环境配置类
#ifndef CONSOLE_SET_H_
#define CONSOLE_SET_H_

#include <windows.h> //HANDLE,CONSOLE_CURSOR_INFO,CONSOLE_SCREEN_BUFFER_INFO
#include <iostream>

class ConsoleSet
{
private:
	HANDLE hd;				//句柄
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;//控制台信息
	CONSOLE_CURSOR_INFO ccInfo;//光标信息
public:
	ConsoleSet();
	bool SetForeground(short color);//设置前景颜色
	bool SetBackground(short color);//背景颜色
	bool SetCursorPosition(int x, int y);//设置光标左边
	bool SetCursorInvisible();
	void GetCursorPosition(PCOORD position);//获取光标坐标
	void TextOut(char * text);
	bool SetTitle(LPCWSTR lpcwstr);
	void clear();
};
//构造函数
ConsoleSet::ConsoleSet()
{
	hd = GetStdHandle(STD_OUTPUT_HANDLE);//获取输入句柄
	GetConsoleScreenBufferInfo(hd, &csbInfo);//获取控制台窗口信息
	GetConsoleCursorInfo(hd, &ccInfo);//获取光标信息
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

