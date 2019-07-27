#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using namespace std;

struct Query {
	string type, s;
	size_t ind;
};

class QueryProcessor {
	int bucket_count;
	vector<vector<string>> elems;
	size_t hash_func(const string& s) const {
		static const long long x = 263;
		static const long long p = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = ((hash * x + s[i]) % p + p) % p;
		return ((hash % bucket_count) + bucket_count) % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) 
	{
		elems.resize(bucket_count);
	}

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		if (query.type == "check") {
			for (int i = static_cast<int>(elems[query.ind].size()) - 1; i >= 0; --i)
				cout << elems[query.ind][i] << " ";
			cout << "\n";
		}
		else {
			long long temp = hash_func(query.s);
			vector<string>::iterator it = find(elems[temp].begin(),
				elems[temp].end(), query.s);

			if (query.type == "find")
				writeSearchResult(it != elems[temp].end());

			else if (query.type == "add") {
				if (it == elems[temp].end())
					elems[temp].push_back(query.s);
			}
			
			else if (query.type == "del") {
				if (it != elems[temp].end())
					elems[temp].erase(it);
			}
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}
