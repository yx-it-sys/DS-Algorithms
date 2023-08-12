#pragma once

#include <string>
#include <cstdlib>
#include <ctime>
const int MAX_LEVEL = 6;

struct SkipListNode {
	int data;
	SkipListNode** forward; // ָ���i�������һ���ڵ��ָ������

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
	int level; // �������
	SkipListNode* head; // ��Ծ���ͷ
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

