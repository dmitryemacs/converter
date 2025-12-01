#include <iostream>
#include <cstdlib>
#include <string>

void printUsage() {
    std::cerr << "Usage: ./converter -v -m <input_video> <output_audio>\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4 || std::string(argv[1]) != "-m") {
        printUsage();
        return 1;
    }

    std::string inputFile = argv[2];
    std::string outputFile = argv[3];

    bool verbose = false;
    if (argc == 5 && std::string(argv[4]) == "-v") {
	verbose = true;
    }
    std::string command = "ffmpeg -i " + inputFile + " -vn -acodec libmp3lame -q:a 2 " + outputFile;
    if (verbose) {
	command += " 2>&1"; // Перенаправить stderr в stdout для отображения прогресса
    }

    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Error: Conversion failed.\n";
        return 1;
    }

    std::cout << "Conversion successful: " << outputFile << "\n";
    return 0;
}
