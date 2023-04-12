#define VK_USE_PLATFORM_XLIB_KHR // X11
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include <X11/Xlib.h>



// defining a windows dimensions
//

const int WIDTH = 800;
const int HEIGHT = 600;

Display* display;
Window window;


// the vulkan instance handle
VkInstance instance;

// vulkan device handle
VkDevice device;

// swap chain images
VkImage swapChainImages[3];

// swap chain image views
VkImageView swapChainImageViews[3];

// swap chain format
VkFormat swapChainImageFormat;

// swap chain extent
VkExtent2D swapChainExtent;

// function to create a vulkan instance

void createInstance() {
    // The Application info
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulken Renderer vrender";
    appInfo.applicationVersion = VK_MAKE_VERSION(0,0,1);
    appInfo.pEngineName = "No Engine here";
    appInfo.engineVersion = VK_MAKE_VERSION(0,0,1);
    appInfo.apiVersion = VK_API_VERSION_1_0;


    // instance create info
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Create Vulkan instance
    VkResult result = vkCreateInstance(&createInfo, NULL, &instance);
    if (result != VK_SUCCESS) {
        printf("Failed to create vk instance\n");
        exit(1);
    }
}

void createWindow() {
    // open X display
    display = XOpenDisplay(NULL);

    if (!display) {
        fprintf(stderr, "Failed to open X display.\n");
        exit(EXIT_FAILURE);
    }

    // Create Window
    Window root = DefaultRootWindow(display);
    XSetWindowAttributes windowAttributes;
    unsigned long mask = CWEventMask;
    windowAttributes.event_mask = ExposureMask | KeyPressMask;
    window = XCreateWindow(display, root, 0, 0, WIDTH, HEIGHT, 0,
            CopyFromParent, InputOutput, CopyFromParent, mask, &windowAttributes);
    XMapWindow(display, window);
    XFlush(display);
}

void handleWindowEvents() {
    // Handle window events
    XEvent event;
    while (XCheckWindowEvent(display, window, ExposureMask | KeyPressMask,
                &event)) {
        switch (event.type) {
            case Expose:
                // TODO: handle expose event, redraw the window
                break;
            case KeyPress:
                // TODO: handle key press event
                break;
            default:
                break;
        }
    }
}

void initVulkan() {
    createInstance();
    createWindow();
    // createDevice(); // pending
    // createSwapChainImages(); // pending

    // TODO: create the vulkan resources (buffers, textures, etc..)
}

// function to render a frame

void renderFrame() {
    // TODO: implement rendering logic
}

void cleanupVulkan() {
    // TODO: Cleanup vulkan resources

    // Destroy swap chain image views
    for (int i = 0; i < 3; i++) {
        vkDestroyImageView(device, swapChainImageViews[i], NULL);
    }

    // Destroy swap chain

    // Destroy vulkan device
    vkDestroyDevice(device, NULL);

    // Destroy vulkan instance
    vkDestroyInstance(instance, NULL);
}

// handling window resizing
void handleWindowResize() {
    // TODO: handle window resizing
    

    // cleanup and reinitialize vulkan resources
    cleanupVulkan();
    initVulkan();
}

int main() {
    initVulkan();

    createWindow();
    // the main loop
    while (1) {

        // TODO: Handle window events
        handleWindowEvents();

        renderFrame();
        
        // TODO swap buffers

        // Break loop on window close event

        if (!XPending(display)) {
            break;
        }

    }

    // cleanup xlib resources
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    // cleanup vulkan resources
    cleanupVulkan();
    return 0;
}
