#include <crow/app.h>
#include <crow/json.h>
#include <vector>
#include <mutex>

struct Toggle {
    std::string name;
    bool state;
};
struct Slider {
    std::string name;
    int value;
};

std::vector<Toggle> toggles = {
    {"Wi-Fi", true},
    {"Bluetooth", false},
    {"Airplane", false}
};
std::vector<Slider> sliders = {
    {"Brightness", 50},
    {"Volume", 70}
};
std::mutex mtx;

int main() {
    crow::SimpleApp app;

    // Serve the frontend
    CROW_ROUTE(app, "/")([]{
        return crow::response::file("control_center.html");
    });

    // Get state
    CROW_ROUTE(app, "/api/state").methods("GET"_method)([](){
        std::lock_guard<std::mutex> lock(mtx);
        crow::json::wvalue res;
        for (size_t i = 0; i < toggles.size(); ++i) {
            res["toggles"][i]["name"] = toggles[i].name;
            res["toggles"][i]["state"] = toggles[i].state;
        }
        for (size_t i = 0; i < sliders.size(); ++i) {
            res["sliders"][i]["name"] = sliders[i].name;
            res["sliders"][i]["value"] = sliders[i].value;
        }
        return res;
    });

    // Toggle a toggle
    CROW_ROUTE(app, "/api/toggle/<int>").methods("POST"_method)
    ([](int idx){
        std::lock_guard<std::mutex> lock(mtx);
        if (idx >= 0 && idx < (int)toggles.size()) {
            toggles[idx].state = !toggles[idx].state;
            return crow::response(200);
        }
        return crow::response(400);
    });

    // Set a slider
    CROW_ROUTE(app, "/api/slider/<int>").methods("POST"_method)
    ([](const crow::request& req, int idx){
        std::lock_guard<std::mutex> lock(mtx);
        if (idx >= 0 && idx < (int)sliders.size()) {
            auto body = crow::json::load(req.body);
            if (!body) return crow::response(400);
            int val = body["value"].i();
            if (val < 0 || val > 100) return crow::response(400);
            sliders[idx].value = val;
            return crow::response(200);
        }
        return crow::response(400);
    });

    app.port(18080).multithreaded().run();
}