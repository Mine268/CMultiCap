#include "CMultiCap.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "stb_image_write.h"


int N_CAP = 2;

int main() {
	get_app();
	init_device();
    std::cout << get_device_count() << std::endl;
    assert(N_CAP == get_device_count());

    for (int i = 0; i < N_CAP; ++i) {
        set_exposure(i, 10000.f);
        set_gain(i, 15.f);
    }

    start_grabbing();

    // D:\Work\CMultiCap\tmp
	for (int fx = 0;; ++fx) {
		auto cap_info = capture();
		assert(cap_info.n_cap == N_CAP);
		
        for (int i = 0; i < N_CAP; ++i) {
            if (!cap_info.flag[i]) {
                continue;
            }
            cv::Mat img_rgb(cap_info.height[i], cap_info.width[i], CV_8UC3, cap_info.ppbuffer[i]), img_bgr;
            cv::cvtColor(img_rgb, img_bgr, cv::COLOR_RGB2BGR);
            cv::imshow(std::format("{}", i), img_bgr);

            std::string path = std::format(R"(D:\Work\CMultiCap\tmp\V{}\{:06}.bmp)", i, fx);
            stbi_write_bmp(path.c_str(), cap_info.width[0], cap_info.height[0], 3, cap_info.ppbuffer[i]);
        }
        if (cv::waitKey(1) == 'q') {
            break;
        }
	}

    stop_grabbing();

	close_device();
	release_app();
	return 0;
}