#include "WebCppApp.h"
#include "cef/include/cef_app.h"
#include "cef/include/cef_client.h"
#include "cef/include/cef_browser.h"
#include "cef/include/cef_command_line.h"
#include "cef/include/wrapper/cef_message_router.h"
#include "cef/include/wrapper/cef_helpers.h"
#include <iostream>

// Forward declaration of helper classes
class WebClient;

class WebCppApp::Impl {
public:
    CefRefPtr<WebClient> client;
    CefRefPtr<CefBrowser> browser;
    CefRefPtr<CefMessageRouterBrowserSide> messageRouter;

    std::string entryFile;
    int width = 800;
    int height = 600;
    bool fullscreen = false;
};

// Custom client to handle browser events and JS bindings
class WebClient : public CefClient,
                  public CefLifeSpanHandler,
                  public CefDisplayHandler {
public:
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    CefRefPtr<CefDisplayHandler> GetDisplayHandler() override {
        return this;
    }

    void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override {
        std::cout << "[WebCpp] Window title changed: " << title.ToString() << std::endl;
    }

    IMPLEMENT_REFCOUNTING(WebClient);
};

WebCppApp::WebCppApp() : impl(std::make_unique<Impl>()) {}

WebCppApp::~WebCppApp() {
    CefShutdown();
}

bool WebCppApp::run(const std::string& entryFile) {
    impl->entryFile = entryFile;

    // CEF settings
    CefMainArgs args;
    CefSettings settings;
    settings.no_sandbox = true;

    CefRefPtr<CefApp> app;
    CefInitialize(args, settings, app, nullptr);

    // Setup browser window info
    CefWindowInfo window_info;
    window_info.SetAsPopup(nullptr, "WebCpp UI");

    CefBrowserSettings browser_settings;
    CefRefPtr<WebClient> client = new WebClient();
    impl->client = client;

    std::string url = "file://" + entryFile;
    CefBrowserHost::CreateBrowser(window_info, client, url, browser_settings, nullptr, nullptr);

    CefRunMessageLoop();
    return true;
}

void WebCppApp::sendToJS(const std::string& event, const std::string& payload) {
    if (impl->browser) {
        std::string js = "window.dispatchEvent(new CustomEvent('" + event + "', { detail: " + payload + " }));";
        impl->browser->GetMainFrame()->ExecuteJavaScript(js, impl->entryFile, 0);
    }
}

void WebCppApp::onMessageFromJS(const std::string& event, const std::function<void(const std::string&)>& callback) {
    // TODO: Hook this into messageRouter to listen for events from JS
}

void WebCppApp::setWindowSize(int width, int height) {
    impl->width = width;
    impl->height = height;
}

void WebCppApp::setFullscreen(bool enabled) {
    impl->fullscreen = enabled;
}
