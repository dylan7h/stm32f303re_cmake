#ifndef __SVC_DEBUG__H__
#define __SVC_DEBUG__H__

/* 
 * ANSI Color Code Refence URL
 * URL: https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
 */

/* # Reset */
#define MSG_Color_Off   "\033[0m"       

/* # Regular Colors */
#define MSG_Black       "\033[0;30m"
#define MSG_Red         "\033[0;31m"
#define MSG_Green       "\033[0;32m"
#define MSG_Yellow      "\033[0;33m"
#define MSG_Blue        "\033[0;34m"
#define MSG_Purple      "\033[0;35m"
#define MSG_Cyan        "\033[0;36m"
#define MSG_White       "\033[0;37m"

/* # Bold */
#define MSG_BBlack      "\033[1;30m"
#define MSG_BRed        "\033[1;31m"
#define MSG_BGreen      "\033[1;32m"
#define MSG_BYellow     "\033[1;33m"
#define MSG_BBlue       "\033[1;34m"
#define MSG_BPurple     "\033[1;35m"
#define MSG_BCyan       "\033[1;36m"
#define MSG_BWhite      "\033[1;37m"

/* # Underline */
#define MSG_UBlack      "\033[4;30m"
#define MSG_URed        "\033[4;31m"
#define MSG_UGreen      "\033[4;32m"
#define MSG_UYellow     "\033[4;33m"
#define MSG_UBlue       "\033[4;34m"
#define MSG_UPurple     "\033[4;35m"
#define MSG_UCyan       "\033[4;36m"
#define MSG_UWhite      "\033[4;37m"

/* # Background */
#define MSG_On_Black    "\033[40m"
#define MSG_On_Red      "\033[41m"
#define MSG_On_Green    "\033[42m"
#define MSG_On_Yellow   "\033[43m"
#define MSG_On_Blue     "\033[44m"
#define MSG_On_Purple   "\033[45m"
#define MSG_On_Cyan     "\033[46m"
#define MSG_On_White    "\033[47m"

/* # High Intensity */
#define MSG_IBlack      "\033[0;90m"
#define MSG_IRed        "\033[0;91m"
#define MSG_IGreen      "\033[0;92m"
#define MSG_IYellow     "\033[0;93m"
#define MSG_IBlue       "\033[0;94m"
#define MSG_IPurple     "\033[0;95m"
#define MSG_ICyan       "\033[0;96m"
#define MSG_IWhite      "\033[0;97m"

/* # Bold High Intensity */
#define MSG_BIBlack     "\033[1;90m"
#define MSG_BIRed       "\033[1;91m"
#define MSG_BIGreen     "\033[1;92m"
#define MSG_BIYellow    "\033[1;93m"
#define MSG_BIBlue      "\033[1;94m"
#define MSG_BIPurple    "\033[1;95m"
#define MSG_BICyan      "\033[1;96m"
#define MSG_BIWhite     "\033[1;97m"

/* # High Intensity backgrounds */
#define MSG_On_IBlack   "\033[0;100m"
#define MSG_On_IRed     "\033[0;101m"
#define MSG_On_IGreen   "\033[0;102m"
#define MSG_On_IYellow  "\033[0;103m"
#define MSG_On_IBlue    "\033[0;104m"
#define MSG_On_IPurple  "\033[0;105m"
#define MSG_On_ICyan    "\033[0;106m"
#define MSG_On_IWhite   "\033[0;107m"

#define MSGINFO         MSG_White
#define MSGERR          MSG_Red
#define MSGWARN         MSG_Yellow

#define DEBUGMSG(cond, format, ...)     Svc_Debug_Printf(cond, format, ##__VA_ARGS__)

void Svc_Debug_Initialize();
int Svc_Debug_Printf(const char* cond, const char* format, ...);

#endif  //!__SVC_DEBUG__H__