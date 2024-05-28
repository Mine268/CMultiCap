#ifndef HEAD_CMULTICAP
#define HEAD_CMULTICAP

constexpr unsigned int INFO_MAX_BUFFER_SIZE = 64;
constexpr unsigned int MAX_CAPTURE = 16;


extern "C" {

    struct CaptureInfo {
        unsigned int n_cap;  // ��׽������
        bool flag[MAX_CAPTURE];  // ÿһ����׽�Ƿ�ɹ�
        unsigned int width[MAX_CAPTURE];  // ÿһ����׽�Ŀ��
        unsigned int height[MAX_CAPTURE];  // ÿһ��ͼ��ĸ߶�
        unsigned char* ppbuffer[MAX_CAPTURE];  // ÿһ����׽�Ļ�������ָ��
        unsigned char serial_numbers[MAX_CAPTURE][INFO_MAX_BUFFER_SIZE]; // ÿһ����׽��ͼ���Ӧ��������к�
    };

    // ��õ���
    __declspec(dllexport) void get_app();

    // ��ϵϵͳ
    __declspec(dllexport) void release_app();

    // ��ȡ�豸
    __declspec(dllexport) auto init_device() -> int;

    // �ر��豸
    __declspec(dllexport) auto close_device() -> int;

    // ��ʼץȡ
    __declspec(dllexport) auto start_grabbing() -> int;

    // ֹͣץȡ
    __declspec(dllexport) auto stop_grabbing() -> int;

    // ץȡһ֡
    __declspec(dllexport) auto capture() -> CaptureInfo;

    // ��ȡ�豸����
    __declspec(dllexport) auto get_device_count() -> int;

    // �����豸�ع�
    __declspec(dllexport) auto set_exposure(unsigned cam_ix, float exposure) -> int;

    // �����豸����
    __declspec(dllexport) auto set_gain(unsigned cam_ix, float gain) -> int;

}


#endif // !HEAD_CMULTICAP