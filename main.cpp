#include <iostream>
#include <cstdlib>
#include <string>

void printUsage() {
    std::cerr << "Usage: ./converter -m <input_video> <output_audio> [-v]\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage();
        return 1;
    }

    bool verbose = false;
    std::string inputFile, outputFile;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-m" && i + 2 < argc) {
            inputFile = argv[i + 1];
            outputFile = argv[i + 2];
            i += 2;
        } else if (std::string(argv[i]) == "-v") {
            verbose = true;
        }
    }

    if (inputFile.empty() || outputFile.empty()) {
        printUsage();
        return 1;
    }

    std::string command = "ffmpeg -i " + inputFile + " -vn -acodec libmp3lame -q:a 2 " + outputFile;
    if (verbose) {
        command += " 2>&1";
    }

    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error: Conversion failed.\n";
        return 1;
    }

    std::cout << "Conversion successful: " << outputFile << "\n";
    return 0;
}
