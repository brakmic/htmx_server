#define CROW_STATIC_DIRECTORY ""
#include <crow.h>

#include <iostream>

int main() {
  crow::SimpleApp app;
  crow::mustache::set_global_base(".");

  CROW_ROUTE(app, "/")
  ([]() {
    auto page = crow::mustache::load_text("index.html");
    return page;
  });

  CROW_ROUTE(app, "/data")
  ([]() { return "<strong>Hello, htmx!</strong>"; });

  CROW_ROUTE(app, "/<path>")
  ([&app](const std::string& path) {
    crow::response res;
    res.response::set_static_file_info(path);
    return res;
  });

  app.bindaddr("127.0.0.1")
      .ssl_file("ssl/server.crt", "ssl/server.key")
      .port(8082)
      .multithreaded()
      .run();
}