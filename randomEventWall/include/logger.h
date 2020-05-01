#pragma once
#include <iostream>
#include <sstream>
#include <windows.h>
#include <string.h>
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

#define LOGLEVEL_VERBOSE 5
#define LOGLEVEL_DEBUG 4
#define LOGLEVEL_INFO 3
#define LOGLEVEL_WARN 2
#define LOGLEVEL_ERROR 1

#define LOG_VERBOSE(a) if(logLevel>=LOGLEVEL_VERBOSE){a;}
#define LOG_DEBUG(a) if(logLevel>=LOGLEVEL_DEBUG){a;}
#define LOG_INFO(a) if(logLevel>=LOGLEVEL_INFO){a;}
#define LOG_WARN(a) if(logLevel>=LOGLEVEL_WARN){a;}
#define LOG_ERROR(a) if(logLevel>=LOGLEVEL_ERROR){a;}

extern int logLevel;


//字符编码转换,STL YES!
static std::string utf8_to_gbk(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	std::wstring tmp_wstr = conv.from_bytes(str);
 
	//GBK locale name in windows
	const char* GBK_LOCALE_NAME = ".936";
	std::wstring_convert<std::codecvt_byname<wchar_t, char, mbstate_t>> convert(new std::codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
	return convert.to_bytes(tmp_wstr);
};

//extern PVZ* pvz;
//游戏内输出
struct inGameCenterCaption
{
   std::stringstream ss;
   template<typename T>
   inGameCenterCaption & operator << (const T &data){
     ss << data;
     PVZ::Caption* cap = pvz->GetCaption();
     std::string testStr = ss.str();
     std::string res;
     res = utf8_to_gbk(testStr);
     cap->Style = CaptionStyle::Center;
     cap->DisappearCountdown = 200;
     cap->SetText(res.c_str());
     return *this;
   }
   operator std::string() { return ss.str(); }
};

//彩色终端输出
inline std::ostream& blue(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
              |FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}
 
inline std::ostream& red(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, 
                FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}
 
inline std::ostream& green(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, 
              FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}
 
inline std::ostream& yellow(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, 
         FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY);
         
    return s;
}
 
inline std::ostream& white(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, 
       FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}
 
struct color {
    color(WORD attribute):m_color(attribute){};
    WORD m_color;
};
 
template <class _Elem, class _Traits>
std::basic_ostream<_Elem,_Traits>& 
      operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c)
{
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout,c.m_color);
    return i;
};
