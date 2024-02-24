#include "CMultiCap.h"

#include <string>
#include <format>

#include "stb_image_write.h"


auto main() -> int {

	get_app();
	init_device();
	start_grabbing();

    for (unsigned int i = 0; i < 10; ++i) {
        auto cap_info = capture();
        std::string path1 = std::format("mvs_image{}_{}.bmp", std::string(reinterpret_cast<const char*>(cap_info.serial_numbers[0])), i);
        if (cap_info.flag[0]) {
            auto ret =
                stbi_write_bmp(path1.c_str(),
                    cap_info.width[0],
                    cap_info.height[0],
                    3,
                    cap_info.ppbuffer[0]);
        }
    }

	stop_grabbing();
	close_device();
	release_app();

	return 0;
}

//auto main() -> int {
//
//    auto* p_app = get_singleton();
//    p_app->init_device();
//    p_app->start_grabbing();
//    
//    for (unsigned int i = 0; i < 10; ++i) {
//        p_app->capture();
//        std::string path1 = std::format("mvs_image1_{}.bmp", i);
//        std::string path2 = std::format("mvs_image2_{}.bmp", i);
//        auto ret =
//            stbi_write_bmp(path1.c_str(),
//                p_app->frame_buffer_list[0].width,
//                p_app->frame_buffer_list[0].height,
//                3,
//                p_app->frame_buffer_list[0].p_buffer);
//        ret =
//            stbi_write_bmp(path2.c_str(),
//                p_app->frame_buffer_list[1].width,
//                p_app->frame_buffer_list[1].height,
//                3,
//                p_app->frame_buffer_list[1].p_buffer);
//    }
//
//
//    p_app->stop_grabbing();
//    p_app->close_device();
//    release_singleton();
//
//    return 0;
//}
