#include<iostream>
#include<stack>
#include<queue>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<set>
#include<unordered_set>
#include<list>
#include<vector>
#include<map>
#include<deque>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
	int key;
	Node *parent;
	std::vector<Node *> children;

	Node() {
		this->parent = NULL;
	}

	void setParent(Node *theParent) {
		parent = theParent;
		parent->children.push_back(this);
	}
};


int main_with_large_stack_space() {
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;
	int rootindx = -1;
	std::vector<Node> nodes;
	nodes.resize(n);
	for (int child_index = 0; child_index < n; child_index++) {
		int parent_index;
		std::cin >> parent_index;
		if (parent_index >= 0)
			nodes[child_index].setParent(&nodes[parent_index]);
		else
			rootindx = child_index;
		nodes[child_index].key = child_index;
	}

	
	int maxHeight = 0;
	std::queue<Node> q;
	q.push(nodes[rootindx]);
	while (1) {
		int ncnt = q.size();	Node temp;
		if (ncnt == 0)
			break;

		maxHeight++;

		while (ncnt--) {
			temp = q.front();
			q.pop();
			for (int i = 0; i < temp.children.size(); i++)	{
				q.push(*(temp.children[i]));
			}
		}
	}

	std::cout << maxHeight << std::endl, 0;
	system("pause");
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}

#endif
	return main_with_large_stack_space();
}
