#include <stdio.h>

int err ()
{
    printf("Nespravny vstup.\n");
    return 1;
}


int main()
{
    int st,end,buff,scan,sys;
    char t0, t1,t2,t3, typ;
    int trS[40];
    int cntS = 0 , cntE = 0;
    for(int i = 40 ; i >=0; i--)
    {
        trS[i]=0;
    }

    printf("Zadejte intervaly:\n");


    while(1) {
        cntS=0,cntE=0;
        for(int i = 40 ; i >=0; i--)
        {
            trS[i]=0;
        }
        scan = scanf(" %c", &t0);
        if (scan==EOF)
        {break;}


        if(scan!=1)
            return err();

        if(t0=='<')
        {
            scan = scanf(" %d %c %d %c %c", &st, &t2,
                  &end, &t3, &typ);

            if(scan!=5)
            {
                if(scan==EOF)
                {break;}
                return err();
            }
            if ( t2 != ';'
                || t3 != '>' || st < 0 || end < 0
                || end < st || (typ != 'l' && typ != 's' && typ != 'z'))
                        { return err(); }
            sys = 10;
        }
        else if (t0=='r')
        {
            scan=scanf(" %d %c %c %d %c %d %c %c",&sys,&t0,&t1, &st, &t2,
                  &end, &t3, &typ);
            if(scan!=8)
            {
                if(scan==EOF)
                {break;}
                return err();
            }
            if ( t2 != ';'
                || t3 != '>' || st < 0 || end < 0
                || end < st || (typ != 'l' && typ != 's' && typ != 'z')
                || sys < 2 || t1 != '<' || t0 != ':' || sys > 36)
            { return err(); }
        }
        else
        {
            return err();
        }

        buff = st;
        while (buff >= sys) {
            trS[cntS] = buff % sys;
            buff = buff / sys;
            cntS++;
        }
        trS[cntS] = buff;


        buff = end;
        while (buff >= sys) {
            buff = buff / sys;
            cntE++;
        }


        if (typ == 'l') {
            int res = 0;
            while (st <= end) {
                res += cntS + 1;
                st++;
                trS[0]++;
                if(trS[0]==sys)
                {
                for (int i = 0; i <= cntS; ++i)
                    {
                        if (trS[i] == sys)
                        {
                            trS[i] = 0;
                            trS[i + 1]++;
                        }
                    }
                }
                if (trS[cntS + 1] >= 1) {
                    cntS++;
                }
            }
            printf("Cifer: %d\n", res);
        } else if (typ == 'z') {
            int res = 0;
            while (st <= end) {
                for (int i = 0; i <= cntS; i++) {
                    if (trS[i] == 0) {
                        res++;
                    }
                }
                st++;
                trS[0]++;
                if(trS[0]==sys)
                {
                    for (int i = 0; i <= cntS; ++i)
                    {
                        if (trS[i] == sys)
                        {
                            trS[i] = 0;
                            trS[i + 1]++;
                        }
                    }
                }
                if (trS[cntS + 1] == 1) {
                    cntS++;
                }
            }
            printf("Nul: %d\n", res);
        } else if (typ == 's') {
            int max = 0;
            int res = 0;


            while (st <= end) {


                for (int i = 0; i <= cntS; i++) {
                    if (trS[i] == 0) {
                        while (trS[i] == 0 && i <= cntS) {
                            i++;
                            res++;
                        }
                    }
                    if (max < res) { max = res; }
                    res = 0;
                }
                st++;
                trS[0]++;
                if(trS[0]==sys)
                {
                    for (int i = 0; i <= cntS; ++i)
                    {
                        if (trS[i] == sys)
                        {
                            trS[i] = 0;
                            trS[i + 1]++;
                        }
                    }
                }
                if (trS[cntS + 1] == 1) {
                    cntS++;
                }

            }


            printf("Sekvence: %d\n", max);

        }
    }

}
