#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

char *makeJson()
{
    cJSON * pJsonRoot = cJSON_CreateObject();
    if(NULL == pJsonRoot)
    {
        // create object faild, exit
        return NULL;
    }
    cJSON_AddStringToObject(pJsonRoot, "name", "JSON中国");
    cJSON_AddStringToObject(pJsonRoot, "url", "http://www.json.org.cn");
    cJSON_AddNumberToObject(pJsonRoot, "page", 88);
    cJSON_AddBoolToObject(pJsonRoot, "isNonProfit", 1);

    cJSON * pJsonSub = cJSON_CreateObject();
    if(NULL == pJsonSub)
    {
        // create object faild, exit
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddItemToObject(pJsonRoot, "address", pJsonSub);
    cJSON_AddStringToObject(pJsonSub, "street", "浙大路38号.");
    cJSON_AddStringToObject(pJsonSub, "city", "浙江杭州");
    cJSON_AddStringToObject(pJsonSub, "country", "中国");

    pJsonSub =  cJSON_CreateArray();
    if(NULL == pJsonSub)
    {
        // create object faild, exit
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddItemToObject(pJsonRoot, "links", pJsonSub);

    cJSON * pJsonSubSub;
    pJsonSubSub = cJSON_CreateObject();
    if(NULL == pJsonSubSub)
    {
        // create object faild, exit
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddItemToArray(pJsonSub, pJsonSubSub);
    cJSON_AddStringToObject(pJsonSubSub, "name", "Google");
    cJSON_AddStringToObject(pJsonSubSub, "url", "http://www.google.com");
    pJsonSubSub = cJSON_CreateObject();
    if(NULL == pJsonSubSub)
    {
        // create object faild, exit
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddItemToArray(pJsonSub, pJsonSubSub);
    cJSON_AddStringToObject(pJsonSubSub, "name", "Baidu");
    cJSON_AddStringToObject(pJsonSubSub, "url", "http://www.baidu.com");
    pJsonSubSub = cJSON_CreateObject();
    if(NULL == pJsonSubSub)
    {
        // create object faild, exit
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    cJSON_AddItemToArray(pJsonSub, pJsonSubSub);
    cJSON_AddStringToObject(pJsonSubSub, "name", "SoSo");
    cJSON_AddStringToObject(pJsonSubSub, "url", "http://www.SoSo.com");

    //char * p = cJSON_Print(pJsonRoot);
    char * p = cJSON_PrintUnformatted(pJsonRoot); //free(p);
    if(NULL == p)
    {
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    //convert json list to string faild, exit
    //because sub json pJsonSubSub han been add to pJsonRoot, so just delete pJsonRoot,
    //if you also delete pJsonSubSub, it will coredump, and error is : double free
    cJSON_Delete(pJsonRoot);
    return p;
}

char *parseJson(char *pMsg)
{
    int i;
    if(NULL == pMsg)
    {
        return NULL;
    }
    cJSON *pJsonRoot = cJSON_Parse(pMsg);
    if(NULL == pJsonRoot)
    {
        // parse faild, return
        return NULL;
    }
    // get string from json
    cJSON * pJsonSub = cJSON_GetObjectItem(pJsonRoot, "name");
    if(NULL == pJsonSub)
    {
        //get object named "name" faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("name : %s\n", pJsonSub->valuestring);
    cJSON_ReplaceItemInObject(pJsonRoot,"name",cJSON_CreateString("JSON中国 1"));//修改json的数据
    // get string from json
    pJsonSub = cJSON_GetObjectItem(pJsonRoot, "url");
    if(NULL == pJsonSub)
    {
        //get object named "url" faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("url : %s\n", pJsonSub->valuestring);
    cJSON_ReplaceItemInObject(pJsonRoot,"url",cJSON_CreateString("http://www.json.org.cn 1"));//修改json的数据
    // get number from json
    pJsonSub = cJSON_GetObjectItem(pJsonRoot, "page");
    if(NULL == pJsonSub)
    {
        //get number from "page" faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("page : %d\n", pJsonSub->valueint);
    cJSON_ReplaceItemInObject(pJsonRoot,"page",cJSON_CreateNumber(88+1));//修改json的数据
    // get bool from json
    pJsonSub = cJSON_GetObjectItem(pJsonRoot, "isNonProfit");
    if(NULL == pJsonSub)
    {
        // get bool from "isNonProfit" faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("isNonProfit : %d\n", pJsonSub->valueint);
    cJSON_ReplaceItemInObject(pJsonRoot,"isNonProfit",cJSON_CreateBool(0));//修改json的数据
    // get sub object
    pJsonSub = cJSON_GetObjectItem(pJsonRoot, "address");
    if(NULL == pJsonSub)
    {
        // get sub object faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    // get sub sub object
    cJSON *pJsonSubSub = cJSON_GetObjectItem(pJsonSub, "street");
    if(NULL == pJsonSubSub)
    {
        // get object from subject object faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("address->street : %s\n", pJsonSubSub->valuestring);
    cJSON_ReplaceItemInObject(pJsonSub,"street",cJSON_CreateString("浙大路38号. 1"));//修改json的数据
    pJsonSubSub = cJSON_GetObjectItem(pJsonSub, "city");
    if(NULL == pJsonSubSub)
    {
        // get object from subject object faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("address->city : %s\n", pJsonSubSub->valuestring);
    cJSON_ReplaceItemInObject(pJsonSub,"city",cJSON_CreateString("浙江杭州 1"));//修改json的数据
    pJsonSubSub = cJSON_GetObjectItem(pJsonSub, "country");
    if(NULL == pJsonSubSub)
    {
        // get object from subject object faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    printf("address->country : %s\n", pJsonSubSub->valuestring);
    cJSON_ReplaceItemInObject(pJsonSub,"country",cJSON_CreateString("中国 1"));//修改json的数据
    pJsonSub = cJSON_GetObjectItem(pJsonRoot, "links");
    if(NULL == pJsonSub)
    {
        // get sub object faild
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    for (i = 0; i < cJSON_GetArraySize(pJsonSub); i++)
    {

        cJSON *pJsonSubArry = cJSON_GetArrayItem(pJsonSub, i);
        if(NULL == pJsonSubArry)
        {
            // get sub object faild
            cJSON_Delete(pJsonRoot);
            return NULL;
        }
        pJsonSubSub = cJSON_GetObjectItem(pJsonSubArry, "name");
        if(NULL == pJsonSub)
        {
            // get object from subject object faild
            cJSON_Delete(pJsonRoot);
            return NULL;
        }
        printf("links[%d]->name : %s\n", i, pJsonSubSub->valuestring);
        cJSON_ReplaceItemInObject(pJsonSubArry,"name",cJSON_CreateString("name 1"));//修改json的数据
        pJsonSubSub = cJSON_GetObjectItem(pJsonSubArry, "url");
        if(NULL == pJsonSubSub)
        {
            // get object from subject object faild
            cJSON_Delete(pJsonRoot);
            return NULL;
        }
        printf("links[%d]->url : %s\n", i, pJsonSubSub->valuestring);
        cJSON_ReplaceItemInObject(pJsonSubArry,"url",cJSON_CreateString("url 1"));//修改json的数据
    }
    char * p = cJSON_Print(pJsonRoot);
    //char * p = cJSON_PrintUnformatted(pJsonRoot); //free(p);
    if(NULL == p)
    {
        cJSON_Delete(pJsonRoot);
        return NULL;
    }
    //Call cJSON_Delete when finished.
    cJSON_Delete(pJsonRoot);
    return p;
}

int main()
{
    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL)
        exit(1);

    printf("===============================\r\n\r\n");
    printf("===============================\r\n\r\n");
    char * p = makeJson();
    if(NULL == p)
    {
        exit(1);
    }
    printf("%s\n", p);
    printf("===============================\r\n\r\n");
    printf("===============================\r\n\r\n");
    p = parseJson(p);
    printf("===============================\r\n\r\n");
    printf("===============================\r\n\r\n");
    printf("%s\n", p);
    fputs(p, fp);
    free(p);//千万不要忘记释放内存呀，cJSON_Print()函数或者cJSON_PrintUnformatted（）产生的内存，使用free(char *)进行释放
    fclose(fp);
    return 0;
}




