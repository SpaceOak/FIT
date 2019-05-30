#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#endif /* __PROGTEST__ */

char             * wordWrap                                ( int               width,
                                                             const char      * src ) {

    if (src == NULL) {
        return NULL;
    }

    int sizeOfArr = width;
    char *arr = (char *) malloc(sizeof(char) * width);
    bool test = false;
    int cntArr = 0, cntSrc = 0, cntSpace = 0;
    int stroke = 0;
    int testSize;


    for (int i = 0; i < sizeOfArr; i++) {
        arr[i] = 0;
    }


    while (1) {

        stroke = 0;

        while (true) {

            if (cntArr + width > sizeOfArr) {
                arr = (char *) realloc(arr, sizeof(char) * sizeOfArr * 2);
                sizeOfArr *= 2;
                for (int i = sizeOfArr / 2; i < sizeOfArr; i++) {
                    arr[i] = 0;
                }
            }

            testSize = 0;


            while (src[cntSrc + testSize] != '\n' &&
                   src[cntSrc + testSize] != '\t' &&
                   src[cntSrc + testSize] != ' ') {
                if (src[cntSrc + testSize] == '\0') {
                    test = true;
                    break;
                }
                testSize++;
            }


            if (testSize > width) {
                free(arr);
                return NULL;
            }

            if (testSize + stroke > width)
                break;

            if (cntArr != 0 && stroke + testSize <= width) {
                if (arr[cntArr - 1] != '\n') {
                    arr[cntArr] = ' ';
                    cntArr++;
                }
            }

            if (test)
                break;

            if (testSize + stroke <= width) {
                for (int i = cntSrc;
                     i < cntSrc + testSize;
                     i++) {
                    arr[cntArr] = src[i];
                    cntArr++;
                }
                cntSrc += testSize;
                cntSpace = 0;
                while (src[cntSrc] == '\n' ||
                       src[cntSrc] == '\t' ||
                       src[cntSrc] == ' ') {
                    if (src[cntSrc] == '\n')
                        cntSpace++;
                    cntSrc++;
                }

                if (cntSpace > 1) {
                    arr[cntArr] = '\n';
                    cntArr++;
                    stroke = 0;
                    break;
                }
                stroke += testSize + 1;
            }
        }

        //next line

        while (arr[cntArr] == ' ') {
            cntArr--;
        }
        arr[cntArr] = '\n';
        cntArr++;

        if (test)
            break;
    }

    //last word
    while ((arr[cntArr] == '\n' ||
            arr[cntArr] == '\t' ||
            arr[cntArr] == ' ' ||
            arr[cntArr] == '\0') && cntArr >= 0) {
        arr[cntArr] = 0;
        cntArr--;
    }
    
    cntArr++;

    if (cntArr != 0)
    {
    arr[cntArr] = ' ';
    cntArr++;
    }
    for ( int i = cntSrc;
          src[i]!='\n' && src[i]!=' ' && src[i]!='\t' && src[i]!='\000';
          i++)
    {
        arr[cntArr]=src[i];
        cntArr++;
    }


    while ( arr[cntArr] == '\n' ||
            arr[cntArr] == '\t' ||
            arr[cntArr] == ' '  ||
            arr[cntArr] == '\000')
    {
        arr[cntArr]=0;
        cntArr--;
    }

    cntArr++;
    arr[cntArr]='\n';


    return arr;
}

#ifndef __PROGTEST__
int                main                                     ( void )
{
  char * res;
  const char * s0 =
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
    "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
    "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
    "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
    "libero non diam.";
  const char * s1 =
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
    "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
    "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
    "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
    "libero non diam.\n"
    "\n"
    "Proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
    "amet, magna. Nam congue cursus magna. In malesuada, velit a gravida sodales,\n"
    "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. Nulla\n"
    "eget risus. Quisque nec sapien blandit odio convallis ullamcorper. Lorem\n"
    "ipsum dolor sit amet, consectetuer adipiscing elit. Pellentesque cursus.\n"
    "Aliquam tempus neque vitae libero molestie ut auctor.\n"
    "\n"
    "\n"
    "\n"
    "In nec massa eu tortor vulputate suscipit.\tNam tristique magna nec pede. Sed\n"
    "a nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla\n"
    "facilisi. Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec\n"
    "sed mauris. Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
    "turpis. Mauris malesuada nisi sed enim. In hac habitasse platea dictumst.\n"
    "Fusce    faucibus, turpis nec auctor posuere, nulla tellus scelerisque metus,\n"
    "quis molestie mi dui id quam. Mauris vestibulum. Nam ullamcorper.\n"
    "\n";


    res = wordWrap ( 40, s0 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. Pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. Nam in pede.\n"
    "Etiam eu sem id urna ultricies congue.\n"
    "Vestibulum porttitor ultrices neque.\n"
    "Mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "Pellentesque dui. Vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n" ) );
  free ( res );

  res = wordWrap ( 120, s0 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
    "feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
    "turpis egestas. Nam in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris semper,\n"
    "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n" ) );
  free ( res );

  res = wordWrap ( 10, s1 );
  assert ( res == NULL );

  res = wordWrap ( 40, s1 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. Pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. Nam in pede.\n"
    "Etiam eu sem id urna ultricies congue.\n"
    "Vestibulum porttitor ultrices neque.\n"
    "Mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "Pellentesque dui. Vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n"
    "\n"
    "Proin est nisi, gravida ac, vulputate\n"
    "id, fringilla sit amet, magna. Nam\n"
    "congue cursus magna. In malesuada, velit\n"
    "a gravida sodales, dolor nisl vestibulum\n"
    "orci, sit amet sagittis mauris tellus\n"
    "nec purus. Nulla eget risus. Quisque nec\n"
    "sapien blandit odio convallis\n"
    "ullamcorper. Lorem ipsum dolor sit amet,\n"
    "consectetuer adipiscing elit.\n"
    "Pellentesque cursus. Aliquam tempus\n"
    "neque vitae libero molestie ut auctor.\n"
    "\n"
    "In nec massa eu tortor vulputate\n"
    "suscipit. Nam tristique magna nec pede.\n"
    "Sed a nisi. Nulla sed augue ut risus\n"
    "placerat porttitor. Ut aliquam. Nulla\n"
    "facilisi. Nulla vehicula nibh ac sapien.\n"
    "Nunc facilisis dapibus ipsum. Donec sed\n"
    "mauris. Nulla quam nisi, laoreet non,\n"
    "dignissim posuere, lacinia nec, turpis.\n"
    "Mauris malesuada nisi sed enim. In hac\n"
    "habitasse platea dictumst. Fusce\n"
    "faucibus, turpis nec auctor posuere,\n"
    "nulla tellus scelerisque metus, quis\n"
    "molestie mi dui id quam. Mauris\n"
    "vestibulum. Nam ullamcorper.\n" ) );
  free ( res );

  res = wordWrap ( 80, s1 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique\n"
    "senectus et netus et malesuada fames ac turpis egestas. Nam in pede. Etiam eu\n"
    "sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris\n"
    "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
    "ante nisl ac ante. Pellentesque dui. Vestibulum pretium, augue non cursus\n"
    "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
    "\n"
    "Proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. Nam congue\n"
    "cursus magna. In malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
    "sit amet sagittis mauris tellus nec purus. Nulla eget risus. Quisque nec sapien\n"
    "blandit odio convallis ullamcorper. Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Pellentesque cursus. Aliquam tempus neque vitae libero molestie\n"
    "ut auctor.\n"
    "\n"
    "In nec massa eu tortor vulputate suscipit. Nam tristique magna nec pede. Sed a\n"
    "nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla facilisi.\n"
    "Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec sed mauris.\n"
    "Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. Mauris\n"
    "malesuada nisi sed enim. In hac habitasse platea dictumst. Fusce faucibus,\n"
    "turpis nec auctor posuere, nulla tellus scelerisque metus, quis molestie mi dui\n"
    "id quam. Mauris vestibulum. Nam ullamcorper.\n" ) );
  free ( res );


    char * ss = "         abc          def         ghi        jkl   mno         pqr          stu\n";
    res = wordWrap(50,ss);
    assert(!strcmp(res,"abc def ghi jkl mno pqr stu\n"));
    free(res);

    char * zz = "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij\n"
            "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij\tabcdefghijabcdefghijabcdefghijabcdefghijabcdefghij\n";
    res = wordWrap(50,zz);


    assert(!strcmp(res,"abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij\n"
                   "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij\n"
                   "abcdefghijabcdefghijabcdefghijabcdefghijabcdefghij\n"));
    free(res);

    char * qq = "abc    \n"
            "    def   \n"
            "    ghi   \n"
            "   jkl \n"
            " mno   \n"
            "      pqr    \n"
            "      stu\n";

    res = wordWrap(50,qq);

    assert(!strcmp(res,"abc def ghi jkl mno pqr stu\n"));
    free(res);


    char * a = "a";
    res=wordWrap(20,a);
    assert(!strcmp(res,"a\n"));
    free (res);

    return 0;
}
#endif /* __PROGTEST__ */