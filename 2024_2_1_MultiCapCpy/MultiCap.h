#ifndef INC_2024_01_28_MULTICAPCPY_MULTICAP_H
#define INC_2024_01_28_MULTICAPCPY_MULTICAP_H

#include "MvCamera.h"
#include <Windows.h>
#include <process.h>
#include <vector>
#include <atomic>


struct SyncCtrl;
struct MultiCap;
struct BufferInfo;


struct SyncCtrl {
    MultiCap* obj_ptr;
    unsigned int cam_ix;
};


struct BufferInfo
{
    unsigned int width; // ͼ����
    unsigned int height; // ͼ��߶�
    unsigned int frame_ix; // ֡���
    unsigned char* p_buffer; // ������ָ��
};


struct MultiCap {
    MV_CC_DEVICE_INFO_LIST device_info_list{ 0 };  // �豸��Ϣ�б�
    std::vector<CMvCamera*> device_obj_list;  // �豸�����б�
    std::vector<BufferInfo> frame_buffer_list;  // ͼ��֡�б�
    std::vector<bool> frame_flag;  // ��ʾͼ���Ƿ�ץȡ�ɹ�
    std::vector<void*> thread_list;  // �߳̾���б�

    HANDLE h_sem_agg{}, h_sem_continue{};  // ���ڿ������̺߳� main ͬ�����ź���
    std::atomic_bool b_grab{ false };

    MultiCap() = default;
    ~MultiCap() = default;

    /**
     * ö�� + ���豸�����ش򿪵��豸������
     */
    int init_device();

    /**
     * ��ʼץȡͼ���������سɹ���ʼץȡ���豸����
     */
    int start_grabbing();

    /**
     * ���߳�ץȡ�� cam_ix �豸ͼ��
     */
    void _work_thread(unsigned int cam_ix);

    /**
     * ����һ��ͬ����׽
     */
    void capture();

    /**
     * �ر�ץȡ�����سɹ��رյ�ץȡ������
     */
    int stop_grabbing();

    /**
     * �ر��豸�����سɹ��رյ��豸����
     */
    int close_device();

    /*
     * ����������
     */
    int get_device_count() const;

    /*
     * ����ĳһ��������ع�ʱ��
     */
    int set_exposure(unsigned int cam_ix, float exposure);

    /*
     * ����ĳһ�����������
     */
    int set_gain(unsigned int cam_ix, float gain);
};


/*
 * ���õ��������� ctypes ��װ
 * */
extern MultiCap* multicap_obj;


MultiCap* get_singleton();


void release_singleton();


unsigned int __stdcall work_thread(void* p_user);


#endif //INC_2024_01_28_MULTICAPCPY_MULTICAP_H
