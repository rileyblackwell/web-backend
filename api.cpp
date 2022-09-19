#include <iostream>
#include <list>
#include <cassert>
#include "json.hpp"

using nlohmann::json;
using namespace std; 


class OHQueue {
public:
    // EFFECTS: Creates an empty queue.
    OHQueue();

    // MODIFIES: queue
    // EFFECTS: Adds a student to the end of the queue.
    // Returns the queue position for the added student.
    int add_queue_position(const string &uniqname, const string &location);

    string get_first_queue_position() const;

    string get_all_queue_positions() const;

    // MODIFIES: queue
    // EFFECTS: Returns true if a student was deleted from the queue.
    // Returns false if no student was deleted because the queue was empty. 
    bool delete_first_queue_position();

private:
  struct Student {
    string uniqname;
    string location;
  };
  list<Student> queue;
};


int main() {
  OHQueue ohqueue;
  string request_method;
  string api_request;
  string headers;
  json request_body;
  while (cin >> request_method >> api_request) {
    // Removes unneeded headers from standard input.
    for (int i = 0; i < 8; ++i) {
      cin >> headers;
    }
    if (request_method == "POST" && api_request == "/api/queue/tail/") {
      cin >> request_body;
      request_body["position"] = ohqueue.add_queue_position(request_body["uniqname"], request_body["location"]);
      string response_body = request_body.dump(4) + "\n";
      int body_length = response_body.length();
      cout << "HTTP/1.1 201 Created\nContent-Type: application/json; charset=utf-8\nContent-Length: "
           << body_length << "\n\n" << response_body;
    }
    else if (request_method == "DELETE" && api_request == "/api/queue/head/") {
      if (ohqueue.delete_first_queue_position()) {
        cout << "HTTP/1.1 204 No Content\nContent-Type: application/json; charset=utf-8\nContent-Length: 0\n\n";
      } else {
        cout << "HTTP/1.1 400 Bad Request\nContent-Type: application/json; charset=utf-8\nContent-Length: 0\n\n";
      }
    }
    else if (request_method == "GET" && api_request == "/api/") {

    }
    else if (request_method == "GET" && api_request == "api/queue/head/") {

    }
    else if (request_method == "GET" && api_request == "api/queue/") {

    }
    else {
      if (headers != "0") {
        cin >> request_body;
      }
      cout << "HTTP/1.1 400 Bad Request\nContent-Type: application/json; charset=utf-8\nContent-Length: 0\n\n";  
    }
    
  }
  
  return 0;
}


OHQueue::OHQueue() : queue() {}

int OHQueue::add_queue_position(const string &uniqname, const string &location) {
  Student student;
  student.uniqname = uniqname;
  student.location = location;
  queue.push_back(student);
  return queue.size();
}

string OHQueue::get_first_queue_position() const {
  assert(false);
}

string OHQueue::get_all_queue_positions() const {
  assert(false);
}

bool OHQueue::delete_first_queue_position() {
  if (!queue.empty()) {
    queue.pop_front();
    return true;
  }
  return false;
}