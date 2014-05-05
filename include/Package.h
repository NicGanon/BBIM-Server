#pragma once

#pragma pack(1)
typedef struct _tagDeal
{
   int bodyLength;
   int function;
   char compress;
   int edition;
   char seq[64];
   int error;
   char desError[100];
} DEAL, *LPDEAL;

const int PACKAGE_LOGIN = 0x00000001;
const int PACKAGE_LOGIN_RESP = 0x10000001;

const int PACKAGE_TEL = 0x00000044;
const int PACKAGE_TEL_RESP = 0x10000044;
const int PACKAGE_TEL_ERROR = 4010;

const int PACKAGE_USER_ERROR = 8010;
const int PACKAGE_PASSWORD_ERROR = 8011;
const int  PACKAGE_ERROR  = 9000;

const int PACKAGE_HEART = 0x00000003;
const int PACKAGE_HEART_RESP = 0x10000003;

