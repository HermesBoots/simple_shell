#ifndef _ERRORS_H_
#define _ERRORS_H_


#define ERROR_SAFE (0x000)
#define ERROR_NOT_FOUND (1 | ERROR_SAFE)
#define ERROR_RISKY (0x400)
#define ERROR_SYNTAX (2 | ERROR_RISKY)
#define ERROR_PERMANENT (0x800)
#define ERROR_MEMORY (3 | ERROR_PERMANENT)
#define ERROR_PROCESS (4 | ERROR_PERMANENT)


void errors(int code);


#endif /* _ERRORS_H_ */
