#pragma once

#include <string>
#include <cstdlib>
#include <ctime>
const int MAX_LEVEL = 6;

struct SkipListNode {
	int data;
	SkipListNode** forward; // 指向第i层结点的下一个节点的指针数组

	SkipListNode(int data, int level) {
		this->data = data;
		forward = new SkipListNode * [level + 1];
		memset(forward, 0, sizeof(SkipListNode*) * (level + 1));
	}
	~SkipListNode() {
		delete[] forward;
	}
};
class SkipList
{
private:
	int level; // 跳表层数
	SkipListNode* head; // 跳跃表表头
	int randomLevel() {
		int level = 0;
		while (rand() < RAND_MAX / 2 && level < MAX_LEVEL) {
			level++;
		}
		return level;
	}
public:
	SkipList();
	~SkipList();
	void insert(int val);
	void remove(int val);
	SkipListNode* search(int val);
	void print();
};

