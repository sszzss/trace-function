#ifdef __cplusplus
extern "C"
{
#endif

    #include <stdio.h>
    #include <stdlib.h>
    // #include <dlfcn.h>

    // Dl_info get_dl_info(void *this_fn, void *call_site)
    //     __attribute__((no_instrument_function));

    void __cyg_profile_func_enter(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));

    void __cyg_profile_func_exit(void *this_fn, void *call_site)
        __attribute__((no_instrument_function));

    void main_constructor()
        __attribute__((no_instrument_function, constructor));

    void main_destructor()
        __attribute__((no_instrument_function, destructor));

    // Dl_info  get_dl_info(void *this_fn, void *call_site)
    // {
    //     Dl_info info;
    //     if (!dladdr(this_fn, &info))
    //     {
    //         info.dli_fname = "?";
    //         info.dli_sname = "?";
    //     }

    //     if (!info.dli_fname)
    //     {
    //         info.dli_fname = "?";
    //     }

    //     if (!info.dli_sname)
    //     {
    //         info.dli_sname="?";
    //     }

    //     return info;

    // }

    static FILE *fp;

    void __cyg_profile_func_enter(void *this_fn, void *call_site)
    {
        // Dl_info info = get_dl_info(this_fn, call_site);
        if (fp == NULL)
        {
            fp = fopen("trace.log", "w");
            if (fp == NULL)
            {
                exit(-1);
            }
        }
        fprintf(fp, "> %p\n", (int *)this_fn);
        printf("> %p\n", (int *)this_fn);
    }

    void __cyg_profile_func_exit(void *this_fn, void *call_site)
    {
        // Dl_info info = get_dl_info(this_fn, call_site);
        fprintf(fp, "< %p\n", (int *)this_fn);
        printf("< %p\n", (int *)this_fn);
    }

    void main_constructor()
    {
    }

    void main_destructor()
    {
        if (fp != NULL)
        {
            fclose(fp);
        }
    }


#ifdef __cplusplus
}
#endif
