#include "catch.hpp"

#include "linked_list.h"
#include "linked_list.h" // include guard test

TEST_CASE("Constructor") {
	dsc::LinkedList list;
}

TEST_CASE("At returns appropriate values by reference") {
	dsc::LinkedList list;

	list.append_back(12);
	REQUIRE(list.at(0) == 12);
	
	int& r1 = list.at(0);
	int& r2 = list.at(0);
	REQUIRE(&r1 == &r2);

	r1 = 328;
	REQUIRE(list.at(0) == 328);
}

TEST_CASE("Appending To Front") {
	dsc::LinkedList list;
	
	list.append_front(3);
	REQUIRE(list.at(0) == 3); // appending to empty list
	
	list.append_front(18);
	REQUIRE(list.at(0) == 18);
	REQUIRE(list.at(1) == 3);
}

TEST_CASE("Appending To Back") {
	dsc::LinkedList list; // new list
	
	list.append_back(44); // appending to empty list
	REQUIRE(list.at(0) == 44);

	list.append_back(583); // appending to list with at least one element
	REQUIRE(list.at(1) == 583);
}

TEST_CASE("Popping Front") {
	dsc::LinkedList list;
	
	list.append_front(52); // popping from list with one element
	
	REQUIRE(list.pop_front() == 52);
	
	list.append_front(65);
	list.append_front(93);
	
	REQUIRE(list.pop_front() == 93); // popping from list with more than one element
	REQUIRE(list.pop_front() == 65); // popping last value from list
}

TEST_CASE("Popping Back") {
	dsc::LinkedList list;
	
	list.append_front(23);
	REQUIRE(list.pop_back() == 23);
	
	list.append_back(33);
	list.append_back(8);
	REQUIRE(list.pop_back() == 8);
	REQUIRE(list.pop_back() == 33); // popping everything from multi item list
}

TEST_CASE("Insertion") {
	dsc::LinkedList list;
	list.insert(74, 0); // insert to empty list
	REQUIRE(list.at(0) == 74);
	
	list.append_back(2);
	list.insert(38, 1);
	REQUIRE(list.at(1) == 38);
	
	list.insert(88, 3); // insert at end
	REQUIRE(list.at(3) == 88);
	
	list.insert(4, 0);
	REQUIRE(list.at(0) == 4);
}

TEST_CASE("Removal") {
	dsc::LinkedList list;
	list.append_back(1);
	list.remove(0);
	REQUIRE(list.empty());
}

TEST_CASE("Copy constructed list is deep copy") {
	dsc::LinkedList src;
	src.append_back(20);
	src.append_back(21);
	src.append_back(22);
	
	dsc::LinkedList copy = src;
	
	REQUIRE(&copy.at(0) != &src.at(0));
}

TEST_CASE("Copy constructed list has same values") {
	dsc::LinkedList src;
	src.append_back(20);
	src.append_back(21);
	src.append_back(22);
	
	dsc::LinkedList copy = src;
	
	REQUIRE(copy.at(0) == src.at(0));
	REQUIRE(copy.at(1) == src.at(1));
	REQUIRE(copy.at(2) == src.at(2));
}

TEST_CASE("Copy assignment EMPTY = EMPTY") {
	dsc::LinkedList list;
	dsc::LinkedList list2 = list;
	
	REQUIRE(list2.empty());
}

TEST_CASE("Copy assignment Nonempty = empty") {
	dsc::LinkedList nonempty;
	nonempty.append_back(47);
	nonempty.append_back(46);
	nonempty.append_back(88);
	
	dsc::LinkedList empty;
	nonempty = empty;
	
	REQUIRE(nonempty.empty());
}

TEST_CASE("copy assignment nonempty = nonempty") {
	dsc::LinkedList nonempty1;
	nonempty1.append_back(46);
	nonempty1.append_back(892);
	nonempty1.append_back(462);
	
	dsc::LinkedList nonempty2;
	nonempty2.append_back(99);
	nonempty2.append_back(69);
	nonempty2.append_back(192);
	nonempty2.append_back(90);
	
	nonempty1 = nonempty2;
	
	REQUIRE(nonempty1.at(0) == 99);
	REQUIRE(nonempty1.at(1) == 69);
	REQUIRE(nonempty1.at(2) == 192);
	REQUIRE(nonempty1.at(3) == 90);
	
	REQUIRE(&nonempty1.at(0) != &nonempty2.at(0));
	REQUIRE(&nonempty1.at(1) != &nonempty2.at(1));
	REQUIRE(&nonempty1.at(2) != &nonempty2.at(2));
	REQUIRE(&nonempty1.at(3) != &nonempty2.at(3));
}

TEST_CASE("Copy assignment empty = nonempty") {
	dsc::LinkedList nonempty;
	nonempty.append_back(47);
	nonempty.append_back(46);
	nonempty.append_back(88);
	
	dsc::LinkedList empty;
	empty = nonempty;
	
	REQUIRE_FALSE(empty.empty());
	
	REQUIRE(empty.at(0) == 47);
	REQUIRE(empty.at(1) == 46);
	REQUIRE(empty.at(2) == 88);
	
	REQUIRE(&empty.at(0) != &nonempty.at(0));
	REQUIRE(&empty.at(1) != &nonempty.at(1));
	REQUIRE(&empty.at(2) != &nonempty.at(2));
}

TEST_CASE("Move constructor") {
	dsc::LinkedList nonempty;
	nonempty.append_back(12);
	nonempty.append_back(25);
	nonempty.append_back(67);
	int* test[] = {&nonempty.at(0), &nonempty.at(1), &nonempty.at(2)};
	
	dsc::LinkedList list = std::move(nonempty);
	REQUIRE(list.at(0) == 12);
	REQUIRE(list.at(1) == 25);
	REQUIRE(list.at(2) == 67);
	
	REQUIRE(&list.at(0) == test[0]);
	REQUIRE(&list.at(1) == test[1]);
}

TEST_CASE("Move assignment address ownership checking") {
	dsc::LinkedList src;
	src.append_back(808);
	src.append_back(111);
	src.append_back(39);
	src.append_back(3);
	
	int* addresses[] = {&src.at(0), &src.at(1), &src.at(2), &src.at(3)};
	
	dsc::LinkedList copy = std::move(src);
	REQUIRE(copy.at(0) == 808);
	REQUIRE(copy.at(1) == 111);
	REQUIRE(copy.at(2) == 39);
	REQUIRE(copy.at(3) == 3);
	
	REQUIRE(&copy.at(0) == addresses[0]);
	REQUIRE(&copy.at(1) == addresses[1]);
	REQUIRE(&copy.at(2) == addresses[2]);
	REQUIRE(&copy.at(3) == addresses[3]);
}

TEST_CASE("empty() test of empty list") {
	dsc::LinkedList empty;
	
	REQUIRE(empty.empty());
}

TEST_CASE("empty() test of nonempty list") {
	dsc::LinkedList nonempty;
	nonempty.append_back(75);
	nonempty.append_back(100);
	nonempty.append_back(123);
	
	REQUIRE_FALSE(nonempty.empty());
}

TEST_CASE("size() of empty list") {
	dsc::LinkedList empty;
	
	REQUIRE(empty.size() == 0);
}

TEST_CASE("size() of nonempty list") {
	dsc::LinkedList nonempty;
	nonempty.append_back(931);
	nonempty.append_back(892);
	nonempty.append_back(4672);
	
	REQUIRE(nonempty.size() == 3);
}

TEST_CASE("Contains() valid search") {
	dsc::LinkedList list;
	list.append_back(19);
	list.append_back(489);
	list.append_back(803);
	
	REQUIRE(list.contains(489));
}

TEST_CASE("!contains()") {
	dsc::LinkedList list;
	list.append_back(70);
	list.append_back(80);
	list.append_back(90);
	
	REQUIRE_FALSE(list.contains(22));
}

TEST_CASE("Iterators") {
	dsc::LinkedList list;
	list.append_back(12);
	list.append_back(542);
	list.append_back(78);
	list.append_back(999);
	
	dsc::LinkedList::Iterator it = list.begin();
	
	SECTION("Dereference of Iterator") {
		REQUIRE(*it == 12);
		it++;
	}
	
	
	SECTION("Beginning through End Iteration") {
		REQUIRE(*it == 542);
		it++;
		
		REQUIRE(*it == 78);
		it++;
		
		REQUIRE(*it == 999);
		it++;
		
		REQUIRE(*it == *list.end());
	}
	
	SECTION("Empty List Iterators") {
		dsc::LinkedList list2;
		dsc::LinkedList::Iterator it2 = list2.begin();
		
		REQUIRE(*it2 == *list2.begin());
		REQUIRE(*it2 == *list2.end());
	}
}

//TEST_CASE("Move assignment ")

