#include <iostream>
#include <vector>
#include<queue>
#include<deque>
#include <algorithm>

#define ll long long
using std::vector;
using std::cin;
using std::cout;
using namespace std;

class thread {
public:
	int id;
	long long nextFreeTime;
	thread(int id) {
		this->id = id;
		nextFreeTime = 0;
	}
	thread() {
		id = -1, nextFreeTime = 0;
	}
	struct threadCompare {
		bool operator()(const thread &w1, const thread &w2) const {
			if (w1.nextFreeTime == w2.nextFreeTime)
				return w1.id > w2.id;
			else
				return w1.nextFreeTime > w2.nextFreeTime;
		}
	};
};


class JobQueue {
private:
	int n, m;
	vector<int> jobs_;

	vector<int> assigned_workers_;
	vector<ll> start_times_;
	vector<pair<ll, ll>> sol;

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i) {
			cout << sol[i].first << " " << sol[i].second << "\n";
		}
	}

	void ReadData() {
		cin >> n >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	void AssignJobs() {
		sol.resize(m);
		priority_queue<thread, vector<thread>, thread::threadCompare> q;
		for (int i = 0; i < n; i++) {
			q.push(thread(i));
		}

		for (int i = 0; i < m; i++) {
			thread th = q.top();
			q.pop();
			sol[i].first = th.id;
			sol[i].second = th.nextFreeTime;
			th.nextFreeTime += jobs_[i];
			q.push(th);
		}

	}

public:
	void Solve() {
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	system("pause");
	return 0;
}
