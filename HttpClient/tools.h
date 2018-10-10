/*
 * tools.h
 *
 * Copyright(C) Launch. All Rights Reserved.
 *
 * Created on: 2018-02-01
 *     Author: luo yongbo <yongbo.luo@cnlaunch.com>
 *
 *     Universal interface for common tools
 *
 */

 
#ifndef _TOOLS_H_
#define _TOOLS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> 
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <dirent.h>
#include <termios.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/vfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BCD2DEC(X) ((X) - ((X) >> 4) * 6) //BCDתʮ���ƣ�Xֻ��Ϊһ���ֽڵ�BCD��
#define DEC2BCD(X) ((((X)/10)<<4) + ((X)%10))

/* time struct */

typedef struct _SYSTEMTIME {
	unsigned short m_year;
	unsigned char  m_month;
	unsigned char  m_wday;    // day of week, 0~6, 0 is sunday
	unsigned char  m_day;
	unsigned char  m_hour;
	unsigned char  m_minute;
	unsigned char  m_second;
	unsigned char  m_milliseconds;
} SYSTEMTIME;

/*
 *  tools_delay_ms
 *
 *  Description:
 *  	sleep micro second
 *
 *  Parameters:
 *    ms: [in]
 *        micro second
 *
 *  Returns:
 *
 *  Comments:
 *
 */
void tools_delay_ms(int ms);

/*
 *  tools_delay_sec
 *
 *  Description:
 *  	sleep second
 *
 *  Parameters:
 *    sec: [in]
 *        second
 *
 *  Returns:
 *
 *  Comments:
 *
 */
void tools_delay_sec(int sec);

/*
 *  tools_value_to_systemtime
 *
 *  Description:
 *  	switch time_t value to struct SYSTEMTIME buffer
 *
 *  Parameters:
 *    p_time: [out]
 *        system time struct pointer
 *    val: [in]
 *        time_t value
 *
 *  Returns:
 *    0 : successfully.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_value_to_systemtime(SYSTEMTIME *p_time, time_t *val);


/*
 *  tools_systemtime_to_value
 *
 *  Description:
 *  	switch struct SYSTEMTIME buffer to time_t value
 *
 *  Parameters:
 *    p_time: [in]
 *        system time struct pointer
 *    val: [out]
 *        time_t value
 *
 *  Returns:
 *    >0: successfully.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_systemtime_to_value(SYSTEMTIME *p_time, time_t *val);

/*
 *  tools_get_system_time
 *
 *  Description:
 *  	get local system time
 *
 *  Parameters:
 *    p_time: [out]
 *        system time struct pointer
 *    val: [out]
 *        time_t value
 *
 *  Returns:
 *    0 : successfully.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_get_system_time(SYSTEMTIME *p_time, time_t *val);

/*
 *  tools_set_system_time
 *
 *  Description:
 *  	set local system time
 *
 *  Parameters:
 *    p_time: [in]
 *        system time struct pointer
 *
 *  Returns:
 *    0 : successfully.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_set_system_time(SYSTEMTIME *p_time);

/*
 *  tools_write_config
 *
 *  Description:
 *  	write key value to configure file 
 *
 *  Parameters:
 *    value: [in]
 *        value string
 *    key: [in]
 *        key string
 *    file_name: [in]
 *        configure file 
 *
 *  Returns:
 *		0 : successfully.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_write_config(char *value, char *key, char *file_name);

/*
 *  tools_read_config
 *
 *  Description:
 *  	read key value from configure file 
 *
 *  Parameters:
 *    value: [out]
 *        value string
 *    key: [in]
 *        key string
 *    file_name: [int]
 *        configure file 
 *
 *  Returns:
 *		>=0: successfully, the size of value string
 *    -1 : failed.
 *
 *  Comments:
 *
 */
int tools_read_config(char *value, const char *key, const char *file_name);

/*
 *  tools_read_bin_config
 *
 *  tools_read_bin_config:
 *  	read key value from bin configure file 
 *
 *  Parameters:
 *    value: [out]
 *        value string
 *    key: [in]
 *        key string
 *    key_len: [in]
 *        the size of key
 *    file_name: [in]
 *        configure file 
 *
 *  Returns:
 *		>=0: successfully, the size of value string
 *    -1 : failed.
 *
 *  Comments:
 *
 */
int tools_read_bin_config(unsigned char *value, void *key, int key_len, char *file_name);

/*
 *  tools_write_bin_config
 *
 *  Description:
 *  	write bin key and value to configure file 
 *
 *  Parameters:
 *    value: [in]
 *        value string
 *    val_len: [in]
 *        value length
 *    key: [in]
 *        key string
 *    key_len:[in]
 *        key string length
 *    file_name: [in]
 *        configure file 
 *
 *  Returns:
 *	  =0: successfully
 *    -1 : failed.
 *
 *  Comments:
 *
 */
int tools_write_bin_config(unsigned char *value, int val_len, void *key, int key_len, char *file_name);

/*
 *  tools_write_bin_conf_with_check
 *
 *  Description:
 *  	����д���������жϣ�������ֵδ�ı䣬��д�ļ�
 *
 *  Parameters:
 *    value: [out]
 *        value string
 *    key: [in]
 *        key string
 *    key_len:[in]
 *        key string length
 *    file_name: [int]
 *        configure file 
 *
 *  Returns:
 *	  =0: successfully
 *    -1 : failed.
 *
 *  Comments:
 *
 */
int tools_write_bin_config_with_check(unsigned char *value, int val_len, void *key, int key_len, char *file_name);

/*
 *  tools_sprintf_hex
 *
 *  Description:
 *  	sprintf hexadecimal number to buffer
 *
 *  Parameters:
 *    output: [out]
 *        the sprintf result buffer
 *    hex_data: [in]
 *        key string
 *    hex_size: [in]
 *        the size of hex_data
 *
 *  Returns:
 *		>0: successfully. the size of output
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_sprintf_hex(char *output, char *hex_data, int hex_size);

/*
 *  tools_config_mutex_init
 *
 *  Description:
 *  	initialize config write mutex
 *
 *  Parameters:
 *	
 *  Returns:
 *
 *  Comments:
 *
 */
void tools_init_config(void);

/*
 *  tools_string_to_bcd
 *
 *  Description:
 *  	���ַ���תBCD��
 *
 *  Parameters:
 *    output: [out]
 *        ת�����BCD��
 *    output_size: [in]
 *        ��Ҫת����BCD�볤�ȣ�Ĭ��Ϊ��ת�����ַ������ȵ�һ��
 *    input: [in]
 *        ��ת�����ַ���
 *    input_size:[in]
 *		  ��ת�����ַ������ȣ�input_size = output_size * 2	
 *  Returns:
 *	  0: successfully.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int tools_string_to_bcd(unsigned char *output, int output_size, unsigned char *input, int input_size);

/*
 *  tools_big_endian_to_ushort
 *
 *  Description:
 *  	������ֽ���ת��Ϊ������
 *
 *  Parameters:
 *    data: [in]
 *        ��ת�����ֽ���
 *  Returns:
 *        ת�����ֵ
 *
 *  Comments:
 *
 */
unsigned short tools_big_endian_to_ushort(unsigned char *data);

/*
 *  tools_big_endian_to_uint
 *
 *  Description:
 *  	������ֽ���ת��Ϊ����
 *
 *  Parameters:
 *    data: [in]
 *        ��ת�����ֽ���
 *  Returns:
 *        ת�����ֵ
 *
 *  Comments:
 *
 */
unsigned int tools_big_endian_to_uint(unsigned char *data);

/*
 *  tools_ushort_to_big_endian
 *
 *  Description:
 *  	��������ת��Ϊ����ֽ���
 *
 *  Parameters:
 *    data: [out]
 *        ת������ֽ���
 *    value:[in]  
 *        ����Ķ�����
 *  Returns:
 *        
 *  Comments:
 *
 */
void tools_ushort_to_big_endian(unsigned char *data, unsigned short value);

/*
 *  tools_uint_to_big_endian
 *
 *  Description:
 *  	������ת��Ϊ����ֽ���
 *
 *  Parameters:
 *    data: [out]
 *        ת������ֽ���
 *    value:[in]  
 *        ���������
 *  Returns:
 *        
 *  Comments:
 *
 */
void tools_uint_to_big_endian(unsigned char *data, unsigned int value);

/*
 *  tools_little_endian_to_ushort
 *
 *  Description:
 *  	��С���ֽ���ת��Ϊ������
 *
 *  Parameters:
 *    data: [in]
 *        ��ת�����ֽ���
 *  Returns:
 *        ת�����ֵ
 *
 *  Comments:
 *
 */
unsigned short tools_little_endian_to_ushort(unsigned char *data);

/*
 *  tools_little_endian_to_uint
 *
 *  Description:
 *  	��С���ֽ���ת��Ϊ����
 *
 *  Parameters:
 *    data: [in]
 *        ��ת�����ֽ���
 *  Returns:
 *        ת�����ֵ
 *
 *  Comments:
 *
 */
unsigned int tools_little_endian_to_uint(unsigned char *data);

/*
 *  tools_ushort_to_little_endian
 *
 *  Description:
 *  	��������ת��ΪС���ֽ���
 *
 *  Parameters:
 *    data: [out]
 *        ת������ֽ���
 *    value:[in]  
 *        ����Ķ�����
 *  Returns:
 *        
 *  Comments:
 *
 */
void tools_ushort_to_little_endian(unsigned char *data, unsigned short value);

/*
 *  tools_uint_to_little_endian
 *
 *  Description:
 *  	������ת��ΪС���ֽ���
 *
 *  Parameters:
 *    data: [out]
 *        ת������ֽ���
 *    value:[in]  
 *        ���������
 *  Returns:
 *        
 *  Comments:
 *
 */
void tools_uint_to_little_endian(unsigned char *data, unsigned int value);


typedef void* (*thread_handler_t)(void *param);
int create_thread(thread_handler_t comm_handler, void *param);

#endif    /*_TOOLS_H_*/