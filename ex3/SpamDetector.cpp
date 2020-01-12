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


bool validScore(string score)
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
    if (v.size() != 2 || v[0].empty() || v[1].empty() || !validScore(v[1]))
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

int calculateStrInStr(string &str, string &substring)
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

int calculateTextScore(string &path, HashMap<string, int> &map)
{
    std::ifstream ifstream(path);
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{" "};
    std::string currentLine;

    if (ifstream.peek() == std::ifstream::traits_type::eof())
    { // empty file
        ifstream.close();
        return 0;
    }
    tokenizer tok{ifstream, sep};
    for (const auto &t: tok)
    {

    }
    ifstream.close();

}

int main(int argc, char *args[])
{
    if (argc != 2) // todo change it
    {
        std::cout << USAGE << std::endl;
        exit(EXIT_FAILURE);
    }
    string csvPath;
    string textPath;
    for (size_t i = 0; i < strlen(args[1]); ++i)
    {
        csvPath += args[1][i];
    }
    for (size_t i = 0; i < strlen(args[2]); ++i)
    {
        textPath += args[2][i];
    }
    HashMap<string, int> map;
    parseCsv(csvPath, map);


    for (auto &t: map)
    {
        cout << t.first << ": " << t.second << endl;
    }

    return EXIT_SUCCESS;
}