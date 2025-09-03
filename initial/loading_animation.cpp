#include <iostream> // Required for input/output operations (like std::cout)
#include <string>   // Required for using std::string
#include <chrono>   // Required for time-related functions (like std::chrono::milliseconds)
#include <thread>   // Required for pausing execution (like std::this_thread::sleep_for)

// Main function where the program execution begins
int main() {
    // Disable synchronization with C stdio and untie cin/cout for faster output.
    // This can be beneficial for console animations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Define the animation frames
    std::string frames[] = {
        "Loading |",
        "Loading /",
        "Loading -",
        "Loading \\"
    };
    int numFrames = sizeof(frames) / sizeof(frames[0]); // Calculate number of frames

    // Set the duration for each frame in milliseconds
    int frameDelayMs = 200;

    // Loop for a certain number of iterations to show the animation
    int animationCycles = 10;
    for (int i = 0; i < animationCycles; ++i) {
        // Iterate through each frame of the animation
        for (int j = 0; j < numFrames; ++j) {
            // Print the current frame.
            // '\r' (carriage return) moves the cursor to the beginning of the line
            // without advancing to the next line, allowing overwrite.
            std::cout << frames[j] << std::flush; // std::flush ensures immediate output

            // Pause execution for the specified frame delay
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelayMs));
        }
    }

    // After the animation, print a newline to move the cursor to the next line
    // so subsequent output doesn't overwrite the last animation frame.
    std::cout << "\nDone!\n";

    // Return 0 to indicate successful execution
    return 0;
}
