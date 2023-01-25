#include <iostream>
#include <vector>
using namespace std;

int arr[100005], seg[4 * 100005], lazy[4 * 100005], n;

void build(int node, int low, int high)
{
    if (low == high)
    {
        seg[node] = arr[low];
        lazy[node] = 0;
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * node + 1, low, mid);
    build(2 * node + 2, mid + 1, high);
    seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
    lazy[node] = 0;
}

int query(int node, int low, int high, int range_low, int range_high)
{
    if (low > high)
        return INT_MAX;

    if (lazy[node] != 0)
    {
        seg[node] += lazy[node];
        if (low != high) // if its not a leaf node as for leaf node we don't have child nodes
        {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (range_low > high || range_high < low) // no overlap
        return INT_MIN;

    if (range_low <= low && high <= range_high) // total overlap
        return seg[node];

    int mid = low + (high - low) / 2;
    int lt = query(2 * node + 1, low, mid, range_low, range_high);      // query on left subhalf
    int rt = query(2 * node + 2, mid + 1, high, range_low, range_high); // query on right subhalf
    return seg[node] = max(lt, rt);
}

void pointUpdate(int node, int low, int high, int range_low, int range_high, int val)
{
    if (low > high)
        return;

    /*
        First thing to check when visit a node is to check the lazy tree for current node
        And propagate the value of lazy tree to the child nodes
    */
    if (lazy[node] != 0)
    {
        seg[node] += lazy[node];
        if (low != high) // if its not a leaf node as for leaf node we don't have child nodes
        {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
        lazy[node] = 0;
    }

    // fully overlap so act lazy
    if (range_low <= low && high <= range_high)
    {
        seg[node] += val;
        if (low != high)
        {
            lazy[2 * node + 1] += val;
            lazy[2 * node + 2] += val;
            seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    // partial overlap so make calls on both sides
    else if (low < range_low && range_high < high)
    {
        int mid = (low + high) >> 1;
        pointUpdate(2 * node + 1, low, mid, range_low, range_high, val);
        pointUpdate(2 * node + 2, mid + 1, high, range_low, range_high, val);

        seg[node] = max(seg[2 * node + 1], seg[2 * node + 2]);
    }
    else if (range_high < low || range_low > high)
        return;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    build(0, 0, n - 1);

    int q;
    cin >> q;
    while (q--)
    {
        int range_low, range_high;
        cin >> range_low >> range_high;
        cout << query(0, 0, n - 1, range_low, range_high) << endl;
    }
    return 0;
}