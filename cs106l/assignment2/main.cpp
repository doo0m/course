/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Na Ma"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
	std::ifstream ifs(filename);
	std::set <std::string> Stu;
	std::string str;
	// std::cout << "get_applicants" << "\n";
	if (!ifs.is_open()){
		std::cerr << "open failed" << "\n";
	}
	
	while (std::getline(ifs,str))
	{
		// std::cout << str << "\n";
		Stu.insert(str);
	}
	ifs.close();
	return Stu;
}


std::string NameHandler(std::string name) {
	// std::cout << "name handler" << "\n";
	std::string res;
	int flag = 0;

	for (auto &chr:name){
		if (flag == 0){
			res += chr;
			flag += 1;
		}

		if (flag == 1 && chr == ' '){
			flag += 1;
			continue;
		}
		if (flag == 2){
			res += chr;
			return res;
		}
			
	}
	return res;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
	std::queue <const std::string*>all_match;
	std::string target = NameHandler(name);
	// std::cout << target << "\n";

	for (auto it = students.begin(); it != students.end(); ++it){
		if (NameHandler(*it) == target){
			// std::cout << (*it) << "\n";
			all_match.push(&(*it));
		}
	}
	// std::cout << all_match.size() << "\n";
	// const std::string * str;
	// while (!all_match.empty())
	// {	
	// 	str = all_match.front();
	// 	std::cout << *str << "\n";
	// 	all_match.pop();
	// }
	
	return all_match;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
	std::string soulmate;
	int idx = 1000;
	int cnt = 0;
	if (matches.empty()){
		return "NO MATCHES FOUND.";
	}

	idx = idx % matches.size();

	while (!matches.empty()){
		if (cnt == idx){
			soulmate = *matches.front();
			return soulmate;
		}
		++cnt;
		matches.pop();
	}
	return "NO MATCHES FOUND.";
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
