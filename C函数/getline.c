#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
    ssize_t getline(char **lineptr, size_t *n, FILE *stream);
    �÷�:
        ��ȡ���ļ���ÿ�ζ�ȡһ�У�������ٶ�ȡ��һ�У�ֱ������ EOF �� ��ȡ����
        �����ж�ȡһ�У�����lineptr�У���'\0'��β��
        ���з�Ҳ�����lineptr�У�
        ������ *lineptr=NULL �� *n=0��getline��Ϊ����䶯̬�洢������getline�����Ƿ�ɹ����û���Ӧfree.
    ����ֵ��
        ʧ�� -1��������errno
        �ɹ� ��ȡ�е��ֽ������������з����ڣ�
    ע�⣺
        �����ı��ļ������з�Ҳ������һ����
    argv[1]�ļ����ݸ�ʽ��
        hello world
        ABC DEF GHHHI
        GOOD
 */
int main(int argc, char *argv[])
{
    int i;
    FILE *f;
    char *line = NULL, *p = NULL;
    size_t len = 0;
    ssize_t nread;
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return -1;
    }
    
    if ((f = fopen(argv[1], "r")) == NULL)
    {
        perror("fopen");
        return -1;
    }
    
    p = line;
    // һ��һ�еĶ�ȡ
    while((nread = getline(&line, &len, f)) != -1)
    {
        printf("nread = %ld, len = %ld\n", nread, len);
        for(i = 0; i < nread; i++)
            printf(" %02X", *line++);
        printf("\n");
    }
    if (nread == -1)
    {
        if (feof(f))
            printf("end of file reached!\n");
        else
            fprintf(stderr, "getline error (%d): %s\n", errno, strerror(errno));
    }
    //ע�⸴λ
    line = p;
    
    free(line);
    fclose(f);

    return 0;
}


