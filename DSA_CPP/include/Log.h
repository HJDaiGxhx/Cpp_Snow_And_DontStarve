#pragma once

#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
using namespace std;

class File
{
protected:
    string forePath;
    string name;
    string type;
    string path;

public:
    File() {}
    File(string p) : path(p) { setTitle(); }
    File(string s1, string s2, string s3) : forePath(s1), name(s2), type(s3)
    {
        setPath();
    }

    void setPath() { path = forePath + name + type; }
    virtual void setTitle() {}

    string getPath() { return path; }
    void setName(string s) { name = s; }
    string getName() { return name; }
};
class Log : public File
{
protected:
    static string title;
    static string date;
    static string _time;
    static string tag;
    string link;

    static string setPres(int, int);
    virtual void setTitle()
    {
        setTime();
        if (title == "")
            title = _time;
        // title = date + ' ' + _time + ' ' + tag;
    }

public:
    Log() : File() {}
    Log(string f, string ty, string folder = "", string t = "null")
    {
        setTitle();
        forePath = f;
        name = date;
        type = ty;
        setPath();
        tag = (t == "") ? "null" : t;
        link = folder + name + "#" + title;
    }

    static string setTime(char = '.', char = ':');
    virtual void function() {}
    void log()
    {
        freopen(path.c_str(), "a", stdout);
        printf("\n## %s\n#%s [[%s]]\n", title.c_str(), tag.c_str(), link.c_str());
        function();
        // freopen("CON", "w", stdout);
    }
};
class Result : public Log
{
public:
    Result() : Log() {}
    Result(string s1, string s2, string s3, string s4) : Log(s1 + "result\\", s2, s3, s4) {}

    void function()
    {
    }
};
class Code : public Log
{
protected:
    string source = "C:\\Users\\qazse\\Documents\\GitHub\\CCpp\\DSA_CPP\\main.cpp";

public:
    Code() : Log() {}
    Code(string s1, string s2, string s3, string s4) : Log(s1 + "code\\", s2, s3, s4) {}
    void function();
};

string Log::title = "";
string Log::date = "";
string Log::_time = "";
string Log::tag = "";

class Log2
{
protected:
    string SOURCE = "C:\\Users\\qazse\\Documents\\GitHub\\CCpp\\DSA_CPP\\main.cpp";
    string FOREPATH = "C:\\Users\\qazse\\Documents\\scripts\\";
    string TYPE = ".md";

    Result result;
    Code code;

public:
    Log2(string t = "null")
    {
        code = Code(FOREPATH, TYPE, "result/", t);
        code.log();
        result = Result(FOREPATH, TYPE, "code/", t);
        result.log();
    }
};

// set date and time precision from 8:4:12 to 08:04:12...
string Log::setPres(int i, int limit = 10)
{
    string s2 = to_string(i);
    if (i < limit)
        s2.insert(0, "0");
    return s2;
}
// date = yyyy.mm.dd, _time = hh:mm:ss.
string Log::setTime(char c1, char c2)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    ltm->tm_year += 1900;
    ltm->tm_mon++;

    string s, s1;
    if (date == "")
    {
        s1 = c1;
        s.append(to_string(ltm->tm_year));
        s.append(s1);
        // 先一个粗糙版
        s.append(setPres(ltm->tm_mon));
        s.append(s1);
        s.append(setPres(ltm->tm_mday));
        date = s;
    }

    // 真的感觉很麻瓜，很菜
    if (_time == "")
    {
        s.clear();
        s1 = c2;
        s.append(setPres(ltm->tm_hour));
        s.append(s1);
        s.append(setPres(ltm->tm_min));
        s.append(s1);
        s.append(setPres(ltm->tm_sec));
        _time = s;
    }
    return date + "_" + _time;
}
void Code::function()
{
    cout << "```" << endl;

    ifstream readFile;
    readFile.open(source, ios::out);
    if (!readFile)
        return;

    int size = 500;
    for (char c[size]; readFile.getline(&c[0], size);)
    {
        string s = c;
        int pos = s.find('/');

        if (pos == 0 || c[pos - 2] == ' ') // 因为vscode自动修正格式，我感觉不会下标出错
        {
            if (c[pos + 1] == '*')
            {
                pos = -1;
                while (pos == -1 && readFile.getline(&c[0], size))
                {
                    string s = c;
                    pos = s.find("*/");
                }
            }
        }
        else if ((pos = s.find("main")) != -1)
        {
            cout << "```" << endl;
            return;
        }
        else if (c[0] != '#' && c[0] != '\000')
            cout << s << endl;
    }
}

#endif