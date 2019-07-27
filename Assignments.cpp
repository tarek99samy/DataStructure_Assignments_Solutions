#include <iostream>
#include <string>
#include <vector>
#define ll long long
#define unsigned long long ull;
using namespace std;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		cout << output[i] << " ";
	cout << "\n";
}

vector<int> get_occurrences(const Data& input) {
	string pat = input.pattern, txt = input.text;	
	ll h = 1, p = 0, t = 0, N = input.text.size(), M = input.pattern.size(), j, d = 256, q = 1000000000001;
	vector<int> ans;

	for (int i = 0; i < M - 1; i++)
		h = (h * d) % q;

	for (int i = 0; i < M; i++) {
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	for (int i = 0; i <= N - M; i++) {
		if (p == t) {
			for (j = 0; j < M; j++){
				if (txt[i + j] != pat[j])
					break;
			}
			if (j == M)
				ans.push_back(i);
		}

		if (i < N - M) {
			t = (d*(t - txt[i] * h) + txt[i + M]) % q;

			if (t < 0)
				t = (t + q);
		}

	}
	return ans;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	print_occurrences(get_occurrences(read_input()));
	//system("pause");
	return 0;
}
