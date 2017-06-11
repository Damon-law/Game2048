#ifndef MY_TIME_H_
#define MY_TIME_H_

#include <ctime>

class MyTime
{
private:
	time_t rawtime;
	tm * timeinfo;
public:
	MyTime();
	void UpdateTime();
	int GetYear();
	int GetMonth();
	int GetYDay();
	int GetMDay();
	int GetWDay();
	int GetHour();
	int GetMinute();
	int GetSecond();
	int IsDST();
};
MyTime::MyTime() {
	UpdateTime();
}
void MyTime::UpdateTime() {
	time(&rawtime);
	timeinfo = localtime(&rawtime);
}
int MyTime::GetYear() {
	return 1900 + timeinfo->tm_year;
}
int MyTime::GetMonth() {
	return 1 + timeinfo->tm_mon;
}
int MyTime::GetYDay() {
	return 1 + timeinfo->tm_yday;
}
int MyTime::GetMDay() {
	return timeinfo->tm_mday;
}
int MyTime::GetWDay() {
	return (timeinfo->tm_wday>0) ? timeinfo->tm_wday : 7;
}
int MyTime::GetHour() {
	return timeinfo->tm_hour;
}
int MyTime::GetMinute() {
	return timeinfo->tm_min;
}
int MyTime::GetSecond() {
	return timeinfo->tm_sec;
}
int MyTime::IsDST() {
	return timeinfo->tm_isdst;
}
#endif // !MY_TIME_H_

