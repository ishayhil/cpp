//
// Created by Ishay Hil on 12/01/2020.
//

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "HashMap.hpp"
#include "boost/filesystem.hpp"
#include "boost/tokenizer.hpp"
#define COMMA_STR ","
#define SPACE ' '
#define USAGE "Usage: SpamDetector <database path> <message path> <threshold>"
#define SPAM "SPAM"
#define NOT_SPAM "NOT_SPAM"
#define INVALID_INPUT "Invalid input"

using std::vector;
using std::cout;
using std::string;
using std::endl;

void invalidInput(int code=EXIT_FAILURE)
{
    std::cerr << INVALID_INPUT << std::endl;
    exit(code);
}

bool validStrInt(string score)
{
    if (score[score.size() - 1] == '\r')
    {
        score.erase(score.size() - 1);
    }
    for (char c: score)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

bool validVector(vector<string> &v)
{
    if (v.size() != 2 || v[0].empty() || v[1].empty() || !validStrInt(v[1]))
    {
        return false;
    }
    int score = std::stoi(v[1]);
    return 0 <= score;
}

void lower(string &str)
{
    for (auto &c: str)
    {
        c = (char) tolower(c);
    }
}

bool multiComma(string &str) {
    int cnt = 0;
    for (auto c: str) {
        if (c == COMMA_STR[0]) {
            cnt++;
        }
    }
    return cnt != 1;
}

void parseCsv(std::string &path, HashMap<string, int> &map)
{
    if (!boost::filesystem::exists(path))
    {
        invalidInput();
    }

    std::ifstream ifstream(path);
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{COMMA_STR};
    std::string currentLine;

    if (ifstream.peek() == std::ifstream::traits_type::eof())
    { // empty file
        ifstream.close();
        return;
    }
    while (getline(ifstream, currentLine))
    { // in line
        tokenizer tok{currentLine, sep};
        if (currentLine.empty() || multiComma(currentLine))
        {
            ifstream.close();
            invalidInput();
        }
        std::vector<std::string> tokens;
        for (const auto &t: tok)
        {
            tokens.push_back(t);
        }
        if (!validVector(tokens))
        {
            ifstream.close();
            invalidInput();
        }
        else
        {
            string phrase = tokens[0];
            lower(phrase);
            int score = std::stoi(tokens[1]);
            map[phrase] = score;
        }
    }
    ifstream.close();
}

int cntSubstr(const string &str, const string &substring)
{
    int cnt = 0;
    string::size_type pos = 0;
    while ((pos = str.find(substring, pos)) != string::npos)
    {
        cnt++;
        pos += substring.length();
    }
    return cnt;
}

string extractInput(int ind, char *args[])
{
    string str;
    for (size_t i = 0; i < strlen(args[ind]); ++i)
    {
        str += args[ind][i];
    }
    return str;
}

int calculateTextScore(string &path, HashMap<string, int> &map)
{

    if (!boost::filesystem::exists(path))
    {
        invalidInput();
    }

    std::ifstream ifstream(path);
    if (ifstream.peek() == std::ifstream::traits_type::eof())
    { // empty file
        ifstream.close();
        return 0;
    }
    char c;
    std::stringstream strStream;

    while (ifstream.peek() != EOF)
    {
        c = (char) ifstream.get();
//        if (c != '\n' && c != '\r')
//        {
//            strStream << (char) tolower(c);
//        }
//        else if (c == '\n')
//        {
//            strStream << SPACE;
//        }
        strStream << (char) tolower(c);
    }

    string str = strStream.str();
//    cout << str << endl;

    int sum = 0;
    for (auto &tuple: map)
    {
        int cnt = cntSubstr(str, tuple.first);
//        cout << tuple.first << ", " << cnt << endl;
        sum += (cnt * tuple.second);
    }
    ifstream.close();
    return sum;
}

int main(int argc, char *args[])
{
    if (argc != 4)
    {
        std::cerr << USAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    string strThreshold = extractInput(3, args);
    if (!validStrInt(strThreshold))
    {
        invalidInput();
    }
    int threshold = std::stoi(strThreshold);
    if (threshold <= 0)
    {
        invalidInput();
    }
    string csvPath = extractInput(1, args);
    string textPath = extractInput(2, args);

    HashMap<string, int> map;
    HashMap<string, int> map2;
    parseCsv(csvPath, map);
    int score = calculateTextScore(textPath, map);
    if (score >= threshold)
    {
        cout << SPAM;
    }
    else
    {
        cout << NOT_SPAM;
    }
    cout << endl;
    return EXIT_SUCCESS;
}