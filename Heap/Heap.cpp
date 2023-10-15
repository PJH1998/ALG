#include <iostream>
#include <vector>
using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
    void push(const T& data)
    {
        _heap.push_back(data);

        int now = static_cast<int>(_heap.size()) - 1;

        while (now > 0)
        {
            int next = (now - 1) / 2;
            if (_predicate(_heap[now], _heap[next]))
                break;

            swap(_heap[now], _heap[next]);
            now = next;
        }

    }

    void pop()
    {
        _heap[0] = _heap.back();
        _heap.pop_back();

        int now = 0;

        while (true)
        {
            int left = now * 2 + 1;
            int right = now * 2 + 2;

            if (left >= _heap.size())
                break;

            int next = now;

            if (_predicate(_heap[next], _heap[left]))
                next = left;

            if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
                next = right;

            if (next == now)
                break;

            swap(_heap[now], _heap[next]);

            now = next;

        }
    }

    T& top()
    {
        return _heap[0];
    }

    bool empty()
    {
        return _heap.empty();
    }

private:

    Container _heap = {};
    Predicate _predicate = {};

};

int main()
{
    PriorityQueue<int, vector<int>, greater<int>> q;

    q.push(100);
    q.push(200);
    q.push(300);
    q.push(400);
    q.push(500);

    while (q.empty() == false)
    {
        cout << q.top() << endl;
        q.pop();
    }
}
