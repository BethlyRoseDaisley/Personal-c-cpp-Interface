#ifndef _LOG_H_
#define _LOG_H_


/* ��־������ */
#define LOG_FATAL           0     // ���ش���
#define LOG_ERROR           1     // һ�����
#define LOG_WARN            2     // ����
#define LOG_INFO            3     // һ����Ϣ
#define LOG_TRACE           4     // ������Ϣ
#define LOG_DEBUG           5     // ������Ϣ
#define LOG_ALL             6     // ������Ϣ

/* �Ƿ��ӡ��Ļ */
#define LOG_SCREENSHOT_NOT  0     // ����ӡ��Ļ
#define LOG_SCREENSHOT_YES  1     // ��ӡ����Ļ

#define LOG_MAX_FILE_NAME_LENGTH   (256)             // ��־�ļ�����󳤶�
#define LOG_MAX_FILE_SIZE          (2*1024*1024)     // ��־�ļ���󳤶�
#define LOG_MAX_FILE_COUNT         (5)               // �����־�ļ����ݸ���


#define LOG_INIT(level, flag, log_file)          log_init(level, flag, log_file)
#define LOG_EXIT()                               log_exit();
#define LOG_WRITE(level, msg, ...)               log_write(__FILE__, __FUNCTION__, __LINE__, level, msg, ##__VA_ARGS__) 
#define LOG_SPRINTF_HEX(output, hex_data, size)  log_sprintf_hex(output, hex_data, size);

/*
 *  log_init
 *
 *  Description:
 *  	initilize logger
 *
 *  Parameters:
 *    log_level: [in]
 *        the logger 
 *    screenshot_flag: [in]
 *        Screenshot flag, 1: print to screen, 0: don't print to screen
 *    log_filename: [in]
 *        the logger file name
 *
 *  Returns:
 *     0: successful.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int log_init(int log_level, int screenshot_flag, char *log_filename);

/*
 *  log_exit
 *
 *  Description:
 *  	exit logger
 *
 *  Parameters:
 *
 *  Returns:
 *     0: successful.
 *    -1: failed.
 *
 *  Comments:
 *
 */
int log_exit(void);

/*
 *  log_write
 *
 *  Description:
 *  	initilize logger
 *
 *  Parameters:
 *    file_name: [in]
 *        source code file name
 *    func_name: [in]
 *        source code function name
 *    code_line: [in]
 *        source code line
 *    log_level: [in]
 *        the logger level
 *    buf: [in]
 *        the write buffer data
 *
 *  Returns:
 *    >0: successful. the size of write buffer data 
 *     0: successful. the log level is lower, no need to write
 *    -1: failed.
 *
 *  Comments:
 *
 */
int log_write(const char *file_name, const char *func_name, int code_line, int log_level, char *buf, ...);

/*
 *  log_sprintf_hex
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
int log_sprintf_hex(unsigned char *output, unsigned char *hex_data, int hex_size);

#endif    /* _LOG_H_ */
