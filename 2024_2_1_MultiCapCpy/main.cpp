#include "CMultiCap.h"

#include <string>
#include <format>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include "stb_image_write.h"


auto main() -> int {

	get_app();
	init_device();

    set_exposure(0, 8000.f);
    set_gain(0, 10.f);

	start_grabbing();

    for (;;) {
        auto cap_info = capture();
        auto n_cap = cap_info.n_cap;
        for (int i = 0; i < n_cap; ++i) {
            if (!cap_info.flag[i]) {
                continue;
            }
            cv::Mat img_rgb(cap_info.height[i], cap_info.width[i], CV_8UC3, cap_info.ppbuffer[i]), img_bgr;
            cv::cvtColor(img_rgb, img_bgr, cv::COLOR_RGB2BGR);
            cv::imshow(std::format("{}", i), img_bgr);
        }
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    //for (unsigned int i = 0; i < 1024; ++i) {
    //    auto cap_info = capture();
    //    std::string path1 = std::format("mvs_image{}_{}.bmp", std::string(reinterpret_cast<const char*>(cap_info.serial_numbers[0])), i);
    //    if (cap_info.flag[0]) {
    //        auto ret =
    //            stbi_write_bmp(path1.c_str(),
    //                cap_info.width[0], 
    //                cap_info.height[0],
    //                3,
    //                cap_info.ppbuffer[0]);
    //    }
    //}

	stop_grabbing();
	close_device();
	release_app();

	return 0;
}