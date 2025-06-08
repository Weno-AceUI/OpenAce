#include <crow/app.h>
#include <crow/json.h>
#include <vector>
#include <mutex>
#include <string>
#include <ctime>

// User data structures
struct Contact {
    uint64_t id;
    std::string name;
    std::string phone;
    std::string email;
    bool favorite;
};

struct Message {
    uint64_t id;
    uint64_t contact_id;
    std::string content;
    uint64_t timestamp;
    bool read;
};

struct AppPref {
    std::string app_name;
    std::string key;
    std::string value;
};

// Global state
std::vector<Contact> contacts;
std::vector<Message> messages;
std::vector<AppPref> app_prefs;
std::mutex mtx;

// Helper function to format timestamp
std::string format_timestamp(uint64_t timestamp) {
    time_t t = timestamp / 1000; // Convert to seconds
    struct tm* tm = localtime(&t);
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);
    return std::string(buffer);
}

int main() {
    crow::SimpleApp app;

    // Serve the frontend
    CROW_ROUTE(app, "/")([]{
        crow::response res;
        res.set_static_file_info("home_screen.html");
        return res;
    });

    // Get contacts
    CROW_ROUTE(app, "/api/contacts").methods("GET"_method)([](){
        std::lock_guard<std::mutex> lock(mtx);
        crow::json::wvalue res;
        for (size_t i = 0; i < contacts.size(); ++i) {
            res["contacts"][i]["id"] = contacts[i].id;
            res["contacts"][i]["name"] = contacts[i].name;
            res["contacts"][i]["phone"] = contacts[i].phone;
            res["contacts"][i]["email"] = contacts[i].email;
            res["contacts"][i]["favorite"] = contacts[i].favorite;
        }
        return res;
    });

    // Add contact
    CROW_ROUTE(app, "/api/contacts").methods("POST"_method)
    ([](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::lock_guard<std::mutex> lock(mtx);
        Contact contact;
        contact.id = contacts.size() + 1;
        contact.name = x["name"].s();
        contact.phone = x["phone"].s();
        contact.email = x["email"].s();
        contact.favorite = false;
        contacts.push_back(contact);

        return crow::response(200);
    });

    // Get messages for a contact
    CROW_ROUTE(app, "/api/contacts/<int>/messages").methods("GET"_method)
    ([](int contact_id){
        std::lock_guard<std::mutex> lock(mtx);
        crow::json::wvalue res;
        size_t msg_count = 0;
        for (const auto& msg : messages) {
            if (msg.contact_id == contact_id) {
                res["messages"][msg_count]["id"] = msg.id;
                res["messages"][msg_count]["content"] = msg.content;
                res["messages"][msg_count]["timestamp"] = format_timestamp(msg.timestamp);
                res["messages"][msg_count]["read"] = msg.read;
                msg_count++;
            }
        }
        return res;
    });

    // Add message
    CROW_ROUTE(app, "/api/contacts/<int>/messages").methods("POST"_method)
    ([](int contact_id, const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::lock_guard<std::mutex> lock(mtx);
        Message message;
        message.id = messages.size() + 1;
        message.contact_id = contact_id;
        message.content = x["content"].s();
        message.timestamp = std::time(nullptr) * 1000; // Current time in milliseconds
        message.read = false;
        messages.push_back(message);

        return crow::response(200);
    });

    // Get app preferences
    CROW_ROUTE(app, "/api/prefs/<string>").methods("GET"_method)
    ([](std::string app_name){
        std::lock_guard<std::mutex> lock(mtx);
        crow::json::wvalue res;
        size_t pref_count = 0;
        for (const auto& pref : app_prefs) {
            if (pref.app_name == app_name) {
                res["prefs"][pref_count]["key"] = pref.key;
                res["prefs"][pref_count]["value"] = pref.value;
                pref_count++;
            }
        }
        return res;
    });

    // Set app preference
    CROW_ROUTE(app, "/api/prefs/<string>").methods("POST"_method)
    ([](std::string app_name, const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::lock_guard<std::mutex> lock(mtx);
        std::string key = x["key"].s();
        std::string value = x["value"].s();

        // Update existing preference or add new one
        bool found = false;
        for (auto& pref : app_prefs) {
            if (pref.app_name == app_name && pref.key == key) {
                pref.value = value;
                found = true;
                break;
            }
        }

        if (!found) {
            AppPref pref;
            pref.app_name = app_name;
            pref.key = key;
            pref.value = value;
            app_prefs.push_back(pref);
        }

        return crow::response(200);
    });

    // Mark message as read
    CROW_ROUTE(app, "/api/messages/<int>/read").methods("POST"_method)
    ([](int message_id){
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& msg : messages) {
            if (msg.id == message_id) {
                msg.read = true;
                return crow::response(200);
            }
        }
        return crow::response(404);
    });

    // Toggle contact favorite status
    CROW_ROUTE(app, "/api/contacts/<int>/favorite").methods("POST"_method)
    ([](int contact_id){
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& contact : contacts) {
            if (contact.id == contact_id) {
                contact.favorite = !contact.favorite;
                return crow::response(200);
            }
        }
        return crow::response(404);
    });

    app.port(8080).multithreaded().run();
    return 0;
} 