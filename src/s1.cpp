#include <iostream>
#include <httpserver.hpp>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace httpserver;
using namespace std;

class S1_get_resource : public http_resource {
public:
    const std::shared_ptr<http_response> render(const http_request&) {
    	string head = "default";
    	string tail = "default"; 
    	string author = "soonest_mended"; 
    	string color = "#0000ff";  
    	string res = "{\"apiversion\":\"1\", \"head\":\"" + head + "\", \"tail\":\"" + tail + "\", \"color\":\"" + color + "\", " + "\"author\":\"" + author + "\"}";
	return std::shared_ptr<http_response>(new string_response(res, 200, "application/json"));
    }
};

class S1_start_resource : public http_resource {
public:
    const std::shared_ptr<http_response> render(const http_request& req) {
	// extract information from request
	rapidjson::Document request_doc, game_doc, board_doc, you_doc;

	request_doc.Parse(req.get_content().c_str());
	assert(request_doc.HasMember("game"));
	assert(request_doc["game"].IsObject());
	assert(request_doc["game"]["id"].IsString());
	assert(request_doc["board"].IsObject());
	assert(request_doc["you"].IsObject());
	cout << request_doc["game"]["id"].GetString() << endl;

	//cout << request_doc["game"].GetString();
	//game_doc.Parse(request_doc["game"].GetString());
	//board_doc.Parse(request_doc["board"].GetString());
	//you_doc.Parse(request_doc["you"].GetString());

	//int turn = request_doc["turn"].GetInt();

	// test print some of the data
	//cout << "Turn: " << turn << endl;
	//cout << "Game ID: " << game_doc["id"].GetString() << endl;
	//cout << "Board size: " << board_doc["width"].GetInt() << " x " << board_doc["height"].GetInt() << endl;

	return std::shared_ptr<http_response>(new string_response(""));
    }

};



class S1_end_resource : public http_resource {
public:
    const std::shared_ptr<http_response> render(const http_request&) {
	return std::shared_ptr<http_response>(new string_response("", 200, "application/json"));
    }
};


class S1_move_resource : public http_resource {
public:
    const std::shared_ptr<http_response> render(const http_request&) {
	cout << "Move requested." << endl;
	// get game information
	// get board information
	// get snake information
	
	// compute move
	
	// 3 potential moves (don't move back into yourself)
	// do flood fill on each
	// move to the one with highest number of accessible open spaces
	string moves[4] = {"up", "down", "left", "right"};
	string res = "{\"move\": \"" + moves[rand() % 4] + "\" }";
	return std::shared_ptr<http_response>(new string_response(res, 200, "application/json"));
    }
};

int main(int argc, char** argv) {
    webserver ws = create_webserver(8000);

    S1_get_resource s1gr;
    ws.register_resource("/", &s1gr);

    S1_start_resource s1sr;
    ws.register_resource("/start", &s1sr);
   
    S1_move_resource s1mr;
    ws.register_resource("/move", &s1mr);

    S1_end_resource s1er;
    ws.register_resource("/end", &s1er);

    ws.start(true);
    return 0;
}
