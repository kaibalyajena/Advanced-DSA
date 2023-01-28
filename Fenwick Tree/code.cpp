#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Fenwick trees are data structures very effective for range queries
// The build time for fenwick tree is O(nlogn)
// The update time is O(logn)
// Space is O(n)
// Time to access element O(logn)

// these are in global scope as all functions are updating these containers or variables so there's
//  no need to pass them as arguments to the functions

vector<int> fen(17, 0);
vector<int> a({-1, 1, 0, 2, 1, 1, 3, 0, 4, 2, 5, 2, 2, 3, 1, 0, 2}); // -1 element as 0th index is the dummy node
// we are following 1 based indexing for fenwick trees
int n = 16;

void build()
{
    for (int i = 1; i <= n; i++)
    {
        int l = i & (i - 1); // turn off rightmost set bit
        l++;
        int r = i;
        int temp = 0;

        for (int j = l; j <= r; j++)
        {
            temp += a[j];
        }

        fen[i] = temp;
    }
}

void update(int i, int add)
{
    a[i] += add;
    while (i <= n)
    {
        fen[i] += add;
        i += (i & (-i));
    }
}

int sum(int i)
{
    int s = 0;
    while (i > 0)
    {
        s += fen[i];
        i -= (i & (-i));
    }
    return s;
}

int rangeSum(int l, int r)
{
    return sum(r) - sum(l - 1); // this range is inclusive range
}

int find(int k) // this function uses binary lifting to find lower_bound
{
    int curr = 0, prevsum = 0;

    for (int i = log2(n); i >= 0; i--)
    {
        if (fen[curr + (1 << i)] + prevsum < k)
        {
            curr += (1 << i);
            prevsum += fen[curr];
        }
    }

    return (curr + 1);
}

/*
    For more info you can find articles on codeforces and topcoders on Binary Lifitng and Fenwick Trees
*/

int main()
{

    return 0;
}