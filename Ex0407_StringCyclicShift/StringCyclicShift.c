#include <stdio.h>
#include <string.h>
#define MAXSIZE 200

void NEXT(const char T[], int next[]) 
{
    next[0] = -1;

    for (int i = 1; i < strlen(T); i++)
    {
        int j = next[i - 1];

        while (j >= 0 && T[i - 1] != T[j])
        {
            j = next[j];
        }

        if (j >= 0 && T[i - 1] == T[j])
        {
            next[i] = j + 1;
        }
        else
        {
            next[i] = 0;
        }
    }
}

int KMP(const char S[], const char T[]) 
{
    // find number of string T in string S
    int next[MAXSIZE];
    NEXT(T, next);

    int index, count = 0;
    for (index = 0; index < strlen(S); ++index)
    {
        int pos = 0;
        int iter = index;
        while (pos < strlen(T) && iter < strlen(S)) 
        {
            if (S[iter] == T[pos]) 
            { 
                ++iter; ++pos;
            }
            else
            {
                if (pos == 0) 
                {
                    ++iter;
                }
                else
                {
                    pos = next[pos - 1] + 1;
                }
            }
        }

        if (pos == strlen(T) && (iter - index) == strlen(T))
        {
            ++count;
        }
    }

    return count;
}

int IsShift(const char s[], const char t[])
{
    if (strlen(s) == 0)
    {
        return 0;
    }
    if (strlen(s) != strlen(t))
    {
        return 0;
    }
    
    char s_copy[2 * MAXSIZE] = "";
    strcat(s_copy, s);
    strcat(s_copy, s);

    if (KMP(s_copy, t) >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    char s[MAXSIZE] = "asdf";
    char t[MAXSIZE] = "sdfa";
    int rslt;

    rslt = IsShift(s, t);

    printf("Origin string 1: %s\n", s);
    printf("Origin string 2: %s\n", t);

    if (rslt == 1)
    {
        printf("They are shift strings.\n");
    }
    else
    {
        printf("They are not shift strings.\n");
    }
    return 0;
}
