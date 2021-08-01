#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <cstddef>
#include <functional>

namespace dsc {
class LinkedList {
	public:
		class Iterator {
			public:
			  Iterator(dsc::LinkedList::Node& source) : source_{&source} {}

			  Iterator& operator++(); // pre
			  Iterator operator++(int); // post
			  int& operator*() const; // dereference
			  bool operator==(const Iterator& other) const;
			  bool operator!=(const Iterator& other) const;
			  
			private:
			  dsc::LinkedList::Node* source_{};
		};
		
		// Constructors/destructors/overloads
		LinkedList() = default; // default constructor
		~LinkedList(); // destructor
		LinkedList(const LinkedList& original); // copy constructor
		LinkedList(LinkedList&& other); // move constructor
		LinkedList& operator=(const LinkedList& original); // copy assignment
		LinkedList& operator=(LinkedList&& other); // move assignment // write tests
	
		// Iterator helpers
		Iterator begin() {return dsc::LinkedList::Iterator{head_};};
		Iterator end() {return dsc::LinkedList::Iterator{tail_};};
		Iterator begin() const {return dsc::LinkedList::Iterator{head_};};
		Iterator end() const {return dsc::LinkedList::Iterator{tail_};};
		
		// member functions
		std::size_t size() const;
		bool empty() const;
		int& at(std::size_t index);
		const int& at(std::size_t index) const;
		void append_front(int value);
		void append_back(int value);
		int pop_front();
		int pop_back();
		void insert(int value, std::size_t index);
		void remove(std::size_t index);
		bool contains(int value) const;
	
		// functional prog functions
		LinkedList map(std::function<int (int)> func) const; // TODO
		LinkedList filter(std::function<bool (int)> func) const; //
		int reduce(std::function<int (int, int)> func) const; //

	private:
		struct Node {
			int value;
			Node* next;
			Node* previous;
		};

		Node* node_at(std::size_t index) const;
		void destroy();
		void copy_from(const LinkedList& other);
		Node* head_{};
		Node* tail_{};
	};
} // namespace dsc
#endif
