//
// Created by Ishay Hil on 12/01/2020.
//

#include <vector>
#include <iostream>
#include <string>
#include "HashMap.hpp"
#include "boost/filesystem.hpp"
#include "boost/tokenizer.hpp"
#define COMMA_STR ","
#define USAGE "Usage:  SpamDetector <database path> <message path> <threshold>"

using std::vector;
using std::cout;
using std::string;
using std::endl;


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

void parseCsv(std::string &path, HashMap<string, int> &map)
{
    if (!boost::filesystem::exists(path))
    {
        cout << "file not exist" << endl;
        exit(EXIT_FAILURE);
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
        if (currentLine.empty())
        {
            ifstream.close();
            cout << "invalid file" << endl;
            exit(EXIT_FAILURE);
        }
        std::vector<std::string> tokens;
        for (const auto &t: tok)
        {
            tokens.push_back(t);
        }
        if (!validVector(tokens))
        {
            ifstream.close();
            cout << "invalid file" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            string phrase = tokens[0];
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
    std::ifstream ifstream(path);
    if (ifstream.peek() == std::ifstream::traits_type::eof())
    { // empty file
        ifstream.close();
        return 0;
    }
    char c;
    string str;
    while (ifstream >> c)
    {
        str += c;
    }
    int sum = 0;
    for (auto &tuple: map)
    {
        int cnt = cntSubstr(str, tuple.first);
        sum += (cnt * tuple.second);
    }
    ifstream.close();
    return sum;
}

int main(int argc, char *args[])
{
    if (argc != 4)
    {
        std::cout << USAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    string strThreshold = extractInput(3, args);
    if (!validStrInt(strThreshold))
    {
        std::cout << "Invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    int threshold = std::stoi(strThreshold);
    if (threshold <= 0)
    {
        std::cout << "Invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }
    string csvPath = extractInput(1, args);
    string textPath = extractInput(2, args);

    HashMap<string, int> map;
    parseCsv(csvPath, map);
    if (calculateTextScore(textPath, map) >= threshold)
    {
        cout << "SPAM";
    }
    else
    {
        cout << "NOT_SPAM";
    }
    return EXIT_SUCCESS;
}