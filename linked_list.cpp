#include "linked_list.h"
#include <cstddef>
#include <cassert>
#include <stdexcept>

dsc::LinkedList::Iterator& dsc::LinkedList::Iterator::operator++() {
	source_ = source_->next;
	return *this;
}

dsc::LinkedList::Iterator dsc::LinkedList::Iterator::operator++(int) {
	auto tmp = *this;
	++*this;
	return tmp;
}

int& dsc::LinkedList::Iterator::operator*() const {
	return source_->value;
}

bool dsc::LinkedList::Iterator::operator==(const Iterator& other) const {
	return source_ == other.source_;
}

bool dsc::LinkedList::Iterator::operator!=(const Iterator& other) const {
	return !(*this == other);
}

dsc::LinkedList::~LinkedList() {
	destroy();
}

dsc::LinkedList::LinkedList(const LinkedList& original) {
	copy_from(original);
}

dsc::LinkedList::LinkedList(LinkedList&& other) : head_{other.head_}, tail_{other.tail_} {
	other.head_ = nullptr;
	other.tail_ = nullptr;
}

dsc::LinkedList& dsc::LinkedList::operator=(const LinkedList& original) {
	if (this == &original) {
		return *this;
	}
	
	destroy();
	copy_from(original);
	
	return *this;
}

dsc::LinkedList& dsc::LinkedList::operator=(LinkedList&& other) {
	if (this == &other) {
		return *this;
	}
	
	destroy();
	
	head_ = other.head_;
	tail_ = other.tail_;
	
	other.head_ = nullptr;
	other.tail_ = nullptr;
	
	return *this;
}

void dsc::LinkedList::destroy() {
	while (head_ != nullptr) {
		Node* current = head_;
		head_ = current->next;
		delete current;
	} // clear list and head
	tail_ = nullptr; // clear tail
	
	assert(head_ == nullptr);
	assert(tail_ == nullptr); // confirm the above
}

void dsc::LinkedList::copy_from(const LinkedList& original) {
	for (Node* current = original.head_; current != nullptr; current = current->next) {
		append_back(current->value);
	}
}

std::size_t dsc::LinkedList::size() const {
	int counter = 0;
	
	for (Node* current = head_; current != nullptr; current = current->next) {
		++counter;
	}
	
	return counter;
}

bool dsc::LinkedList::empty() const {
	return head_ == nullptr;
}

int& dsc::LinkedList::at(std::size_t index) {
	Node* target = node_at(index);
	if (target == nullptr) {throw std::out_of_range ("index out of list bounds");}
	
	return target->value;
}

const int& dsc::LinkedList::at(std::size_t index) const {
	Node* target = node_at(index);
	if (target == nullptr) {throw std::out_of_range ("index out of list bounds");}
	
	return target->value;
}

void dsc::LinkedList::append_front(int value) {
	Node* new_head = new Node{value, head_, nullptr}; // init node w head as next, nullptr as prev
	
	if (head_ != nullptr) { // list not empty
		head_->previous = new_head; // associate new head as old head's previous
	}
	head_ = new_head; // update head to point to new node
	
	if (tail_ == nullptr) {tail_ = head_;} // empty list case
}

void dsc::LinkedList::append_back(int value) {
	Node* new_tail = new Node{value, nullptr, tail_};
	
	if (tail_ != nullptr) {
		tail_->next = new_tail; // associate new tail as old tail's next
	}
    tail_ = new_tail; // update tail to point to new node

	if (head_ == nullptr) {head_ = tail_;} // empty list case
}

int dsc::LinkedList::pop_front() {
	if (head_ == nullptr) {return -1;} // is empty // -1 appropriate return value?
	
	Node* popped_node = head_; // is populated
	int tmp = popped_node->value;

	if (popped_node->next == nullptr) { // just 1
		assert(popped_node->previous == nullptr);
		head_ = tail_ = nullptr;
	} else { // more than 1
		head_ = head_->next;
		head_->previous = nullptr;
	}
	delete popped_node;
	
	return tmp;
}

int dsc::LinkedList::pop_back() {
	if (head_ == nullptr) {return -1;} // empty list
	
	Node* popped_node = tail_;
	int tmp = popped_node->value;
	
	if (popped_node->previous == nullptr) {
		head_ = tail_ = nullptr;
	} else {
		tail_ = tail_->previous;
		tail_->next = nullptr;
	}
	delete popped_node;
	
	return tmp;
}

void dsc::LinkedList::insert(int value, std::size_t index) {
	if (index == 0) { // front case
		append_front(value);
		return;
	}
	
	Node* target = node_at(index);
	
	if (target == nullptr) { // back case
		append_back(value);
		return;
	}
	
	Node* new_node = new Node{value, target, target->previous};
	target->previous->next = new_node;
	target->previous = new_node;
}

void dsc::LinkedList::remove(std::size_t index) {
	if (index == 0) {
		pop_front();
		return;
	}
	
	Node* target = node_at(index);
	
	if (target == nullptr) {
		throw std::out_of_range ("index out of bounds");
	} else if (target->next == nullptr) {
		pop_back();
		return;
	}
	
	target->previous->next = target->next;
	target->next->previous = target->previous;
	
	delete target;
}

bool dsc::LinkedList::contains(int value) const {
	Node* current = head_;
	
	while(current != nullptr) {
		if (current->value == value) {return true;}
		current = current->next;
	}
	
	return false;
}

dsc::LinkedList::Node* dsc::LinkedList::node_at(std::size_t index) const {
	Node* current = head_;

	for (std::size_t counter = 0; counter < index; ++counter) {
		if (current == nullptr) {return nullptr;}
		current = current->next;
	}
	
	return current;
}
