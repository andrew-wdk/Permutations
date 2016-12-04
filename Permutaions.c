/*
	This code prints all possible permutations for a given set of characters (without repetition).
	The user should input the size of the set and the length of each permutaion as the main arguments
	then the members of the set (single characters) are inputed one by one.
*/


#include <stdio.h>
#include <cs50.h>

bool repeated(int p, char* mem, int* memt, char* N);
int perm (int p, char* mem, int* memt, char* N);
long long factorial(long long n);

int w = 0;
int n;
int k;

int main (int argc, char** argv)
{
    n = atoi(argv[1]); // number of characters
    k = atoi(argv[2]); // number of positions
    
    // holds the last writen character in postition k
    char mem[k];
    
    // holds the number of the next character
    int memt[k];
    for (int i = 0; i < k; i++)
        memt[i] = 0;
    
    // holds the inputed characters
    char N[n];
    for (int i = 0; i < n; i++)
        N[i] = GetChar();
    
    perm(0, mem, memt, N, n, k);
    
    // number of permutations
    long long P = factorial(n) / factorial(n-k);
    
    printf("P = %lld", P);

    return 0;
}

int perm (int p, char* mem, int* memt, char* N) 
            //p indicates the position of the character to be writen
{
    //checks if the next character is repeated 
    GO: while (repeated(p, mem, memt, N))
    {   
        memt[p]++; //skip character
        
        if (memt[p] == n) // if the skiped character was the last one
        {
            memt[p] = 0;
            w = 0;          //indicates that the characters in previous positions are not writen
            return 0;
        }
    }
    
    //write the previous characters (if any)
    if (w == 0)
    {
        for (int i = 0; i < p; i++)
        {
            printf("%c", mem[i]);
        }
    }
    
    // writes the current character, update mem, update memt
    printf("%c", N[memt[p]]);
    mem[p] = N[memt[p]];
    memt[p]++;
    
    if (memt[p] == n) // if the writen character is the last one
    {
        memt[p] = 0;
        
        if (p == k-1) // if last position, go to new line
        {   
            printf("\n");
            w = 0;
        }
        else          
        {
            w = 1; // indicate previous characters are writen
            perm(p+1, mem, memt, N);
        }
        return 0;
    }
    else if (p == k-1) // not the last character, last position
    {
        printf("\n");
        w = 0;
        goto GO;
    }
    else // not last character, not last position
    {
        w = 1;
        perm(p+1, mem, memt, N);                    // if last character -> return to previous position
        goto GO;                                    // if not -> goto (same position)
    }
}
       

bool repeated(int p, char* mem, int* memt, char* N)
{  
    for (int i = 0; i < p; i++)
    {
        if (N[memt[p]] == mem[i])
            return true;
    }
    return false;
}

long long factorial(long long n)
{    
    if (n > 1)
        n = n * factorial(n-1);
        
    return n;
}
