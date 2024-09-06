#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void applyBlur(Mat& image, int kernelSize) {
    GaussianBlur(image, image, Size(kernelSize, kernelSize), 0);
}

void applySharpen(Mat& image) {
    Mat kernel = (Mat_<float>(3,3) <<
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1);
    filter2D(image, image, image.depth(), kernel);
}

void adjustBrightness(Mat& image, double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

void adjustSaturation(Mat& image, double factor) {
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    vector<Mat> channels;
    split(hsv, channels);
    channels[1] *= factor;
    merge(channels, hsv);
    cvtColor(hsv, image, COLOR_HSV2BGR);
}

int main() {
    string imagePath;
    cout << "Enter the path to your image: ";
    cin >> imagePath;

    Mat image = imread(imagePath);
    if (image.empty()) {
        cout << "Error: Could not read the image." << endl;
        return -1;
    }

    int choice;
    do {
        cout << "\nImage Processing Menu:" << endl;
        cout << "1. Apply Blur" << endl;
        cout << "2. Apply Sharpen" << endl;
        cout << "3. Adjust Brightness" << endl;
        cout << "4. Adjust Saturation" << endl;
        cout << "5. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int kernelSize;
                cout << "Enter kernel size (odd number, e.g., 3, 5, 7): ";
                cin >> kernelSize;
                applyBlur(image, kernelSize);
                break;
            }
            case 2: {
                applySharpen(image);
                break;
            }
            case 3: {
                double alpha;
                int beta;
                cout << "Enter alpha (contrast, e.g., 1.5): ";
                cin >> alpha;
                cout << "Enter beta (brightness, e.g., 50): ";
                cin >> beta;
                adjustBrightness(image, alpha, beta);
                break;
            }
            case 4: {
                double factor;
                cout << "Enter saturation factor (e.g., 1.5): ";
                cin >> factor;
                adjustSaturation(image, factor);
                break;
            }
            case 5: {
                string outputPath;
                cout << "Enter the output image path: ";
                cin >> outputPath;
                imwrite(outputPath, image);
                cout << "Image saved successfully." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 5) {
            imshow("Processed Image", image);
            waitKey(0);
        }
    } while (choice != 5);

    return 0;
}