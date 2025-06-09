#include <crow/app.h>
#include <crow/json.h>
#include <string>
#include <mutex>

std::string current_pin = "";
std::mutex pin_mutex;

int main() {
    crow::SimpleApp app;

    // Serve the lock screen frontend
    CROW_ROUTE(app, "/")([]{
        crow::response res;
        res.set_static_file_info("lock_screen.html");
        return res;
    });

    // API: Submit PIN (for unlock)
    CROW_ROUTE(app, "/api/pin").methods("POST"_method)
    ([](const crow::request& req){
        std::lock_guard<std::mutex> lock(pin_mutex);
        auto body = crow::json::load(req.body);
        if (!body || body["pin"].t() != crow::json::type::String) {
    return crow::response(400, "Invalid request");
}
        current_pin = body["pin"].s();
        // TODO: Validate PIN, trigger unlock, etc.
        return crow::response(200, "PIN received");
    });

    // (Optional) API: Get notifications (future extension)
    CROW_ROUTE(app, "/api/notifications").methods("GET"_method)
    ([](){
        crow::json::wvalue res;
        // TODO: Populate with real notifications
        res["notifications"] = crow::json::wvalue::list{};
        return res;
    });

    app.port(18081).multithreaded().run();
    return 0;
} 