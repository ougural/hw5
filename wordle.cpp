// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
#include "vector"
using namespace std;


// Add prototypes of helper functions here
void findDashCombs(
    int numDashes,
    std::string prefix,
    std::set<std::string> &dashCombs,
    std::string alphabet);

std::set<std::string> combined(
  std::set<std::string> &dashCombs, 
	const std::string &in);

std::set<std::string> filterNonFloats(
  std::set<std::string> &fullCombs, 
	const std::string &floating);

std::set<std::string> filterNonWords(
  std::set<std::string> &firstFilter, 
	const std::set<std::string> &dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string &in,
    const std::string &floating,
    const std::set<std::string> &dict)
{
    // find num dashes and fixed indeces
    int numDashes = 0;
    for(int i = 0; i < in.size(); i++){
      if(in[i] == '-'){
        numDashes++;
      }
    }
    // find all combs for dash spaces
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::set<std::string> dashCombs;
    findDashCombs(numDashes, "", dashCombs, alphabet);
    // combine dash combs and fixeds into a new set
		std::set<std::string> fullCombs = combined(dashCombs, in);
    // filter non floats
		std::set<std::string> firstFilter = filterNonFloats(fullCombs, floating);
		// filter non words
		std::set<std::string> secondFilter = filterNonWords(firstFilter, dict);
		return secondFilter;
}

// Define any helper functions here

std::set<std::string> filterNonWords(
  std::set<std::string> &firstFilter, 
	const std::set<std::string> &dict)
{
	std::set<std::string> returnThis;
	std::set<std::string>::iterator it;
	for(it = firstFilter.begin(); it != firstFilter.end(); ++it){
		if(dict.find(*it) != dict.end()){
			// cout << *it << endl;
			returnThis.insert(*it);
		}
	}
	return returnThis;
}


std::set<std::string> filterNonFloats(
  std::set<std::string> &fullCombs, 
	const std::string &floating)
	{
		std::set<std::string> returnThis;
		std::set<std::string>::iterator it;
		for(it = fullCombs.begin(); it != fullCombs.end(); ++it){
			int ctr = 0;
			std::string temp = floating;
			for(int i = 0; i < (*it).size(); i++){
				for(int j = 0; j < temp.size(); j++){
					if((*it)[i] == temp[j]){
						temp[j] = '0';
						ctr++;
					}
				}
			}
			if(ctr == temp.size()){
				// cout << *it << endl;
				returnThis.insert(*it);
			}
		}
		return returnThis;
	}

void findDashCombs(
    int numDashes,
    std::string prefix,
    std::set<std::string> &dashCombs,
    std::string alphabet
  )
{ 
  if(prefix.size() == numDashes){
    dashCombs.insert(prefix);
  }
  else if(prefix.size() < numDashes){
    for(auto l : alphabet){
      findDashCombs(numDashes, prefix + l, dashCombs, alphabet); 
    }
  }
}

std::set<std::string> combined(
  std::set<std::string> &dashCombs, 
  const std::string &in)
{
  std::set<std::string> returnThis;

  std::set<std::string>::iterator it;
  int ctr = 0;
  for(it = dashCombs.begin(); it != dashCombs.end(); ++it){
    ctr = 0;
    std::string temp = "";
    for(int i = 0; i < in.size(); i++){
			if(in[i] != '-'){
        temp += in[i];
      }
      else{
        temp += (*it)[ctr];
        ctr++;
      }
    }
		// cout << temp << endl;
    returnThis.insert(temp);
  }
  return returnThis;  
}







