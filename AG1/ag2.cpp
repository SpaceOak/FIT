#ifndef __PROGTEST__
#include "flib.h"
#endif //__PROGTEST__

//
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int arr[], int n, int i) {
    int max = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] > arr[max])
        max = leftChild;

    if (rightChild < n && arr[rightChild] > arr[max])
        max = rightChild;

    if (max != i) {
        swap(&arr[i], &arr[max]);
        heapify(arr, n, max);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}


void main_merge_sort(int32_t first, int32_t second,int32_t third, int32_t bytes)
{


    int32_t * l_buff = new int32_t[bytes/4];
    int32_t * r_buff = new int32_t[bytes/4];
    int64_t l_cur = 0, r_cur = 0;
    int64_t left, right;
    left = flib_read(first,l_buff,bytes/4);
    right = flib_read(second,r_buff,bytes/4);

    int32_t *target = new int32_t[bytes/2];
    int64_t t_size = 0;


    int64_t i = 0;
    for (; ; i++)
    {

        if (l_cur == left)
        {
            left = flib_read(first,l_buff,bytes/4);
            l_cur = 0;

            if ( left == 0 )
            {

                while ( right != 0 )
                {
                    target[i] = r_buff[r_cur];
                    r_cur++;
                    t_size++;
                    i++;

                    if ( r_cur == right )
                    {
                        right = flib_read(second,r_buff,bytes/4);
                        r_cur = 0;
                    }



                    if ( t_size >= bytes/2 )
                    {
                        flib_write(third,target,t_size);
                        t_size = 0;
                        i = 0;
                    }


                }

                break;

            }

        }
        else if ( r_cur == right )
        {
            right = flib_read(second,r_buff,bytes/4);
            r_cur = 0;

            if ( right == 0 )
            {

                while ( left != 0 )
                {
                    target[i] = l_buff[l_cur];
                    l_cur++;
                    t_size++;
                    i++;


                    if ( l_cur == left )
                    {
                        left = flib_read(first,l_buff,bytes/4);
                        l_cur = 0;
                    }

                    if ( t_size >= bytes/2 )
                    {
                        flib_write(third,target,t_size);
                        t_size = 0;
                        i = 0;
                    }

                }

                break;

            }
        }

        if ( t_size >= bytes/2 )
        {
            flib_write(third,target,t_size);
            t_size = 0;
            i = 0;
        }


        if (l_cur <= left && r_cur <= right)
        {
            if (l_buff[l_cur] < r_buff[r_cur])
            {
                target[i] = l_buff[l_cur];
                l_cur++;
                t_size++;
            }
            else
            {
                target[i] = r_buff[r_cur];
                r_cur++;
                t_size++;
            }
        }
        else if (l_cur <= left)
        {
            target[i] = l_buff[l_cur];
            l_cur++;
            t_size++;
        }
        else
        {
            target[i] = r_buff[r_cur];
            r_cur++;
            t_size++;
        }
    }
//----------------------
    /*
    printf("\n sorted shit: ");
    for ( int i = 0 ; i < t_size; i++)
    {
        printf("%d ",target[i]);
    }
    printf("\n");
    */
    flib_write(third,target,t_size);
    delete[] l_buff;
    delete[] r_buff;
    delete[] target;

}


void tarant_allegra ( int32_t in_file, int32_t out_file, int32_t bytes ){

    flib_open ( in_file, READ );
    int32_t * buffer = new int32_t[bytes/4];

    int total = 2;

    uint64_t loaded = flib_read(in_file, buffer, bytes/4);
    for(; loaded != 0 ; loaded = flib_read(in_file, buffer, bytes/4)){
        heapSort(buffer,loaded);
        flib_open(total,WRITE);
        flib_write(total,buffer,loaded);
        flib_close(total);
        //printf(" loaded %d to %d\n", loaded, total);
        total ++;
    }
    //printf(" end of start\n");


    flib_close ( in_file );

    //printf(" last file is %d\n",total);
    for ( int i = 2; i + 1 < total ; i += 2 )
    {
        flib_open(i,READ);
        flib_open(i+1,READ);
        flib_open(total,WRITE);

        main_merge_sort(i,i+1,total,bytes);

        flib_close(total);
        flib_close(i);
        flib_close(i+1);

        total++;

        flib_remove(i);
        flib_remove(i+1);
    }

    loaded = 1;

    flib_open(out_file, WRITE);
    flib_open(total - 1, READ);
    while ( loaded != 0 )
    {
        loaded = flib_read(total - 1, buffer, bytes/4);
        flib_write(out_file,buffer,loaded);
    }
    flib_close(out_file);
    flib_close(total - 1);
    flib_remove(total - 1);


    delete[] buffer;

    //printf(" end of tarant_allegra\n");
}


#ifndef __PROGTEST__

uint64_t total_sum_mod;
void create_random(int output, int size){
    total_sum_mod=0;
    flib_open(output, WRITE);
    /* srand(time(NULL)); */
#define STEP 100ll
    int val[STEP];
    for(int i=0; i<size; i+=STEP){
        for(int j=0; j<STEP && i+j < size; ++j){
            val[j]=-1000 + (rand()%(2*100000+1));
            total_sum_mod += val[j];
        }
        flib_write(output, val, (STEP < size-i) ? STEP : size-i);
    }
    flib_close(output);
}


void check_result ( int out_file, int SIZE ){
    flib_open(out_file, READ);
    int q[30], loaded, last=-(1<<30), total=0;
    uint64_t current_sum_mod=0;
    while(loaded = flib_read(out_file, q, 30), loaded != 0){
        total += loaded;
        for(int i=0; i<loaded; ++i){
            if(last > q[i]){
                printf("the result file contains numbers %d and %d on position %d in the wrong order!\n", last, q[i], i-1);
                exit(1);
            }
            last=q[i];
            current_sum_mod += q[i];
        }
    }
    if(total != SIZE){
        printf("the output contains %d but the input had %d numbers\n", total, SIZE); exit(1);
    }
    if(current_sum_mod != total_sum_mod){
        printf("the output numbers are not the same as the input numbers\n");
        exit(1);
    }
    flib_close(out_file);
    printf(" NOICE\n");
}


int main(int argc, char **argv){
    const uint16_t MAX_FILES = 65535;
    flib_init_files(MAX_FILES);
    int INPUT = 0;
    int RESULT = 1;
    int SIZE = 14000;

    create_random(INPUT, SIZE);
    tarant_allegra(INPUT, RESULT, 1000);
    check_result(RESULT, SIZE);

    flib_free_files();
    return 0;
}
#endif //__PROGTEST__