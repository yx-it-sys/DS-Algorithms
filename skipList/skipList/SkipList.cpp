#include "SkipList.h"
#include <stdio.h>

SkipList::SkipList()
{
	level = 0;
	head = new SkipListNode(0, MAX_LEVEL);
}

SkipList::~SkipList()
{
	delete head;
}

void SkipList::insert(int val)
{
	SkipListNode* update[MAX_LEVEL + 1];
	memset(update, 0, sizeof(SkipListNode*) * (MAX_LEVEL + 1));
	SkipListNode* current = head;
		for (int i = level; i >= 0; i--) {
			while (current->forward[i] != nullptr && current->forward[i]->data < val) {
				current = current->forward[i];
			}
			update[i] = current;
		}
		current = current->forward[0];

		int newLevel = randomLevel();
		if (newLevel > level) {
			for (int i = level + 1; i <= newLevel; i++) {
				update[i] = head;
			}
			level = newLevel;
		}
		SkipListNode* node = new SkipListNode(val, newLevel);
		for (int i = 0; i <= newLevel; i++) {
			node->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = node;
		}
}

void SkipList::remove(int val)
{
	SkipListNode* current = head;
	SkipListNode* update[MAX_LEVEL + 1];
	memset(update, 0, sizeof(SkipListNode*) * (MAX_LEVEL + 1));

	for (int i = level; i >= 0; i--) {
		while (current->forward[i] != nullptr && current->forward[i]->data < val) {
			current = current->forward[i];
		}
		update[i] = current;
	}
	current = current->forward[0];
	if (current && current->data == val) {
		for (int i = 0; i <= level; i++) {
			if (update[i]->forward[i] == current) {
				update[i]->forward[i] = current->forward[i];
			}
			while (level > 0 && head->forward[level] == nullptr) {
				level--;
			}
		}
	}
	delete current;
}


SkipListNode* SkipList::search(int val)
{
	SkipListNode* current = head;

	for (int i = level; i >= 0; i--) {
		while (current->forward != nullptr && current->forward[i] != nullptr && val > current->forward[i]->data) {
			current = current->forward[i];
		}
	}
	current = current->forward[0];

	if (current && current->data == val) {
		return current;
	}
	else {
		return nullptr;
	}
}

void SkipList::print()
{
	for (int i = level; i >= 0; i--) {
		printf("µÚ%d²ã±í£º", i + 1);
		SkipListNode* p = head->forward[i];
		while (p != nullptr) {
			printf("%d%s", p->data, p->forward[i] ? "-->" : "");
			p = p->forward[i];
		}
		printf("\n");
	}
}
