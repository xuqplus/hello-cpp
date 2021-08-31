#include <iostream>
#include <config.h>
#include <curl/curl.h>

using namespace std;

void config_print()
{
    std::cout << "HELLO_CPP_VERSION_MAJOR -> " << HELLO_CPP_VERSION_MAJOR << std::endl;
    std::cout << "HELLO_CPP_VERSION_MINOR -> " << HELLO_CPP_VERSION_MINOR << std::endl;
}

void run_function_in_my_lib()
{
#ifndef USE_MY_LIB
    {
        std::cout << "USE_MY_LIB - my lib not compiled .." << std::endl;
    }
#else
    {
        function_in_my_lib();
    }
#endif
}

#include <my-lib2.h>
void run_function_in_my_lib2()
{
    function_in_my_lib2();
}

#include <hello-static-lib.h>
void test_static_lib()
{
    test_f();
}

#include <hello-shared-lib.h>
void test_shared_lib()
{
    test_g();
}

void test_curl()
{
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://example.com/");
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main(int, char **)
{
    std::cout << "hello cpp .." << std::endl;

    config_print();

    run_function_in_my_lib();

    run_function_in_my_lib2();

    test_static_lib();

    test_shared_lib();

    test_curl();
    return 0;
}
