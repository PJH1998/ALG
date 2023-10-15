#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

vector<vector<int>> adj(6, vector<int>(6, -1));


void CreateGraph()
{
    adj[0][1] = 15;
    adj[0][3] = 35;
    adj[1][0] = 15;
    adj[1][2] = 5;
    adj[1][3] = 10;
    adj[3][4] = 5;
    adj[5][4] = 5;
}

void Dijikstra(int here)
{
    struct VC
    {
        int vertex;
        int cost;
    };

    queue<VC> discovered;
    vector<int> best(6, INT32_MAX);

    discovered.push(VC{here, 0});

    int cnt = 0;
    
    while (discovered.empty() == false)
    {
        const VC vc = discovered.front();
        const int v = vc.vertex;
        const int c = vc.cost;
        discovered.pop();

        cout << v << " / " << c << endl;
        cnt++;

        if (best[v] <= c)
            continue;

        best[v] = c;
        here = v;

        for (int there = 0; there < 6; there++)
        {
            if (adj[here][there] == -1)
                continue;
            discovered.push(VC{ there, best[v] + adj[here][there]});
        }
    }

    cout << cnt << endl;
}

void Dijikstra_list(int here)
{
    struct VC
    {
        int vertex;
        int cost;
    };

    list<VC> discovered;
    vector<int> best(6, INT32_MAX);
    vector<int> parent(6, -1);

    discovered.push_back(VC{ here , 0 });
    best[here] = 0;
    parent[here] = 0;

    int cnt = 0;

    while (discovered.empty() == false)
    {
        //제일 좋은 후보
        list<VC>::iterator bestIt;
        int bestCost = INT32_MAX;

        //코스트가 제일 낮은 후보 서치
        for (auto it = discovered.begin(); it != discovered.end(); it++)
        {
            if (it->cost < bestCost)
            {
                bestCost = it->cost;
                bestIt = it;
            }
        }

        int cost = bestIt->cost;
        here = bestIt->vertex;
        discovered.erase(bestIt);

        cout << here << " / " << cost << endl;
        cnt++;

        //방문 전 이미 더 짧은 길을 찾았다면 스킵
        if (best[here] < cost)
            continue;

        for (int there = 0; there < 6; there++)
        {
            if (adj[here][there] == -1)
                continue;
            
            int nextCost = best[here] + adj[here][there];
            if (nextCost >= best[there])
                continue;

            discovered.push_back(VC{ there, nextCost });
            best[there] = nextCost;
            parent[there] = here;
        }
    }

    cout << cnt << endl;
}

int main()
{
    CreateGraph();

    Dijikstra_list(0);

    return 0;
}

//불필요한 길을 막을 수는 없다
//단지 붙어있는 버텍스중 우선적으로 가까운 곳을 향해 이동한다. 