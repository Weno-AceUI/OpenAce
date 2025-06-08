#ifndef WEBCPP_APP_H
#define WEBCPP_APP_H

#include <string>
#include <memory>

class WebCppApp {
public:
    // Constructor & Destructor
    WebCppApp();
    ~WebCppApp();

    // Run the app, loading a local or embedded HTML file
    bool run(const std::string& entryFile);

    // Inject data into JS runtime
    void sendToJS(const std::string& event, const std::string& payload);

    // Handle messages from JS
    void onMessageFromJS(const std::string& event, const std::function<void(const std::string&)>& callback);

    // Optional: Set window size or fullscreen
    void setWindowSize(int width, int height);
    void setFullscreen(bool enabled);

private:
    // Internal implementation class to hide browser engine details
    class Impl;
    std::unique_ptr<Impl> impl;
};

#endif // WEBCPP_APP_H
