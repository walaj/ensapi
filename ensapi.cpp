#include <iostream> 
#include <fstream>
#include <string>
#include <vector>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

//using namespace utility;                    // Common utilities like string conversions
//using namespace web;                        // Common features like URIs.
//using namespace web::http;                  // Common HTTP functionality
//using namespace web::http::client;          // HTTP client features
//using namespace concurrency::streams;       // Asynchronous streams

int main(int argc, char** argv) {
  int ret = 0;

  bool verbose = false;

  std::vector<std::string> queries; // = {"ENSG00000157764","ENSG00000157764"};5D

  // read the file
  std::string line;
  if (argc > 1) {
    std::ifstream in(argv[1]);
    while (std::getline(in, line)) 
      queries.push_back(line);
  } else {
    while (std::getline(std::cin, line)) 
      queries.push_back(line);
  }

  for (auto& q : queries) {

    // Open stream to output file.
    // Create http_client to send the request.
    web::http::client::http_client client("http://rest.ensembl.org/");
    
    // Build request URI and start the request.
    web::http::uri_builder builder("/sequence/id/" + q);
    //builder.append_query("q", "cpprestsdk github");

    if (verbose)
      std::cerr << "Path: " << builder.path() << std::endl;

    web::http::http_request request(web::http::methods::GET);
    request.headers().set_content_type("text/plain");
    request.set_request_uri(builder.to_string());
    
    pplx::task<int> requestTask = client.request(request)

    // Handle response headers arriving.
    .then([=](web::http::http_response response)
	  {
	    if (verbose)
	      fprintf(stderr, "Received response status code:%u\n", response.status_code());
	    
	    // Write response body into the file.
	    return response.extract_string(); //.read_to_end(fileStream->streambuf());
	  })
   .then([=](utility::string_t s)
    	  {
	    std::cout << ">" << q << std::endl << s << std::endl;
	    return 0;
	    //return fileStream->close();
      });

  // Wait for all the outstanding I/O to complete and handle any exceptions
    try
      {
        requestTask.wait();
      }
    catch (const std::exception &e)
      {
        fprintf(stderr, "Error exception:%s on %s\n", e.what(), q.c_str());
      }
  }

  // your code goes here
  return ret;
} 
