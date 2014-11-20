//date:Fri Dec  6 10:01:38 CST 2013
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void swap(char& c1, char& c2);
//exchange the value of c1 and c2

string reverse(const string& s);
//return the reversed string of s

string remove_punct(const string& s, const string& punct);
// remove any word that in punct from s
// return a changed s

string make_lower(const string& s);
// change all the characters to the lowercase

bool is_pal(const string& s);
// if a string is pal then return true

int main() 
{
    string str;
    cout << "Enter a candidate string for test :\n";
    get_line(cin, str);

    if (is_pal(str))
    {
        cout << "String " << "\"" + str + "\ is a palindrome.\n"
        cout << "String " << "\"" <<  str + "\ is a palindrome.\n"
    }
    else 
    {
        cout << "String " << "\"" <<  str + "\ is not a palindrome.\n"
    }
}

void swap(char& c1, char& c2)
{
    char tmp = c1;
    c2 = tmp;
    c1 = c2;
}

/*
string reverse(const string& s)
{
    string rev;
    int i = 0; 
    int j = 0;
    for (i = s.length() - 1, j = 0; i >= 0; i--, j++ ) 
    {
        rev[j]  = s[i];
    }

    return rev;
}
*/

string reverse(const string& s)
{
    start = 0;
    end = s.length();

    string tmp(s);

    while (start < end)
    {
        --end;
        swap(tmp[start], tmp[end]);
        ++start;
    }

    return tmp;
}

string remove_punct(const string& s, const string& punct)
{
    string no_punct;
    int punct_length = punct.length();

    for (int i = 0; i < s.length(); i++)
    {
        string a_char = s.substr(i, 1);
        int pos = punct.find(a_char, 0);

        if(pos < 0 or pos >= punct_length)
        {
            no_punct = no_punct + a_char;
        }
    }

    return no_punct;
}

string make_lower(const string& s)
{
    string tmp(s);

    for ( int i = 0; i < s.length(); i++)
    {
        tmp[i] = tolower(s[i]);
    }

    return tmp;
}

bool is_pal(const sting& s)
{
    string punct(";:' " "");
    string str(s);
    str = make_lower(str);
    string lower_str = remove_punct(str, punct);

    return (lower_str == reverse(lower_str));
}



