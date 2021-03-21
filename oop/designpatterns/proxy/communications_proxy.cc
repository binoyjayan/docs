#include <string>
#include <sstream>
#include <memory>
#include <iostream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace std;

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

struct Pingable {
  virtual ~Pingable() = default;
  virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable {
  wstring ping(const wstring& message) override {
    return message + L" pong";
  }
};

struct RemotePong : Pingable {
  wstring ping(const wstring& message) override {
    wstring result;
    http_client client(U("http://localhost:9149/"));
    uri_builder builder(U("/api/pingpong/"));
    builder.append(message);
    pplx::task<wstring> task = client.request(methods::GET, builder.to_string())
      .then([=](http_response r) {
      return r.extract_string();
    });
    task.wait();
    return task.get();
  }
};

void tryit(Pingable& pp) {
  wcout << pp.ping(L"ping") << "\n";
}

void communication_proxy() {
  Pong pp;
  for (int i = 0; i < 3; ++i) {
    tryit(pp);
  }
}

int main() {
  communication_proxy();
  return 0;
}

