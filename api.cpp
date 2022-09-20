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

    // EFFECTS: Returns the student at the front of the queue as a json formatted string.
    // If the queue is empty then an empty string is returned.
    string get_first_queue_position() const;

    // EFFECTS: Returns {count: number of students in the queue, results: students in the queue} 
    // as a json formatted string. If the queue is empty, count: 0 and results: null is returned.
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
    
    if (request_method == "GET" && api_request == "/api/") {
      json supported_urls = {
        {"queue_head_url", "http://localhost/queue/head/"},
        {"queue_list_url", "http://localhost/queue/"},
        {"queue_tail_url", "http://localhost/queue/tail/"}
      };
      string supported_urls_str = supported_urls.dump(4) + "\n";
      cout << "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: 160\n\n"
           << supported_urls_str;
    }
    
    else if (request_method == "POST" && api_request == "/api/queue/tail/") {
      cin >> request_body;
      request_body["position"] = ohqueue.add_queue_position(request_body["uniqname"], request_body["location"]);
      string response_body = request_body.dump(4) + "\n";
      int body_length = response_body.length();
      cout << "HTTP/1.1 201 Created\nContent-Type: application/json; charset=utf-8\nContent-Length: "
           << body_length << "\n\n" << response_body;
    }
    
    else if (request_method == "GET" && api_request == "/api/queue/head/") {
      string response_body = ohqueue.get_first_queue_position(); 
      if (!response_body.empty()) {
        int body_length = response_body.length();
        cout << "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: "
             << body_length << "\n\n" << response_body;
      } else {
        cout << "HTTP/1.1 400 Bad Request\nContent-Type: application/json; charset=utf-8\nContent-Length: 0\n\n"; 
      } 
    }
    
    else if (request_method == "GET" && api_request == "/api/queue/") {
      string response_body = ohqueue.get_all_queue_positions();
      int body_length = response_body.length();
      cout << "HTTP/1.1 200 OK\nContent-Type: application/json; charset=utf-8\nContent-Length: "
           << body_length << "\n\n" << response_body; 
    }
    
    else if (request_method == "DELETE" && api_request == "/api/queue/head/") {
      if (ohqueue.delete_first_queue_position()) {
        cout << "HTTP/1.1 204 No Content\nContent-Type: application/json; charset=utf-8\nContent-Length: 0\n\n";
      } else {
        cout << "HTTP/1.1 400 Bad Request\nContent-Type: application/json; charset=utf-8\nContent-Length: 0\n\n";
      }
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
  if (!queue.empty()) {
    json response = {
      {"uniqname", queue.front().uniqname},
      {"location", queue.front().location},
      {"position", 1}
    };
    return response.dump(4) + "\n";  
  }
  return "";
}

string OHQueue::get_all_queue_positions() const {
  if (!queue.empty()) {
    json response;
    int queue_size = queue.size();
    response["count"] = queue_size;
    json students;
    int position = 1;
    for (list<Student>::const_iterator it = queue.begin(); it != queue.end(); ++it) {
      Student student = *it;
      json student_object = {
        {"location", student.location},
        {"position", position++},
        {"uniqname", student.uniqname}  
      };
      students.push_back(student_object); 
    }
    response["results"] = students;
    return response.dump(4) + "\n";
  }

  json queue_empty_response = {
    {"count", 0},
    {"results", nullptr}
  };
  return queue_empty_response.dump(4) + "\n";
}

bool OHQueue::delete_first_queue_position() {
  if (!queue.empty()) {
    queue.pop_front();
    return true;
  }
  return false;
}