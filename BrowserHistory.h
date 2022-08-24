#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>     // std::next, std::prev
#include <list>

using std::string;

struct Website {
  std::string url;
  size_t filesize;
  Website() {url = ""; filesize = 0;}
  Website(std::string url_, size_t filesize_) {url = url_; filesize = filesize_;}
};


class BrowserHistory {
public:
    BrowserHistory();
    BrowserHistory(std::string url, size_t filesize);

    void visitSite(string url, size_t filesize);
    void backButton();
    void forwardButton();
    void readFile(std::string fileName);


    string currentUrl();
    size_t currentPageSize();
    size_t getHistoryLength();

private:
  std::list<Website> wlist;
  std::list<Website>::iterator it1, it2;
  int historyLength;

  // TO BE COMPLETED
};

//Default Constructor
BrowserHistory::BrowserHistory() {
  wlist = std::list<Website>();
  it1 = wlist.begin();
  it2 = wlist.begin();
  historyLength = 0;
}

//Returns Current URL
string BrowserHistory::currentUrl() {
  if(it1 == wlist.end()) {
    return "";
  }
  std::string url = it1->url;
  return url;
};

//Returns filesize
size_t BrowserHistory::currentPageSize() {
  if(it1 == wlist.end()) {
    return 0;
  }
  size_t filesize = it1->filesize;
  return filesize;
};

//Returns History Length
size_t BrowserHistory::getHistoryLength() {
  return historyLength;
};

//Moves list iterator back
void BrowserHistory::backButton(){
  if (it1 != wlist.begin()) {
    it1--;
  }
}

//Moves iterator forward
void BrowserHistory::forwardButton(){
  it1++;
  if (it1 == wlist.end()) {
    it1--;
  }
}


//Visit Site Function that also removes history if a new site is added in the middle of the list
void BrowserHistory::visitSite(std::string url, size_t pagesize){
  while (it1 != it2) {
    it2--;
    historyLength--;
    wlist.pop_back();
  }
  Website temp(url, pagesize);
  wlist.push_back(temp);
  historyLength++;
  it1++;
  it2 = it1;
}

//Read File Function
void BrowserHistory::readFile(std::string filename){
  std::string test;
  std::string url;
  size_t num;
  int x = 0;
  std::ifstream file;

  file.open(filename);
  while (file >> test) {

    if (test.compare("visit") == 0) {
      file >> url >> num;
      visitSite(url, num);
    }

    if (test.compare("back") == 0) {
      backButton();
    }

    if (test.compare("forward") == 0){
      forwardButton();
    }
  }
  file.close();

}
